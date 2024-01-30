from pyDICOS import DX
from .TDR import TDRLoader
from .._dicosio import read_dcs, write_dcs
import numpy as np

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

        else:
            self.dx_object = DX()

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