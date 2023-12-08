from pyDICOS import Section
from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import CustomMemoryManager
from pyDICOS import CT
from pyDICOS import DcsString
from pyDICOS import MemoryBuffer
from pyDICOS import Array1DS_UINT16
from pyDICOS import Array1DPairBoolMemBuff
from pyDICOS import Array3DLargeS_UINT16
from pyDICOS import Volume
import numpy as np

np.set_printoptions(suppress=True, formatter={'float_kind':'{:0.2f}'.format}) 

CTObject = CT()
filename_ = Filename("SimpleCT/SimpleCT0000.dcs")
print(filename_.GetFullPath())
errorlog_ = ErrorLog()

if CTObject.Read(filename_, errorlog_, None):
    print("Loaded CT")
    sectionIt = CTObject.Begin()
    sectionCount = 0
    slice_count = 0
    b_res = True
    section_size = CTObject.GetNumberOfSections()
    depth_size = 0
    height_size = 0
    width_size = 0

    sectionIt = CTObject.Begin()
    while sectionIt != CTObject.End():
        pSection = sectionIt.deref()
        pixel_data_type = pSection.GetPixelDataType()

        if Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit == pixel_data_type:
            volume = pSection.GetPixelData()

            if volume.GetDepth() > depth_size:
                depth_size = volume.GetDepth()

            xyPlane = volume.GetUnsigned16()
            if xyPlane.GetHeight() > height_size:
                height_size = xyPlane.GetHeight()
            if xyPlane.GetWidth() > width_size:
                width_size = xyPlane.GetWidth()

        next(sectionIt)

    data_array = np.zeros((section_size, depth_size, height_size, width_size), dtype=np.uint16)
    
    sectionIt = CTObject.Begin()
    while sectionIt != CTObject.End():
        pSection = sectionIt.deref()
        pixel_data_type = pSection.GetPixelDataType()
        if Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit == pixel_data_type:
            volume_iterator = pSection.GetPixelData().Begin()
            while volume_iterator != pSection.GetPixelData().End():
                volume = pSection.GetPixelData()
                sectionData = volume.GetUnsigned16()
                for i in range(volume.GetDepth()):
                    xyPlane = sectionData[i]
                    for j in range(1, xyPlane.GetHeight()):
                        for k in range(1, xyPlane.GetWidth()):
                            #print('(', i, ',', j, ', ', k,')', xyPlane.Get(j, k), '|', 'Depth ', volume.GetDepth(), 'Height ', xyPlane.GetHeight(),  'Width ', xyPlane.GetWidth())
                            data_array[sectionCount, i, j, k] = xyPlane.Get(j, k)
                cur_slice = volume_iterator.AsUnsigned16()
                b_res = (cur_slice is not None) and b_res
                print('b_Res  ', b_res, '  sliceCount  ', slice_count, '  sectionCount  ', sectionCount)
                next(volume_iterator)
                slice_count += 1
        next(sectionIt)
        sectionCount += 1
else:
    print("Failed to load CT")