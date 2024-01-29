from pyDICOS import CT, DX, TDR
from pyDICOS import Volume, Array1DPoint3Dfloat, Point3Dfloat, DcsLongText, DcsLongString, DcsShortText, CustomArray1DDcsLongString, Bitmap
from pyDICOS import DcsDateTime, DcsDate, DcsTime
from ._dicosio import read_dcs, write_dcs
import numpy as np
import os

# Handles the ATR metadata.
class ATRSettings:
    def __init__(self, manufacturer, version, parameters) -> None:
        """Initialize the ATR class.
        
        Parameters
        ----------
        manufacturer : str
            The manufacturer of the ATR.
        version : str
            The version of the ATR.
        parameters : dict
            The parameters of the ATR. ex. {"threshold": "0.5", "quantized": "True"...}
        """
        self.manufacturer = DcsLongString(manufacturer)
        self.version = DcsLongString(version)
        self.parameters = CustomArray1DDcsLongString(len(parameters))
        for i, (key, value) in enumerate(parameters.items()):
            self.parameters.SetBuffer(i, DcsLongString(f"-{key}={value}"))

class TDRLoader:
    def __init__(self, filename: str = None, tdr_object: TDR = None) -> None:
        """Initialize the TDRLoader class.

        Parameters
        ----------
        filename : str, optional
            The name of the file to read. The default is None.
        tdr_object : TDR, optional
            The TDR object to use. The default is None.
        """
        self.tdr_object = None

        if filename is not None and tdr_object is not None:
            raise ValueError("Cannot set both filename and TDR object simultaneously.")

        if filename is not None:
            self.tdr_object = read_dcs(filename, "TDR")

        elif tdr_object is not None:
            self.tdr_object = tdr_object

    def write(self, filename :str) -> None:
        """Writes the object to a file.

        Parameters
        ----------
        filename : str
            The name of the file to write.
        """
        write_dcs(self.tdr_object, filename=filename)

    def set_ATR_metadata(self, atr: ATRSettings) -> None:
        """Set the ATR metadata.
        
        Parameters
        ----------
        atr : ATRSettings
            The ATR settings.
        """
        self.tdr_object.SetATRManufacturer(atr.manufacturer)
        self.tdr_object.SetATRVersion(atr.version)
        self.tdr_object.SetATRParameters(atr.parameters)

# This class can be utilized to load a CT object by either reading a CT file or using a provided CT object.
# The 'get_data' function returns a list of 2D NumPy arrays.
class CTLoader:
    def __init__(self, filename: str = None, ct_object: CT = None) -> None:
        """Initialize the CTLoader class.

        Parameters
        ----------
        filename : str, optional
            The name of the file to read. The default is None.
        ct_object : CT, optional
            The CT object to use. The default is None.
        """
        self.ct_object = None

        if filename is not None and ct_object is not None:
            raise ValueError("Cannot set both filename and CT object simultaneously.")

        if filename is not None:
            self.ct_object = read_dcs(filename, "CT")

        elif ct_object is not None:
            self.ct_object = ct_object

    def write(self, filename :str) -> None:
        """Writes the object to a file.

        Parameters
        ----------
        filename : str
            The name of the file to write.
        """
        write_dcs(self.ct_object, filename=filename)

    def get_data(self) -> list:
        """Get the data from the CT object.
        
        Returns
        -------
        data_arrays : list
            A list of 3D NumPy arrays.
        """
        data_arrays = []
        sectionIt = self.ct_object.Begin()

        sectionCount = 0
        while sectionIt != self.ct_object.End():
            # get the section from CTObject iterator
            pSection = sectionIt.deref()
            pixel_data_type = pSection.GetPixelDataType()
            # The IMAGE_DATA_TYPE enumeration is situated in the binding code of the Volume Module.
            if pixel_data_type == Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit:
                volume = pSection.GetPixelData()
                depth_size = volume.GetDepth()
                height_size = volume.GetUnsigned16().GetHeight()
                width_size = volume.GetUnsigned16().GetWidth()

                data_array = np.zeros((depth_size, height_size, width_size), dtype=np.uint16)

                for i in range(volume.GetDepth()):
                    xyPlane = volume.GetUnsigned16()[i]
                    data_array[i] = np.array(xyPlane, copy=False)

                data_arrays.append(data_array)
            next(sectionIt)
            sectionCount += 1
        return data_arrays
    
    def generate_tdr(self, detection_boxes: list, output_file: str = None) -> TDRLoader:
        """Generate a TDR file from the CT object and detections.
        
        Parameters
        ----------
        detection_boxes : list
            A list of detection boxes.
            A detection box is a dictionary with the following keys:
                - "label": The label of the detection box.
                - "point1": The first point of the detection box (front top left).
                - "point2": The second point of the detection box (back bottom right).
                - "confidence": The confidence of the detection box.
                - "mask": The mask of the detection, can be None.
        output_file : str, optional
            The name of the file to write. The default is None.
        """
        if output_file is None:
            raise ValueError("Cannot write TDR file without a filename.")

        tdr = TDR()
        bRes = True
        bRes = bRes and tdr.SetOOIID(self.ct_object.GetOOIID())
        bRes = bRes and tdr.SetScanInstanceUID(self.ct_object.GetScanInstanceUID())
        bRes = bRes and tdr.SetSeriesInstanceUID(self.ct_object.GetSeriesInstanceUID())
        tdr.GenerateSopInstanceUID()
        bRes = bRes and tdr.SetFrameOfReferenceUID(self.ct_object.GetFrameOfReferenceUID())
        
        bounds = Array1DPoint3Dfloat()
        bounds.SetSize(2, False)
        ptBase = Point3Dfloat()
        ptExtents = Point3Dfloat()
        realworld_offset = [- dim // 2 for dim in self.get_data()[0].shape]

        for i, detection_box in enumerate(detection_boxes):
            bRes = bRes and tdr.AddPotentialThreatObject(i, TDR.ThreatType.enumThreatTypeBaggage)
            bRes = bRes and tdr.SetProcessingStartTime(i, DcsDateTime(DcsDate.Today(), DcsTime.Now()))
            bRes = bRes and tdr.AddReferencedInstance(i, self.ct_object.GetSopClassUID(), self.ct_object.GetSopInstanceUID(), 0)
            bRes = bRes and tdr.AddPTOAssessment(i,
                                         TDR.ASSESSMENT_FLAG.enumThreat,
                                         TDR.THREAT_CATEGORY.enumProhibitedItem,
                                         TDR.ABILITY_ASSESSMENT.enumNoInterference,
                                         DcsLongText(detection_box["label"]),
                                         float(detection_box["confidence"]))
            
            # Set the PTO bounding polygon
            bounds[0].Set(realworld_offset[0] + detection_box["point1"][0], 
                          realworld_offset[1] + detection_box["point1"][1], 
                          realworld_offset[2] + detection_box["point1"][2])
            bounds[1].Set(realworld_offset[0] + detection_box["point2"][0], 
                          realworld_offset[1] + detection_box["point2"][1], 
                          realworld_offset[2] + detection_box["point2"][2])
            bRes = bRes and tdr.SetThreatBoundingPolygon(i, bounds, 0)

            # Set the PTO mask
            ptBase.Set(*detection_box["point1"])
            ptExtents.Set(detection_box["point2"][0] - detection_box["point1"][0],
                          detection_box["point2"][1] - detection_box["point1"][1],
                          detection_box["point2"][2] - detection_box["point1"][2])

            bRes = bRes and tdr.SetThreatRegionOfInterest(i, ptBase, ptExtents, detection_box["mask"] or Bitmap(), 0)
            bRes = bRes and tdr.SetBaggagePTODetails(i, 0, 0, 0)
            bRes = bRes and tdr.SetBaggagePTOLocationDescription(i, DcsShortText(detection_box["label"]), 0)
            bRes = bRes and tdr.SetProcessingEndTime(i, DcsDateTime(DcsDate.Today(), DcsTime.Now()))

        assert bRes, "Error setting TDR values"

        if output_file is not None:
            write_dcs(tdr, output_file)
        
        return TDRLoader(tdr_object=tdr)

# This class can be utilized to load a DX object by either reading a DX file or using a provided DX object.
# The 'get_data' function returns 2D NumPy array.
class DXLoader:
    def __init__(self, filename: str = None, dx_object: DX = None) -> None:
        """Initialize the DXLoader class.

        Parameters
        ----------
        filename : str, optional
            The name of the file to read. The default is None.
        ct_object : DX, optional
            The DX object to use. The default is None.
        """
        self.dx_object = None

        if filename is not None and dx_object is not None:
            raise ValueError("Cannot set both filename and DX object simultaneously.")

        if filename is not None:
            self.dx_object = read_dcs(filename, "DX")

        elif dx_object is not None:
            self.dx_object = dx_object

    def write(self, filename :str) -> None:
        """Writes the object to a file.

        Parameters
        ----------
        filename : str
            The name of the file to write.
        """
        write_dcs(self.dx_object, filename=filename)

    def get_data(self) -> np.ndarray:
        """Get the data from the DX object.
        
        Returns
        -------
        data_array : numpy.ndarray
            A 2D NumPy array.
        """
        imgPixelData = self.dx_object.GetXRayData()
        vIndexData = imgPixelData.GetUnsigned16()
        array2d = np.array(vIndexData, copy=False)
        return array2d

    # Note: This function is not implemented in the Stratovan Toolkit yet.
    def generate_tdr(self, detection_boxes: list, output_file: str = None) -> TDRLoader:
        """Generate a TDR file from the DX object and detections.
        
        Parameters
        ----------
        detection_boxes : list
            A list of detection boxes.
            A detection box is a dictionary with the following keys:
                - "label": The label of the detection box.
                - "point1": The first point of the detection box (top left).
                - "point2": The second point of the detection box (bottom right).
                - "confidence": The confidence of the detection box.
        output_file : str, optional
            The name of the file to write. The default is None.
        """
        return TDRLoader()
    
