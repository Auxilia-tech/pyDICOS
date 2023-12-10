from pyDICOS import Section
from pyDICOS import Filename
from pyDICOS import Folder
from pyDICOS import ErrorLog
from pyDICOS import DX
from pyDICOS import CT
from pyDICOS import Vector3Dfloat
from pyDICOS import Point3Dfloat
from pyDICOS import Array2DS_UINT16
from pyDICOS import Volume
import numpy as np



def CreateDXForProcessingSimple():
    
    dx =  DX(CT.OBJECT_OF_INSPECTION_TYPE.enumTypeCargo,
                DX.PRESENTATION_INTENT_TYPE.enumProcessing,
                DX.PIXEL_DATA_CHARACTERISTICS.enumOriginal,
                CT.PHOTOMETRIC_INTERPRETATION.enumMonochrome2)
    
    width = 256 
    height = 128

    dxData = dx.GetXRayData()
    dxData.Allocate(Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit, width, height)
    rawData = dxData.GetUnsigned16()

    count = 0

    for row in range(dxData.GetHeight()):
        for col in range(dxData.GetWidth()):
            rawData.Set(col, row, count)
            count = count + 1
 
    dx.SetKVP(1)
    dx.SetImageOrientation(Vector3Dfloat(1, 0, 0), Vector3Dfloat(0, 1, 0))
    dx.SetImagePosition(Point3Dfloat(0, 0, 1))
    dx.SetXRayTubeCurrent(2.5)

    errorlog = ErrorLog()
    dxFolder = Folder("DXFiles")
    dxFilename = Filename(dxFolder, "SimpleProcessingDX.dcs") 

    if dx.Write(dxFilename ,errorlog,  CT.TRANSFER_SYNTAX.enumLittleEndianExplicit) != True :
        print("Simple DX Template Example unable to write DICOS File", dxFilename)
        print(errorlog)
        return False
    else:
        print("Wrote file to", dxFilename)
        errorlog = ErrorLog()
        dxRead =  DX()
                
    if dxRead.Read(dxFilename,errorlog, None):
        if dxRead == dx: 
            print("Successfully read and compared DX files")
            return True 
        else:
            print("DX file loaded from", dxFilename, "does not match original.")
            return False
    else:
        print("Unable to read DX file", dxFilename)
        print(errorlog)
        return False

def CreateDXForPresentationSimple():

    dx = DX(CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBioSample,
            DX.PRESENTATION_INTENT_TYPE.enumPresentation,
            DX.PIXEL_DATA_CHARACTERISTICS.enumOriginal,
            CT.PHOTOMETRIC_INTERPRETATION.enumMonochrome2)
    
    width = 256 
    height = 128

    dxData = dx.GetXRayData()
    dxData.Allocate(Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit, width, height)
    rawData = dxData.GetUnsigned16()

    count = 0
 
    for row in range(dxData.GetHeight()):
        for col in range(dxData.GetWidth()):
            rawData.Set(col, row, count)
            count = count + 1
       
    dx.SetWindowCenterAndWidth(1234, 500)
    windowCenter = 0
    windowWidth = 0
    result, windowCenter, windowWidth = dx.GetWindowCenterAndWidth(windowCenter,windowWidth)
    print(windowCenter, windowWidth)
    

def main():
    CreateDXForProcessingSimple()
    CreateDXForPresentationSimple()

if __name__ == "__main__":
    main()