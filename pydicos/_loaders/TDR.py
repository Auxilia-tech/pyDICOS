from pyDICOS import TDR, Bitmap, Point3Dfloat, DcsLongString, Array1DDcsLongString, Array1DS_UINT16, Array1DPoint3Dfloat
from .ATR import ATRSettings
from .._dicosio import read_dcs, write_dcs
from ..utils.time import DicosDateTime
import numpy as np

# This class can be utilized to load a TDR object by either reading a TDR file or using a provided TDR object.
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

        else:
            self.tdr_object = TDR()

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
        self.tdr_object.SetTDRTypeATR(atr.manufacturer, atr.version, atr.parameters)

    def get_ATR_metadata(self) -> ATRSettings:
        """Get the ATR metadata.
        
        Returns
        -------
        atr : ATRSettings
            The ATR settings.
        """
        meta = self.tdr_object.GetATRInfo(DcsLongString(), DcsLongString(), Array1DDcsLongString())
        atr = ATRSettings()
        atr.manufacturer = meta[1]
        atr.version = meta[2]
        atr.parameters = meta[3]

        return atr
    
    def get_data(self) -> dict:
        """Get the data from the TDR object.
        
        Returns
        -------
        data_arrays : list
            A dict of values.
            The keys are:
                - InstanceNumber : int, the instance number of the TDR.
                - InstanceUID : str, the instance UniqueID of the TDR.
                - ScanStartDateTime : dict, the scan start date and time.
                - ScanType : int, the scan type.
                - ImageScaleRepresentation : int, the image scale representation.
                - ATR : dict, the ATR metadata.
                - PTOs : list, the list of PTOs.
        """
        data = {"InstanceNumber": self.tdr_object.GetInstanceNumber(),
                "InstanceUID": self.tdr_object.GetScanInstanceUID().Get(),
                "ScanStartDateTime": DicosDateTime(date=self.tdr_object.GetScanStartDate(), 
                                                   time=self.tdr_object.GetScanStartTime()).as_dict(),
                "ProcessingTime": self.tdr_object.GetTotalProcessingTimeInMS(),
                "ScanType": self.tdr_object.GetScanType(),
                "AlarmDecision": self.tdr_object.GetAlarmDecision(),
                "ImageScaleRepresentation": self.tdr_object.GetImageScaleRepresentation(),
                "ATR": self.get_ATR_metadata().as_dict(),
                "PTOs": []}
        
        PTOIds = Array1DS_UINT16()
        self.tdr_object.GetPTOIds(PTOIds)
        PTOBase, PTOExtent, bitmap, polygon = Point3Dfloat(), Point3Dfloat(), Bitmap(), Array1DPoint3Dfloat()
        for i in range(PTOIds.GetSize()):
            self.tdr_object.GetThreatRegionOfInterest(PTOIds[i], PTOBase, PTOExtent, bitmap, 0)
            # TODO: debug the following line
            # self.tdr_object.GetThreatBoundingPolygon(PTOIds[i], polygon, 0)
            data["PTOs"].append({"Base": {"x" : PTOBase.x, "y" : PTOBase.y, "z" : PTOBase.z},
                                 "Extent": {"x" : PTOExtent.x, "y" : PTOExtent.y, "z" : PTOExtent.z},
                                 "Bitmap": np.array(bitmap.GetBitmap().GetData(), copy=False),
                                 "Description": self.tdr_object.GetPTOAssessmentDescription(PTOIds[i], 0).Get(),
                                 "Probability": self.tdr_object.GetPTOAssessmentProbability(PTOIds[i], 0),
                                 "Polygon": [{"x" : polygon[j].x, "y" : polygon[j].y, "z" : polygon[j].z} for j in range(polygon.GetSize())],
                                 "ID": PTOIds[i]
                                 })
        
        return data
    
    def __len__(self) -> int:
        """Get the number of PTO.
        
        Returns
        -------
        int
            The number of PTO.
        """
        return self.tdr_object.GetNumPTOs()