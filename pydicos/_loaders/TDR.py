import numpy as np
from pyDICOS import (
    TDR,
    Array1DDcsLongString,
    Array1DPoint3Dfloat,
    Array1DS_UINT16,
    Bitmap,
    DcsLongString,
    Point3Dfloat,
)

from .._dicosio import read_dcs, write_dcs
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
            read_dcs(filename, dcs=self)

    def write(self, filename: str) -> None:
        """Writes the object to a file.

        Parameters
        ----------
        filename : str
            The name of the file to write.
        """
        write_dcs(self, filename=filename)

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
                - ScanStartDateTime : dict, the scan start date and time.
                - ScanType : int, the scan type.
                - ImageScaleRepresentation : int, the image scale representation.
                - ATR : dict, the ATR metadata.
                - PTOs : list, the list of PTOs.
        """
        data = {
            "InstanceNumber": self.GetInstanceNumber(),
            "InstanceUID": self.GetScanInstanceUID().Get(),
            "ScanStartDateTime": DicosDateTime(
                date=self.GetScanStartDate(), time=self.GetScanStartTime()
            ).as_dict(),
            "ProcessingTime": self.GetTotalProcessingTimeInMS(),
            "ScanType": self.GetScanType(),
            "AlarmDecision": self.GetAlarmDecision(),
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
            # TODO: debug the following line
            # self.GetThreatBoundingPolygon(PTOIds[i], polygon, 0)
            data["PTOs"].append(
                {
                    "Base": {"x": PTOBase.x, "y": PTOBase.y, "z": PTOBase.z},
                    "Extent": {"x": PTOExtent.x, "y": PTOExtent.y, "z": PTOExtent.z},
                    "Bitmap": np.array(bitmap.GetBitmap().GetData(), copy=False),
                    "Description": self.GetPTOAssessmentDescription(PTOIds[i], 0).Get(),
                    "Probability": self.GetPTOAssessmentProbability(PTOIds[i], 0),
                    "Polygon": [
                        {"x": polygon[j].x, "y": polygon[j].y, "z": polygon[j].z}
                        for j in range(polygon.GetSize())
                    ],
                    "ID": PTOIds[i],
                }
            )

        return data

    def __len__(self) -> int:
        """Get the number of PTO.

        Returns
        -------
        int
            The number of PTO.
        """
        return self.GetNumPTOs()
