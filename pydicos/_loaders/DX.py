import numpy as np
from pyDICOS import DX, ErrorLog, Filename, Volume

from .TDR import TDRLoader


# This class can be utilized to load a DX object by either reading a DX file or using a provided DX object.
# The 'get_data' function returns 2D NumPy array.
class DXLoader(DX):
    def __init__(self, filename: str = None) -> None:
        """Initialize the DXLoader class.

        Parameters
        ----------
        filename : str, optional
            The name of the file to read.
            The default is None and will create an empty DX.
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
