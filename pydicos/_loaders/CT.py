import numpy as np
from pyDICOS import (
    CT,
    TDR,
    DcsUniqueIdentifier,
    Array1DPoint3Dfloat,
    Bitmap,
    MemoryBuffer,
    DcsDate,
    DcsDateTime,
    DcsLongText,
    SCAN_TYPE,
    DcsShortText,
    DcsTime,
    Point3Dfloat,
    Volume,
    Filename,
    ErrorLog,
)

from .TDR import TDRLoader
from .ATR import ATRSettings


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

    def generate_tdr(self, data: dict, output_file: str = None) -> TDRLoader:
        """Generate a TDR file from the CT object and detections.

        Parameters
        ----------
        data : dict
            A dict of values.
            The keys are:
                - InstanceNumber : int, the instance number of the TDR.
                - ContentDateAndTime : dict, the scan start date and time.
                - ProcessingTime : int, the processing time.
                - ScanType : int, the scan type.
                - AlarmDecision : int, the alarm decision.
                - AlarmDecisionDateTime : dict, the alarm decision date and time.
                - ImageScaleRepresentation : int, the image scale representation.
                - ATR : dict, the ATR metadata. See TDR_DATA_TEMPLATE for more information.
                - PTOs : list, the list of PTOs. A PTO is a dict with the following keys:
                    - Base : dict, the base point of the PTO.
                    - Extent : dict, the extent of the PTO.
                    - Bitmap : np.ndarray, the bitmap of the PTO.
                    - Description : str, the description of the PTO.
                    - Probability : float, the probability of the PTO.
                    - Polygon : list, the list of points of the PTO polygon.
                    - ID : int, the ID of the PTO.
                    - ReferencedInstance : dict, the referenced instance of the PTO.
                    - PTOProcessingTime : dict, the processing time of the PTO.
        """
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

        if "InstanceNumber" in data:
            assert isinstance(data["InstanceNumber"], int), "InstanceNumber must be an integer"
            tdr.SetInstanceNumber(data["InstanceNumber"])
        
        if "ContentDateAndTime" in data:
            assert isinstance(data["ContentDateAndTime"], dict), "ContentDateAndTime must be a dict"
            assert "date" in data["ContentDateAndTime"], "ContentDateAndTime must have a date"
            assert isinstance(data["ContentDateAndTime"]["date"], (list, tuple)), "ContentDateAndTime date must be a list"
            assert len(data["ContentDateAndTime"]["date"]) == 3, "ContentDateAndTime date must have 3 elements"
            assert "time" in data["ContentDateAndTime"], "ContentDateAndTime must have a time"
            assert isinstance(data["ContentDateAndTime"]["time"], (list, tuple)), "ContentDateAndTime time must be a list"
            assert len(data["ContentDateAndTime"]["time"]) == 4, "ContentDateAndTime time must have 4 elements"
            tdr.SetContentDateAndTime(DcsDate(*data["ContentDateAndTime"]["date"]), DcsTime(*data["ContentDateAndTime"]["time"]))
        
        if "ProcessingTime" in data:
            assert isinstance(data["ProcessingTime"], (int, float)), "ProcessingTime must be a float or int"
            tdr.SetTotalProcessingTimeInMS(data["ProcessingTime"])
        
        if "ScanType" in data:
            assert isinstance(data["ScanType"], SCAN_TYPE), "ScanType must be a SCAN_TYPE enum"
            tdr.SetScanType(data["ScanType"])
        
        if "AlarmDecision" in data:
            assert isinstance(data["AlarmDecision"], TDR.ALARM_DECISION), "AlarmDecision must be an ALARM_DECISION enum"
            tdr.SetAlarmDecision(data["AlarmDecision"])
        
        if "AlarmDecisionDateTime" in data:
            assert isinstance(data["AlarmDecisionDateTime"], dict), "AlarmDecisionDateTime must be a dict"
            assert "date" in data["AlarmDecisionDateTime"], "AlarmDecisionDateTime must have a date"
            assert isinstance(data["AlarmDecisionDateTime"]["date"], (list, tuple)), "AlarmDecisionDateTime date must be a list"
            assert len(data["AlarmDecisionDateTime"]["date"]) == 3, "AlarmDecisionDateTime date must have 3 elements"
            assert "time" in data["AlarmDecisionDateTime"], "AlarmDecisionDateTime must have a time"
            assert isinstance(data["AlarmDecisionDateTime"]["time"], (list, tuple)), "AlarmDecisionDateTime time must be a list"
            assert len(data["AlarmDecisionDateTime"]["time"]) == 4, "AlarmDecisionDateTime time must have 4 elements"
            tdr.SetAlarmDecisionDateTime(
                DcsDate(*data["AlarmDecisionDateTime"]["date"]), DcsTime(*data["AlarmDecisionDateTime"]["time"])
            )
        
        if "ImageScaleRepresentation" in data:
            assert isinstance(data["ImageScaleRepresentation"], (float, int)), "ImageScaleRepresentation must be a float or int"
            tdr.SetImageScaleRepresentation(data["ImageScaleRepresentation"])
        
        if "ATR" in data:
            assert isinstance(data["ATR"], dict), "ATR must be a dict"
            for field in data["ATR"]:
                assert field in ["manufacturer", "version", "parameters"], "ATR must have manufacturer, version and parameters fields only"
            tdr.set_ATR_metadata(ATRSettings(**data["ATR"]))

        if "PTOs" in data:
            assert isinstance(data["PTOs"], list), "PTOs must be a list"
            for pto in data["PTOs"]:
                assert isinstance(pto, dict), "PTOs must be a list of dicts"
                for field in ["Base", "Extent", "ID"]:
                    assert field in pto, f"PTO must have {field} field"

                tdr.AddPotentialThreatObject(pto["ID"], TDR.ThreatType.enumThreatTypeBaggage)
                threat_bitmap = Bitmap()
                if "Bitmap" in pto:
                    assert isinstance(pto["Bitmap"], np.ndarray), "Bitmap must be a numpy array"
                    assert pto["Bitmap"].ndim == 3, "Bitmap must be a 3D numpy array"
                    assert pto["Bitmap"].shape == (pto["Extent"]["x"], pto["Extent"]["y"], pto["Extent"]["z"]), "Bitmap shape must match the extent"
                    if pto["Bitmap"].sum() != 0:
                        threat_bitmap.SetDims(pto["Bitmap"].shape[0], pto["Bitmap"].shape[1], pto["Bitmap"].shape[2], True)
                        flat_bitmap = pto["Bitmap"].astype(np.uint8).ravel()
                        byte_array = np.packbits(flat_bitmap, bitorder="little")
                        byte_buffer = MemoryBuffer()
                        byte_buffer.SetBuffer(byte_array.tobytes(), byte_array.size)
                        threat_bitmap.SetBitmapData(byte_buffer, True)
                        assert threat_bitmap.GetNumBits() == pto["Bitmap"].size, "Failed to set bitmap"

                tdr.SetThreatRegionOfInterest(
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
                    tdr.SetThreatBoundingPolygon(pto["ID"], polygon, 0)

                if "Assessment" in pto:
                    assert isinstance(pto["Assessment"], dict), "Assessment must be a dict"
                    for field in pto["Assessment"]:
                        assert field in ["flag", "category", "ability", "description", "probability"], "Assessment must have flag, category, ability, description and probability fields only"
                    tdr.DeleteAssessments(pto["ID"])
                    tdr.AddPTOAssessment(
                        pto["ID"],
                        pto["Assessment"].get("flag", TDR.ASSESSMENT_FLAG.enumUnknown),
                        pto["Assessment"].get("category", TDR.THREAT_CATEGORY.enumAnomaly),
                        pto["Assessment"].get("ability", TDR.ABILITY_ASSESSMENT.enumNoInterference),
                        DcsLongText(pto["Assessment"].get("description", "")),
                        pto["Assessment"].get("probability", -1)
                    )
                if "ReferencedInstance" in pto:
                    assert isinstance(pto["ReferencedInstance"], dict), "ReferencedInstance must be a dict"
                    for field in pto["ReferencedInstance"]:
                        assert field in ["SopClassUID", "SopInstanceUID"], "ReferencedInstance must have SopClassUID and SopInstanceUID fields only"
                    tdr.AddReferencedInstance(
                        pto["ID"], 
                        DcsUniqueIdentifier(pto["ReferencedInstance"]["SopClassUID"]),
                        DcsUniqueIdentifier(pto["ReferencedInstance"]["SopInstanceUID"]),
                        0 ) # Index for which PTO Representation Sequence Item
                else:
                    bRes = bRes and tdr.AddReferencedInstance(pto["ID"], self.GetSopClassUID(), self.GetSopInstanceUID(), 0)
                    
                if "PTOProcessingTime" in pto:
                    assert isinstance(pto["PTOProcessingTime"], dict), "PTOProcessingTime must be a dict"
                    for field in pto["PTOProcessingTime"]:
                        assert field in ["ProcessingStartTime", "ProcessingEndTime", "fTotalTimeMS"], "PTOProcessingTime must have ProcessingStartTime, ProcessingEndTime and fTotalTimeMS fields only"
                    ProcessingStartTime = pto["PTOProcessingTime"]["ProcessingStartTime"]
                    ProcessingEndTime = pto["PTOProcessingTime"]["ProcessingEndTime"]
                    assert isinstance(ProcessingStartTime, dict), "ProcessingStartTime must be a dict"
                    assert isinstance(ProcessingEndTime, dict), "ProcessingEndTime must be a dict"
                    tdr.SetPTOProcessingTime(
                        pto["ID"],
                        DcsDateTime(DcsDate(*ProcessingStartTime["date"]), DcsTime(*ProcessingStartTime["time"])),
                        DcsDateTime(DcsDate(*ProcessingEndTime["date"]), DcsTime(*ProcessingEndTime["time"])),
                        pto["PTOProcessingTime"]["fTotalTimeMS"])
                
        assert bRes, "Error setting TDR values"

        if output_file is not None:
            tdr.write(output_file)

        return tdr