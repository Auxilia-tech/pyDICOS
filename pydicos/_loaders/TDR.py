import numpy as np
from pyDICOS import (
    TDR,
    Array1DDcsLongString,
    Array1DPoint3Dfloat,
    Array1DS_UINT16,
    Bitmap,
    DcsLongString,
    DcsLongText,
    DcsUniqueIdentifier,
    Point3Dfloat,
    DcsDate,
    DcsTime,
    ErrorLog,
    Filename,
    SCAN_TYPE,
    ALARM_DECISION,
    ASSESSMENT_FLAG,
    THREAT_CATEGORY,
    ABILITY_ASSESSMENT,
)

from ..utils.time import DicosDateTime
from .ATR import ATRSettings


# This class can be utilized to load a TDR object by either reading a TDR file or using a provided TDR object.
class TDRLoader(TDR):
    def __init__(self, filename: str = None) -> None:
        """Initialize the TDRLoader class.

        Parameters
        ----------
        filename : str, optional
            The name of the file to read.
            The default is None and will create an empty TDR.
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
        if not self.Write(Filename(filename), _err):
            raise RuntimeError(
            f"Failed to write DICOS file: {filename}\n{_err.GetErrorLog().Get()}"
        )

    def set_ATR_metadata(self, atr: ATRSettings) -> None:
        """Set the ATR metadata.

        Parameters
        ----------
        atr : ATRSettings
            The ATR settings.
        """
        self.SetTDRTypeATR(atr.manufacturer, atr.version, atr.parameters)

    def get_ATR_metadata(self) -> ATRSettings:
        """Get the ATR metadata.

        Returns
        -------
        atr : ATRSettings
            The ATR settings.
        """
        meta = self.GetATRInfo(DcsLongString(), DcsLongString(), Array1DDcsLongString())
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
                - ContentDateAndTime : dict, the scan start date and time.
                - ScanType : int, the scan type.
                - ImageScaleRepresentation : int, the image scale representation.
                - ATR : dict, the ATR metadata.
                - PTOs : list, the list of PTOs.
        """
        data = {
            "InstanceNumber": self.GetInstanceNumber(),
            "InstanceUID": self.GetScanInstanceUID().Get(),
            "OOIID": self.GetOOIID().Get(),
            "ContentDateAndTime": DicosDateTime(
                date=self.GetContentDate(), 
                time=self.GetContentTime(),
            ).as_dict(),
            "ProcessingTime": self.GetTotalProcessingTimeInMS(),
            "ScanType": self.GetScanType(),
            "AlarmDecision": self.GetAlarmDecision(),
            "AlarmDecisionDateTime": DicosDateTime(
                date=self.GetAlarmDecisionDateTime(DcsDate(), DcsTime())[1],
                time=self.GetAlarmDecisionDateTime(DcsDate(), DcsTime())[2],
            ).as_dict(),
            "ImageScaleRepresentation": self.GetImageScaleRepresentation(),
            "ATR": self.get_ATR_metadata().as_dict(),
            "PTOs": [],
        }

        PTOIds = Array1DS_UINT16()
        self.GetPTOIds(PTOIds)
        PTOBase, PTOExtent, bitmap, polygon = (
            Point3Dfloat(),
            Point3Dfloat(),
            Bitmap(),
            Array1DPoint3Dfloat(),
        )
        for i in range(PTOIds.GetSize()):
            self.GetThreatRegionOfInterest(PTOIds[i], PTOBase, PTOExtent, bitmap, 0)
            self.GetThreatBoundingPolygon(PTOIds[i], polygon, 0)
            data["PTOs"].append(
                {
                    "Base": {"x": PTOBase.x, "y": PTOBase.y, "z": PTOBase.z},
                    "Extent": {"x": PTOExtent.x, "y": PTOExtent.y, "z": PTOExtent.z},
                    "Bitmap": np.array(bitmap.GetBitmap().GetData(), copy=False),
                    "Polygon": [
                        {"x": polygon[j].x, "y": polygon[j].y, "z": polygon[j].z}
                        for j in range(polygon.GetSize())
                    ],
                    "ID": PTOIds[i],
                    "Assessment": {
                        "flag": self.GetPTOAssessmentFlag(PTOIds[i], 0),
                        "category": self.GetPTOAssessmentThreatCategory(PTOIds[i], 0),
                        "ability": self.GetPTOAssessmentAbility(PTOIds[i], 0),
                        "description": self.GetPTOAssessmentDescription(PTOIds[i], 0).Get(),
                        "probability": self.GetPTOAssessmentProbability(PTOIds[i], 0),
                    },
                }
            )

        return data
    
    def set_data(self, data: dict) -> None:
        """Set the data in the TDR object.

        Parameters
        ----------
        data : dict
            A dict of values.
            The keys are:
                - InstanceNumber : int, the instance number of the TDR.
                - InstanceUID : str, the instance UniqueID of the TDR.
                - ContentDateAndTime : dict, the scan start date and time.
                - ProcessingTime : int, the processing time.
                - ScanType : int, the scan type.
                - AlarmDecision : int, the alarm decision.
                - AlarmDecisionDateTime : dict, the alarm decision date and time.
                - ImageScaleRepresentation : int, the image scale representation.
                - ATR : dict, the ATR metadata.
                - PTOs : list, the list of PTOs. A PTO is a dict with the following keys:
                    - Base : dict, the base point of the PTO.
                    - Extent : dict, the extent of the PTO.
                    - Bitmap : np.ndarray, the bitmap of the PTO.
                    - Description : str, the description of the PTO.
                    - Probability : float, the probability of the PTO.
                    - Polygon : list, the list of points of the PTO polygon.
                    - ID : int, the ID of the PTO.
        """
        if "InstanceNumber" in data:
            assert isinstance(data["InstanceNumber"], int), "InstanceNumber must be an integer"
            self.SetInstanceNumber(data["InstanceNumber"])
        
        if "InstanceUID" in data:
            assert isinstance(data["InstanceUID"], str), "InstanceUID must be a string"
            self.SetScanInstanceUID(DcsUniqueIdentifier(data["InstanceUID"]))
        
        if "OOIID" in data:
            assert isinstance(data["OOIID"], str), "OOIID must be a string"
            self.SetOOIID(DcsLongString(data["OOIID"]))
        
        if "ContentDateAndTime" in data:
            assert isinstance(data["ContentDateAndTime"], dict), "ContentDateAndTime must be a dict"
            assert "date" in data["ContentDateAndTime"], "ContentDateAndTime must have a date"
            assert isinstance(data["ContentDateAndTime"]["date"], (list, tuple)), "ContentDateAndTime date must be a list"
            assert len(data["ContentDateAndTime"]["date"]) == 3, "ContentDateAndTime date must have 3 elements"
            assert "time" in data["ContentDateAndTime"], "ContentDateAndTime must have a time"
            assert isinstance(data["ContentDateAndTime"]["time"], (list, tuple)), "ContentDateAndTime time must be a list"
            assert len(data["ContentDateAndTime"]["time"]) == 4, "ContentDateAndTime time must have 4 elements"
            self.SetContentDateAndTime(DcsDate(*data["ContentDateAndTime"]["date"]), DcsTime(*data["ContentDateAndTime"]["time"]))
        
        if "ProcessingTime" in data:
            assert isinstance(data["ProcessingTime"], (int, float)), "ProcessingTime must be a float or int"
            self.SetTotalProcessingTimeInMS(data["ProcessingTime"])
        
        if "ScanType" in data:
            assert isinstance(data["ScanType"], SCAN_TYPE), "ScanType must be a SCAN_TYPE enum"
            self.SetScanType(data["ScanType"])
        
        if "AlarmDecision" in data:
            assert isinstance(data["AlarmDecision"], ALARM_DECISION), "AlarmDecision must be an ALARM_DECISION enum"
            self.SetAlarmDecision(data["AlarmDecision"])
        
        if "AlarmDecisionDateTime" in data:
            assert isinstance(data["AlarmDecisionDateTime"], dict), "AlarmDecisionDateTime must be a dict"
            assert "date" in data["AlarmDecisionDateTime"], "AlarmDecisionDateTime must have a date"
            assert isinstance(data["AlarmDecisionDateTime"]["date"], (list, tuple)), "AlarmDecisionDateTime date must be a list"
            assert len(data["AlarmDecisionDateTime"]["date"]) == 3, "AlarmDecisionDateTime date must have 3 elements"
            assert "time" in data["AlarmDecisionDateTime"], "AlarmDecisionDateTime must have a time"
            assert isinstance(data["AlarmDecisionDateTime"]["time"], (list, tuple)), "AlarmDecisionDateTime time must be a list"
            assert len(data["AlarmDecisionDateTime"]["time"]) == 4, "AlarmDecisionDateTime time must have 4 elements"
            self.SetAlarmDecisionDateTime(
                DcsDate(*data["AlarmDecisionDateTime"]["date"]), DcsTime(*data["AlarmDecisionDateTime"]["time"])
            )
        
        if "ImageScaleRepresentation" in data:
            assert isinstance(data["ImageScaleRepresentation"], (float, int)), "ImageScaleRepresentation must be a float or int"
            self.SetImageScaleRepresentation(data["ImageScaleRepresentation"])
        
        if "ATR" in data:
            assert isinstance(data["ATR"], dict), "ATR must be a dict"
            for field in data["ATR"]:
                assert field in ["manufacturer", "version", "parameters"], "ATR must have manufacturer, version and parameters fields only"
            self.set_ATR_metadata(ATRSettings(**data["ATR"]))

        if "PTOs" in data:
            assert isinstance(data["PTOs"], list), "PTOs must be a list"
            for pto in data["PTOs"]:
                assert isinstance(pto, dict), "PTOs must be a list of dicts"
                for field in ["Base", "Extent", "ID"]:
                    assert field in pto, f"PTO must have {field} field"

                self.AddPotentialThreatObject(pto["ID"], TDR.ThreatType.enumThreatTypeBaggage)
                threat_bitmap = Bitmap()
                # if "Bitmap" in pto:
                #     threat_bitmap.SetData(pto["Bitmap"].tobytes()) # TODO: Implement this
                self.SetThreatRegionOfInterest(
                    pto["ID"],
                    Point3Dfloat(pto["Base"]["x"], pto["Base"]["y"], pto["Base"]["z"]),
                    Point3Dfloat(pto["Extent"]["x"], pto["Extent"]["y"], pto["Extent"]["z"]),
                    threat_bitmap, 
                    0,
                )

                if "Polygon" in pto:
                    polygon = Array1DPoint3Dfloat()
                    for point in pto["Polygon"]:
                        polygon.Append(Point3Dfloat(point["x"], point["y"], point["z"]))
                    self.SetThreatBoundingPolygon(pto["ID"], polygon, 0)

                if "Assessment" in pto:
                    assert isinstance(pto["Assessment"], dict), "Assessment must be a dict"
                    for field in pto["Assessment"]:
                        assert field in ["flag", "category", "ability", "description", "probability"], "Assessment must have flag, category, ability, description and probability fields only"
                    self.DeleteAssessments(pto["ID"])
                    self.AddPTOAssessment(
                        pto["ID"],
                        pto["Assessment"].get("flag", ASSESSMENT_FLAG.enumUnknown),
                        pto["Assessment"].get("category", THREAT_CATEGORY.enumAnomaly),
                        pto["Assessment"].get("ability", ABILITY_ASSESSMENT.enumNoInterference),
                        DcsLongText(pto["Assessment"].get("description", "")),
                        pto["Assessment"].get("probability", -1)
                    )

    def __len__(self) -> int:
        """Get the number of PTO.

        Returns
        -------
        int
            The number of PTO.
        """
        return self.GetNumPTOs()


TDR_DATA_TEMPLATE = {
    "InstanceNumber": 0,
    "InstanceUID": "",
    "OOIID": "",
    "ContentDateAndTime": {
        "date": (0, 0, 0),
        "time": (0, 0, 0, 0),
    },
    "ProcessingTime": 0,
    "ScanType": SCAN_TYPE.enumUnknownScanType,
    "AlarmDecision": ALARM_DECISION.enumUnknownAlarmDecision,
    "AlarmDecisionDateTime": {
        "date": (0, 0, 0),
        "time": (0, 0, 0, 0),
    },
    "ImageScaleRepresentation": 0,
    "ATR": {
        "manufacturer": "",
        "version": "",
        "parameters": {"param1": "value1", "param2": "value2"},
    },
    "PTOs": [
        {
            "Base": {"x": 0, "y": 0, "z": 0},
            "Extent": {"x": 0, "y": 0, "z": 0},
            "Bitmap": np.zeros((0, 0, 0), dtype=np.uint16),
            "Polygon": [],
            "ID": 0,
            "Assessment": {
                "flag": ASSESSMENT_FLAG.enumUnknown,
                "category": THREAT_CATEGORY.enumAnomaly,
                "ability": ABILITY_ASSESSMENT.enumNoInterference,
                "description": "",
                "probability": -1.0,
            }
        }
    ],
}