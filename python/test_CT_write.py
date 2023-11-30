from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import CustomMemoryManager
from pyDICOS import Section
from pyDICOS import CT
from pyDICOS import DcsString, DcsLongString
from pyDICOS import MemoryBuffer
from pyDICOS import Array1D_PairBoolMemBuff
from pyDICOS import Vector3Dfloat
from pyDICOS import Volume
from pyDICOS import Array3DLargeS_UINT16
from pyDICOS import Array2DS_UINT16

import numpy as np


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
VecRow = Vector3Dfloat(1, 0, 0)
VecColumn = Vector3Dfloat(0, 1, 0)
SectionObject.SetPlaneOrientation(VecRow, VecColumn)
SectionObject.SetSlicingDirection(True)
volume = SectionObject.GetPixelData()
volume.Allocate(Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit, 128, 129, 100)
#sectionData = volume.GetUnsigned16()

# Create userData array
#userData = np.zeros(volume.GetWidth()  * volume.GetHeight(), dtype=np.uint16)

# Fill userData array
#for i in range(volume.GetSliceSize()):
#    userData[i] = i & 0xFFFF

#for i in range(volume.GetDepth()):
#    xyPlane = sectionData[i]
 #   pBuffer = xyPlane.GetBuffer()

    # The user can copy their data into pBuffer from another source or place it directly in pBuffer.
 #   pBuffer[:, :] = userData[:xyPlane.GetHeight(), :xyPlane.GetWidth()]