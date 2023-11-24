from pyDICOS import Section
from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import CustomMemoryManager
from pyDICOS import CT
from pyDICOS import DcsString
from pyDICOS import MemoryBuffer
from pyDICOS import Array1D
#from pyDICOS import *
import numpy


CTObject = CT(CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBaggage,
              CT.OOI_IMAGE_CHARACTERISTICS.enumHighEnergy,
              CT.IMAGE_FLAVOR.enumVolume,
              CT.PHOTOMETRIC_INTERPRETATION.enumMonochrome2)

CTObject.SetImageAcquisitionDuration(5.2)
CTObject.SetScanDescription("HIGH ENERGY SCAN")



