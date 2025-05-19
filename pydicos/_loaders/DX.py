import numpy as np
from pathlib import Path
from pyDICOS import DX, ErrorLog, Filename, Volume
from typing import Optional, Union

from .TDR import TDRLoader
from ..metadata import (
    DXMetadata,
    DateTimeMetadata
)


# This class can be utilized to load a DX object by either reading a DX file or using a provided DX object.
# The 'get_data' function returns 2D NumPy array.
class DXLoader(DX):
    def __init__(self, filename: Optional[Union[str, Path]] = None) -> None:
        """Initialize the DXLoader class.

        Parameters
        ----------
        filename : str|Path, optional
            The name of the file to read.
            The default is None and will create an empty DX.
        """
        super().__init__()
        self._metadata: Optional[DXMetadata] = None

        if filename is not None:
            self.read(filename)

    @property
    def metadata(self) -> DXMetadata:
        """Get the DX metadata.

        Returns
        -------
        DXMetadata
            The DX metadata.
        """
        if self._metadata is None:
            self._metadata = self._load_metadata()
        return self._metadata

    def _load_metadata(self) -> DXMetadata:
        """Load the DX metadata from the DX object.

        Returns
        -------
        DXMetadata
            The DX metadata.
        """
        content_date = self.GetContentDate()
        content_time = self.GetContentTime()

        return DXMetadata(
            instance_number=self.GetInstanceNumber(),
            instance_uid=self.GetScanInstanceUID().Get(),
            series_instance_uid=self.GetSeriesInstanceUID().Get(),
            frame_of_reference_uid=self.GetFrameOfReferenceUID().Get(),
            ooi_id=self.GetOOIID().Get(),
            ooi_type=self.GetOOIType(),
            content_date_time=DateTimeMetadata(
                date=(content_date.GetYear(), content_date.GetMonth(), content_date.GetDay()),
                time=(content_time.GetHour(), content_time.GetMinute(), content_time.GetSecond(), content_time.GetMicrosecond())
            ),
            sop_class_uid=self.GetSopClassUID().Get()
        )

    def read(self, filename: Union[str, Path]) -> None:
        """Reads the object from a file.

        Parameters
        ----------
        filename : str|Path
            The name of the file to read.
        """
        _err = ErrorLog()
        if not self.Read(Filename(str(filename)), _err, None):
            raise RuntimeError(
            f"Failed to read DICOS file: {filename}\n{_err.GetErrorLog().Get()}"
        )
        self._metadata = None  # Reset metadata cache

    def write(self, filename: Union[str, Path]) -> None:
        """Writes the object to a file.

        Parameters
        ----------
        filename : str|Path
            The name of the file to write.
        """
        _err = ErrorLog()
        if not self.Write(Filename(str(filename)), _err):
            raise RuntimeError(
            f"Failed to write DICOS file: {filename}\n{_err.GetErrorLog().Get()}"
        )

    def get_data(self) -> np.ndarray:
        """Get the data from the DX object.

        Returns
        -------
        data_array : numpy.ndarray
            A 2D NumPy array.
        """
        imgPixelData = self.GetXRayData()
        vIndexData = imgPixelData.GetUnsigned16()
        return np.array(vIndexData, copy=False)
    
    def set_data(self, data: np.ndarray) -> None:
        """Set the data in the DX object.

        Parameters
        ----------
        data : numpy.ndarray
            A 2D NumPy array.
        """
        assert data.ndim == 2, "Data must be 2D"
        assert data.dtype == np.uint16, "Data must be uint16"
        width, height = data.shape

        dxData = self.GetXRayData()
        dxData.Allocate(Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit, height, width)
        rawData = dxData.GetUnsigned16()

        for row in range(height):
            for col in range(width):
                rawData.Set(row, col, data[col, row])

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
