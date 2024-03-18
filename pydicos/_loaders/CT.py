import numpy as np
from pyDICOS import (
    CT,
    TDR,
    Array1DPoint3Dfloat,
    Bitmap,
    DcsDate,
    DcsDateTime,
    DcsLongText,
    DcsShortText,
    DcsTime,
    Point3Dfloat,
    Volume,
    Filename,
    ErrorLog,
)

from .TDR import TDRLoader


# This class can be utilized to load a CT object by either reading a CT file or using a provided CT object.
# The 'get_data' function returns a list of 2D NumPy arrays.
class CTLoader(CT):
    def __init__(self, filename: str = None) -> None:
        """Initialize the CTLoader class.

        Parameters
        ----------
        filename : str, optional
            The name of the file to read.
            The default is None and will create an empty CT.
        """
        super().__init__()

        if filename is not None:
            self.read(filename)

    def read(self, filename: str) -> None:
        """Reads the object from a file.

        Parameters
        ----------
        filename : str
            The name of the file to read.
        """
        _err = ErrorLog()
        if not self.Read(Filename(filename), _err, None):
            raise RuntimeError(
            f"Failed to read DICOS file: {filename}\n{_err.GetErrorLog().Get()}"
        )

    def write(self, filename: str) -> None:
        """Writes the object to a file.

        Parameters
        ----------
        filename : str
            The name of the file to write.
        """
        _err = ErrorLog()
        if not self.Write(
            Filename(filename), _err, CT.TRANSFER_SYNTAX.enumLittleEndianExplicit
        ):
            raise RuntimeError(
            f"Failed to write DICOS file: {filename}\n{_err.GetErrorLog().Get()}"
        )

    def get_data(self) -> list:
        """Get the data from the CT object.

        Returns
        -------
        data_arrays : list
            A list of 3D NumPy arrays.
        """
        data_arrays = []
        sectionIt = self.Begin()

        sectionCount = 0
        while sectionIt != self.End():
            # get the section from CTObject iterator
            pSection = sectionIt.deref()
            pixel_data_type = pSection.GetPixelDataType()
            # The IMAGE_DATA_TYPE enumeration is situated in the binding code of the Volume Module.
            if pixel_data_type == Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit:
                volume = pSection.GetPixelData()
                depth_size = volume.GetDepth()
                height_size = volume.GetUnsigned16().GetHeight()
                width_size = volume.GetUnsigned16().GetWidth()

                data_array = np.zeros(
                    (depth_size, height_size, width_size), dtype=np.uint16
                )

                for i in range(volume.GetDepth()):
                    xyPlane = volume.GetUnsigned16()[i]
                    data_array[i] = np.array(xyPlane, copy=False)

                data_arrays.append(data_array)
            next(sectionIt)
            sectionCount += 1
        return data_arrays
    
    def set_data(self, data: list) -> None:
        """Set the data in the CT object.

        Parameters
        ----------
        data : list
            A list of 3D NumPy arrays.
        """

        self.SetNumberOfSections(len(data))

        for n, array in enumerate(data):
            assert array.ndim == 3, "Data must be 3D"
            assert array.dtype == np.uint16, "Data must be uint16"

            section = self.GetSectionByIndex(n)
            volume = section.GetPixelData()
            volume.set_data(volume, array)

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
        for field in ["label", "point1", "point2", "confidence", "mask"]:
            for box in detection_boxes:
                assert field in box
    
        tdr = TDRLoader()
        bRes = True
        bRes = bRes and tdr.SetOOIType(self.GetOOIType())
        bRes = bRes and tdr.SetOOIID(self.GetOOIID())
        bRes = bRes and tdr.SetOOIIDType(self.GetOOIIDType())
        bRes = bRes and tdr.SetScanInstanceUID(self.GetScanInstanceUID())
        bRes = bRes and tdr.SetSeriesInstanceUID(self.GetSeriesInstanceUID())
        bRes = bRes and tdr.SetTDRType(TDR.TDR_TYPE.enumMachine)
        tdr.GenerateSopInstanceUID()
        bRes = bRes and tdr.SetFrameOfReferenceUID(self.GetFrameOfReferenceUID())

        bounds = Array1DPoint3Dfloat()
        bounds.SetSize(2, False)
        ptBase = Point3Dfloat()
        ptExtents = Point3Dfloat()
        realworld_offset = [-dim // 2 for dim in self.get_data()[0].shape]

        for i, detection_box in enumerate(detection_boxes):
            bRes = bRes and tdr.AddPotentialThreatObject(
                i, TDR.ThreatType.enumThreatTypeBaggage
            )
            bRes = bRes and tdr.SetProcessingStartTime(
                i, DcsDateTime(DcsDate.Today(), DcsTime.Now())
            )
            bRes = bRes and tdr.AddReferencedInstance(
                i, self.GetSopClassUID(), self.GetSopInstanceUID(), 0
            )
            bRes = bRes and tdr.AddPTOAssessment(
                i,
                TDR.ASSESSMENT_FLAG.enumThreat,
                TDR.THREAT_CATEGORY.enumProhibitedItem,
                TDR.ABILITY_ASSESSMENT.enumNoInterference,
                DcsLongText(detection_box["label"]),
                float(detection_box["confidence"]),
            )

            # Set the PTO bounding polygon
            bounds[0] = Point3Dfloat(
                realworld_offset[0] + detection_box["point1"][0],
                realworld_offset[1] + detection_box["point1"][1],
                realworld_offset[2] + detection_box["point1"][2],
            )
            bounds[1] = Point3Dfloat(
                realworld_offset[0] + detection_box["point2"][0],
                realworld_offset[1] + detection_box["point2"][1],
                realworld_offset[2] + detection_box["point2"][2],
            )
            bRes = bRes and tdr.SetThreatBoundingPolygon(i, bounds, 0)

            # Set the PTO mask
            ptBase.Set(*detection_box["point1"])
            ptExtents.Set(
                detection_box["point2"][0] - detection_box["point1"][0],
                detection_box["point2"][1] - detection_box["point1"][1],
                detection_box["point2"][2] - detection_box["point1"][2],
            )

            bRes = bRes and tdr.SetThreatRegionOfInterest(
                i, ptBase, ptExtents, detection_box["mask"] or Bitmap(), 0
            )
            bRes = bRes and tdr.SetBaggagePTODetails(i, 0, 0, 0)
            bRes = bRes and tdr.SetBaggagePTOLocationDescription(
                i, DcsShortText(detection_box["label"]), 0
            )
            bRes = bRes and tdr.SetProcessingEndTime(
                i, DcsDateTime(DcsDate.Today(), DcsTime.Now())
            )

        assert bRes, "Error setting TDR values"

        if output_file is not None:
            tdr.write(output_file)

        return tdr
