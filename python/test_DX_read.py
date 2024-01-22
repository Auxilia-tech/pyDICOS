from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import DX

import numpy as np

#This class can be utilized to load a DX object by either reading a DX file or using a provided DX object. 
#The 'get_data' function returns 2D NumPy array.
class DXLoader:
    def __init__(self, filename=None, dx_object=None):
        self.height_size = 0
        self.width_size = 0

        if filename is not None and dx_object is not None:
            raise ValueError("Cannot set both filename and DX object simultaneously.")
        
        if filename is not None:
            self.dx_object = DX()
            self.load_file(filename)
        
        elif dx_object is not None:
            self.dx_object = dx_object
            self.load_dx_object()

    def load_file(self, filename):
        errorlog_ = ErrorLog()
        if self.dx_object.Read(Filename(filename), errorlog_, None):
            print("Loaded DX from file")
        else:
            print("Failed to load DX from file") 
            print(errorlog_.GetErrorLog().Get())         
    
    def load_dx_object(self):
        print("Using provided DX object")

    def get_data(self):
        imgPixelData = self.dx_object.GetXRayData()
        vIndexData = imgPixelData.GetUnsigned16()
        array2d = np.array(vIndexData, copy = False)
        return array2d

def main():
    # Example 1: Load DX from a file
    filename = "DXFiles/SimpleProcessingDX.dcs"
    dx_loader_file = DXLoader(filename=filename)
    data = dx_loader_file.get_data()
    print(data)

    # Example 2: Load DX from an existing DX object
    DXObject = DX()
    errorlog_ = ErrorLog()
    if DXObject.Read(Filename("DXFiles/SimpleProcessingDX.dcs"), errorlog_, None):
        dx_loader_object = DXLoader(dx_object=DXObject)
        data = dx_loader_object.get_data()
        print(data)
    else:
        print("Failed to load DX")
        print(errorlog_.GetErrorLog().Get())  

    # Example 1: Load DX from a file
    filename = "DXFiles/SimplePresentationDX.dcs"
    dx_loader_file = DXLoader(filename=filename)
    data = dx_loader_file.get_data()
    print(data)

    # Example 2: Load DX from an existing DX object
    DXObject = DX()
    errorlog_ = ErrorLog()
    if DXObject.Read(Filename("DXFiles/SimplePresentationDX.dcs"), errorlog_, None):
        dx_loader_object = DXLoader(dx_object=DXObject)
        data = dx_loader_object.get_data()
        print(data)
    else:
        print("Failed to load DX")
        print(errorlog_.GetErrorLog().Get())  


    # Example 1: Load DX from a file
    filename = "DXFiles/SimpleColorPaletteDX.dcs"
    dx_loader_file = DXLoader(filename=filename)
    data = dx_loader_file.get_data()
    print(data)

    # Example 2: Load DX from an existing DX object
    DXObject = DX()
    errorlog_ = ErrorLog()
    if DXObject.Read(Filename("DXFiles/SimpleColorPaletteDX.dcs"), errorlog_, None):
        dx_loader_object = DXLoader(dx_object=DXObject)
        data = dx_loader_object.get_data()
        print(data)
    else:
        print("Failed to load DX")
        print(errorlog_.GetErrorLog().Get())  

if __name__ == "__main__":
    main()