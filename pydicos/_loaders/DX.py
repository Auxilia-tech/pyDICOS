from pyDICOS import DX
from .TDR import TDRLoader
from .._dicosio import read_dcs, write_dcs
import numpy as np

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
            read_dcs(filename, dcs=self)

    def write(self, filename :str) -> None:
        """Writes the object to a file.

        Parameters
        ----------
        filename : str
            The name of the file to write.
        """
        write_dcs(self, filename=filename)

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