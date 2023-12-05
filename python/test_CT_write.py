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
from pyDICOS import Point3DS_UINT16

import numpy as np
import ctypes

def GenerateCTSection(ct):
    SectionObject = Section()
    ct.SetNumberOfSections(1)
    SectionObject = ct.GetSectionByIndex(0)
    SectionObject.SetFilterMaterial(Section.FILTER_MATERIAL.enumAluminum)
    SectionObject.SetFocalSpotSizeInMM(10)
    SectionObject.SetKVP(7000)

    VecRowOrientation = Vector3Dfloat(1, 0, 0)
    VecColumnOrientation = Vector3Dfloat(0, 1, 0)
    SectionObject.SetPlaneOrientation(VecRow, VecColumn)
    SectionObject.SetPositionInMM(-125,-125,125)

    fColumnSpacing = 1.0
    fRowSpacing = 1.0
    fSliceSpacing = 1.0
    fSliceThickness = 1.0 

    SectionObject.SetSpacingInMM(fColumnSpacing, fRowSpacing, fSliceSpacing)
    SectionObject.SetSliceThickness(fSliceThickness)
    volume = SectionObject.GetPixelData()
    volume.Allocate(Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit, 256, 256, 256)
    Array3Dlarge = volume.GetUnsigned16()
    Array3Dlarge.Zero(0)

    ptCenter = Point3DS_UINT16(125,125,125)

    nWhite = 0xFFFF
    nGray256 = 0x0100
    nGray2048 = 0x1000
    ptPos = Point3DS_UINT16()

    curSlice = 0

    for ptPos.z in range(200):
        pSlice = Array3Dlarge.GetSlice(ptPos.z) #SDICOS::Array2D<SDICOS::S_UINT16>* pSlice

        for ptPos.y in range(20):
            for ptPos.x in range(50):
                 pSlice.Set(ptPos.y, ptPos.x , nWhite)
        curSlice += 1

    curSlice = 0
    for ptPos.z in range(ptCenter.z - 40, ptCenter.z + 40):
        pSlice = Array3Dlarge.GetSlice(ptPos.z) #SDICOS::Array2D<SDICOS::S_UINT16>* pSlice
        for ptPos.y in range(ptCenter.y - 40, ptCenter.y + 40):
            for ptPos.x in range(ptCenter.x - 40, ptCenter.x + 40):
                pSlice.Set(ptPos.y, ptPos.x , nGray256)
        curSlice += 1

    curSlice = 0
    for ptPos.z in range(ptCenter.z - 5, ptCenter.z + 5):
        pSlice = Array3Dlarge.GetSlice(ptPos.z) #SDICOS::Array2D<SDICOS::S_UINT16>* pSlice
        for ptPos.y in range(ptCenter.y - 5, ptCenter.y + 5):
            for ptPos.x in range(ptCenter.x - 5, ptCenter.x + 5):
                pSlice.Set(ptPos.y, ptPos.x , nGray2048)
        curSlice += 1

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
    #print(b_res)
    next(volume_iterator)
    #print(slice_count)
    slice_count += 1

if slice_count != 100 or not b_res:
    print("UserCTExample CreateCTSimple failed to verify slice count using iterator. ", b_res)

GenerateCTSection(CTObject)