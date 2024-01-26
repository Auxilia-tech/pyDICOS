from pyDICOS import CT, DX, Volume
from ._dicosio import read_dcs, write_dcs
import numpy as np


# This class can be utilized to load a CT object by either reading a CT file or using a provided CT object.
# The 'get_data' function returns a list of 2D NumPy arrays.
class CTLoader:
    def __init__(self, filename: str = None, ct_object: CT = None):
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

    def get_data(self):
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
                    for j in range(xyPlane.GetHeight()):
                        for k in range(xyPlane.GetWidth()):
                            data_array[i, j, k] = xyPlane.Get(j, k)
                data_arrays.append(data_array)
            next(sectionIt)
            sectionCount += 1
        return data_arrays


# This class can be utilized to load a DX object by either reading a DX file or using a provided DX object.
# The 'get_data' function returns 2D NumPy array.
class DXLoader:
    def __init__(self, filename: str = None, dx_object: DX = None):
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

    def get_data(self):
        imgPixelData = self.dx_object.GetXRayData()
        vIndexData = imgPixelData.GetUnsigned16()
        array2d = np.array(vIndexData, copy=False)
        return array2d
