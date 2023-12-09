from pyDICOS import Section
from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import DX
from pyDICOS import CT
from pyDICOS import Array1DS_UINT16
from pyDICOS import Array1DPairBoolMemBuff
from pyDICOS import Array3DLargeS_UINT16
from pyDICOS import Volume
import numpy as np



def CreateDXForProcessingSimple() :
    
    DXObject =  DX(CT.OBJECT_OF_INSPECTION_TYPE.enumTypeCargo,
                DX.PRESENTATION_INTENT_TYPE.enumProcessing,
                DX.PIXEL_DATA_CHARACTERISTICS.enumOriginal,
                CT.PHOTOMETRIC_INTERPRETATION.enumMonochrome2)
    
    width = 256 
    height = 128

    SDICOS::Image2D& dxData = dx.GetXRayData();
        dxData.Allocate(SDICOS::Image2D::enumUnsigned16Bit, width,height)
 