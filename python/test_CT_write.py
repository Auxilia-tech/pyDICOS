from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import CustomMemoryManager
from pyDICOS import Section
from pyDICOS import CT
from pyDICOS import DcsString, DcsLongString
from pyDICOS import MemoryBuffer
from pyDICOS import Array1D

import numpy


CTObject = CT(CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBaggage,
              CT.OOI_IMAGE_CHARACTERISTICS.enumHighEnergy,
              CT.IMAGE_FLAVOR.enumVolume,
              CT.PHOTOMETRIC_INTERPRETATION.enumMonochrome2)

CTObject.SetImageAcquisitionDuration(5.2)
DCS = DcsLongString("HIGH ENERGY SCAN")
CTObject.SetScanDescription(DCS)
CTObject.SetNumberOfSections(1)

SectionObject = Section()
SectionObject = CTObject.GetSectionByIndex(0)
SectionObject.SetFocalSpotSizeInMM(1.414)
print(SectionObject.GetFocalSpotSize())

