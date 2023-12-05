from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import CustomMemoryManager
from pyDICOS import Section
from pyDICOS import CT
from pyDICOS import DcsString, DcsLongString
from pyDICOS import MemoryBuffer
from pyDICOS import Array1DS_UINT16
from pyDICOS import Array1DArray2DS_UINT16
from pyDICOS import Array1DPairBoolMemBuff
from pyDICOS import Array2DS_UINT16
from pyDICOS import Vector3Dfloat
from pyDICOS import Volume
from pyDICOS import Array3DLargeS_UINT16

import numpy as np
import ctypes


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
sectionData = volume.GetUnsigned16()
# Create userData array
userData = np.zeros(volume.GetWidth() * volume.GetHeight(), dtype=np.uint16)

# Fill userData array
for i in range(volume.GetSliceSize()):
    userData[i] = i & 0xFFFF



for i in range(volume.GetDepth()):
     xyPlane = sectionData[i]
     pBuffer = xyPlane.GetBuffer()
     size_of_data = ctypes.sizeof(ctypes.c_uint16) * xyPlane.GetWidth() * xyPlane.GetHeight()

    # Create a ctypes array from the userData
     data_array = (ctypes.c_uint16 * (xyPlane.GetWidth() * xyPlane.GetHeight())).from_buffer(userData)

    # Copy the data to pBuffer
     for j in range(1, xyPlane.GetHeight()):
        for k in range(1, xyPlane.GetWidth()):
            xyPlane.Set(j, k, userData[k + j * xyPlane.GetWidth()])
            #print('(', j, ', ', k,')' , xyPlane.Get(j, k))

slice_count = 0
b_res = True

volume_iterator = volume.Begin()
while volume_iterator != volume.End():
    cur_slice = volume_iterator.AsUnsigned16()
    cur_slice.Zero(slice_count)
    b_res = (cur_slice.GetWidth() == 128) and (cur_slice.GetHeight() == 129) and b_res
    print(b_res)
    next(volume_iterator)
    print(volume_iterator)
    print(slice_count)
    slice_count += 1

if slice_count != 100 or not b_res:
    print("UserCTExample CreateCTSimple failed to verify slice count using iterator. ", b_res)