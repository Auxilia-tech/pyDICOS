from pyDICOS import Section
from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import DX
from pyDICOS import CT
from pyDICOS import Vector3Dfloat
from pyDICOS import Point3Dfloat
from pyDICOS import Array2DS_UINT16
from pyDICOS import Volume
import numpy as np



def CreateDXForProcessingSimple():
    
    DXObject =  DX(CT.OBJECT_OF_INSPECTION_TYPE.enumTypeCargo,
                DX.PRESENTATION_INTENT_TYPE.enumProcessing,
                DX.PIXEL_DATA_CHARACTERISTICS.enumOriginal,
                CT.PHOTOMETRIC_INTERPRETATION.enumMonochrome2)
    
    width = 256 
    height = 128

    dxData = DXObject.GetXRayData()
    dxData.Allocate(Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit, width, height)
    rawData = dxData.GetUnsigned16()

    count = 0

    for row in range(dxData.GetHeight()):
        for col in range(dxData.GetWidth()):
            rawData.Set(col, row, count)
            count = count + 1
 
    DXObject.SetKVP(1)
    DXObject.SetImageOrientation(Vector3Dfloat(1, 0, 0), Vector3Dfloat(0, 1, 0))
    DXObject.SetImagePosition(Point3Dfloat(0, 0, 1))
    DXObject.SetXRayTubeCurrent(2.5)

def main():
    CreateDXForProcessingSimple()

if __name__ == "__main__":
    main()