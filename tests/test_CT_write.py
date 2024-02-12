import numpy as np
from pyDICOS import (
    CT,
    Array3DLargeS_UINT16,
    DcsLongString,
    ErrorLog,
    Filename,
    Folder,
    Point3DS_UINT16,
    Section,
    Vector3Dfloat,
    Volume,
)


def GenerateCTSection(ct):
    ct.SetNumberOfSections(1)
    SectionObject = ct.GetSectionByIndex(0)
    # The FILTER_MATERIAL enumeration is situated in the binding code of the Section Module.
    SectionObject.SetFilterMaterial(Section.FILTER_MATERIAL.enumAluminum)
    SectionObject.SetFocalSpotSizeInMM(10)
    SectionObject.SetKVP(7000)
    assert ct.GetNumberOfSections() == 1

    # float in Vector3Dfloat means that the type of the components of Vector3D is float"
    # the supported types of Vector3D are : S_UINT8, S_INT8, S_UINT16, S_INT16, float
    VecRowOrientation = Vector3Dfloat(1, 0, 0)
    VecColumnOrientation = Vector3Dfloat(0, 1, 0)
    SectionObject.SetPlaneOrientation(VecRowOrientation, VecColumnOrientation)
    SectionObject.SetPositionInMM(-125, -125, 125)

    fColumnSpacing = 1.0
    fRowSpacing = 1.0
    fSliceSpacing = 1.0
    fSliceThickness = 1.0

    SectionObject.SetSpacingInMM(fColumnSpacing, fRowSpacing, fSliceSpacing)
    SectionObject.SetSliceThickness(fSliceThickness)

    volume = SectionObject.GetPixelData()
    # The IMAGE_DATA_TYPE enumeration is situated in the binding code of the Volume Module.
    volume.Allocate(Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit, 256, 256, 256)
    Array3Dlarge = volume.GetUnsigned16()
    Array3Dlarge.Zero(0)

    # S_UINT16 in Point3DS_UINT16 means that the type of the components of Point3D is S_UINT16"
    # the supported types of Point3D are : S_UINT8, S_INT8, S_UINT16, S_INT16, float
    ptCenter = Point3DS_UINT16(125, 125, 125)

    nWhite = 0xFFFF
    nGray256 = 0x0100
    nGray2048 = 0x1000
    ptPos = Point3DS_UINT16()

    curSlice = 0

    for ptPos.z in range(200):
        pSlice = Array3Dlarge.GetSlice(curSlice)

        for ptPos.y in range(20):
            for ptPos.x in range(50):
                pSlice.Set(ptPos.y, ptPos.x, nWhite)
        curSlice += 1

    curSlice = 0
    for ptPos.z in range(ptCenter.z - 40, ptCenter.z + 40):
        pSlice = Array3Dlarge.GetSlice(curSlice)
        for ptPos.y in range(ptCenter.y - 40, ptCenter.y + 40):
            for ptPos.x in range(ptCenter.x - 40, ptCenter.x + 40):
                pSlice.Set(ptPos.y, ptPos.x, nGray256)
        curSlice += 1

    curSlice = 0
    for ptPos.z in range(ptCenter.z - 5, ptCenter.z + 5):
        pSlice = Array3Dlarge.GetSlice(curSlice)
        for ptPos.y in range(ptCenter.y - 5, ptCenter.y + 5):
            for ptPos.x in range(ptCenter.x + 41, ptCenter.x + 51):
                pSlice.Set(ptPos.y, ptPos.x, nGray2048)
        curSlice += 1

    return ct


def test_create_ct_files(session_cleanup):
    # The OBJECT_OF_INSPECTION_TYPE enumeration is situated in the binding code of the CT Module.
    # The OOI_IMAGE_CHARACTERISTICS enumeration is situated in the binding code of the CT Module.
    # The IMAGE_FLAVOR enumeration is situated in the binding code of the CT Module.
    # The PHOTOMETRIC_INTERPRETATION enumeration is situated in the binding code of the CT Module.
    CTObject = CT(
        CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBaggage,
        CT.OOI_IMAGE_CHARACTERISTICS.enumHighEnergy,
        CT.IMAGE_FLAVOR.enumVolume,
        CT.PHOTOMETRIC_INTERPRETATION.enumMonochrome2,
    )

    CTObject.SetImageAcquisitionDuration(5.2)
    DCS = DcsLongString("HIGH ENERGY SCAN")
    CTObject.SetScanDescription(DCS)
    CTObject.SetNumberOfSections(1)

    SectionObject = CTObject.GetSectionByIndex(0)
    SectionObject.SetFocalSpotSizeInMM(1.414)
    VecRow = Vector3Dfloat(1, 0, 0)
    VecColumn = Vector3Dfloat(0, 1, 0)
    SectionObject.SetPlaneOrientation(VecRow, VecColumn)
    SectionObject.SetSlicingDirection(True)
    volume = SectionObject.GetPixelData()
    volume.Allocate(Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit, 128, 129, 100)
    sectionData = volume.GetUnsigned16()

    userData = np.zeros(volume.GetWidth() * volume.GetHeight(), dtype=np.uint16)

    for i in range(volume.GetSliceSize()):
        userData[i] = i & 0xFFFF

    for i in range(volume.GetDepth()):
        xyPlane = sectionData[i]
        for j in range(1, xyPlane.GetHeight()):
            for k in range(1, xyPlane.GetWidth()):
                xyPlane.Set(j, k, userData[k + j * xyPlane.GetWidth()])

    slice_count = 0
    b_res = True

    volume_iterator = volume.Begin()
    while volume_iterator != volume.End():
        cur_slice = volume_iterator.AsUnsigned16()
        cur_slice.Zero(slice_count)
        b_res = (
            (cur_slice.GetWidth() == 128) and (cur_slice.GetHeight() == 129) and b_res
        )
        # we used next to increment the volume_iterator
        next(volume_iterator)
        slice_count += 1

    assert slice_count == 100 or not b_res, (
        "UserCTExample CreateCTSimple failed to verify slice count using iterator. "
        "Expected 100, got " + str(slice_count)
    )

    CTObject = GenerateCTSection(CTObject)
    totalSliceCount = CTObject.GetSectionByIndex(0).GetDepth()
    assert totalSliceCount == 256

    # S_UINT16 in Array3DLargeS_UINT16 means that the type of the components of Array3DLarge is S_UINT16"
    # the supported types of Array3DLarge are : S_UINT8, S_INT8, S_UINT16, S_INT16, float
    # The VOLUME_MEMORY_POLICY enumeration is situated in the binding code of the CT Module.
    vUnsigned16bitData = Array3DLargeS_UINT16(
        10, 20, 40, CT.VOLUME_MEMORY_POLICY.OWNS_SLICES
    )
    vUnsigned16bitData.Zero(0xBEEF)

    pSection2 = CTObject.AddSection(
        vUnsigned16bitData, CT.VOLUME_MEMORY_POLICY.DOES_NOT_OWN_SLICES
    )
    b_res = pSection2 is not None and b_res
    assert b_res
    totalSliceCount += pSection2.GetDepth()
    assert totalSliceCount == 296

    sectionIt = CTObject.Begin()
    sectionCount = 0
    slice_count = 0
    while sectionIt != CTObject.End():
        # get the section from CTObject iterator
        pSection = sectionIt.deref()
        pixel_data_type = pSection.GetPixelDataType()
        if Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit == pixel_data_type:
            volume_iterator = pSection.GetPixelData().Begin()
            while volume_iterator != pSection.GetPixelData().End():
                cur_slice = volume_iterator.AsUnsigned16()
                b_res = (cur_slice is not None) and b_res
                next(volume_iterator)
                slice_count += 1
        next(sectionIt)
        sectionCount += 1

    b_res = (0 != sectionCount) and b_res
    assert (
        (sectionCount == 2) and (slice_count == totalSliceCount)
    ), "UserCTExample CreateCTSimple failed to verify sections and slices using iterator"

    errorlog = ErrorLog()
    ctFolder = Folder("SimpleCT")
    ctFilename = Filename(ctFolder, "SimpleCT.dcs")
    session_cleanup.append("SimpleCT")

    # The TRANSFER_SYNTAX enumeration is situated in the binding code of the CT Module.
    assert CTObject.Write(
        ctFilename, errorlog, CT.TRANSFER_SYNTAX.enumLittleEndianExplicit
    ), f"UserCTExample CreateCTSimple unable to write DICOS File {ctFilename}\n{errorlog.GetErrorLog().Get()}"

    CTObject_c0 = CT()
    errorlog_c0 = ErrorLog()
    filename_c0 = Filename("SimpleCT/SimpleCT0000.dcs")
    # You should set 'None' for the unused argument of the 'Read' function.
    if CTObject_c0.Read(filename_c0, errorlog_c0, None):
        section_size_c0 = CTObject_c0.GetNumberOfSections()
        depth_size_c0 = 0
        height_size_c0 = 0
        width_size_c0 = 0

        sectionIt_c0 = CTObject_c0.Begin()
        while sectionIt_c0 != CTObject_c0.End():
            pSection_c0 = sectionIt_c0.deref()
            pixel_data_type_c0 = pSection_c0.GetPixelDataType()

            if Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit == pixel_data_type_c0:
                volume_c0 = pSection_c0.GetPixelData()
                depth_size_c0 = volume_c0.GetDepth()
                xyPlane_c0 = volume_c0.GetUnsigned16()
                height_size_c0 = xyPlane_c0.GetHeight()
                width_size_c0 = xyPlane_c0.GetWidth()

            next(sectionIt_c0)
    else:
        raise RuntimeError(
            f"Failed to load SimpleCT0000 \n{errorlog_c0.GetErrorLog().Get()}"
        )

    CTObject_c1 = CT()
    errorlog_c1 = ErrorLog()
    filename_c1 = Filename("SimpleCT/SimpleCT0001.dcs")

    # You should set 'None' for the unused argument of the 'Read' function.
    if CTObject_c1.Read(filename_c1, errorlog_c1, None):
        sectionIt_c1 = CTObject_c1.Begin()
        section_size_c1 = CTObject_c1.GetNumberOfSections()
        depth_size_c1 = 0
        height_size_c1 = 0
        width_size_c1 = 0

        sectionIt_c1 = CTObject_c1.Begin()
        while sectionIt_c1 != CTObject_c1.End():
            pSection_c1 = sectionIt_c1.deref()
            pixel_data_type_c1 = pSection_c1.GetPixelDataType()

            if Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit == pixel_data_type_c1:
                volume_c1 = pSection_c1.GetPixelData()
                depth_size_c1 = volume_c1.GetDepth()
                xyPlane_c1 = volume_c1.GetUnsigned16()
                height_size_c1 = xyPlane_c1.GetHeight()
                width_size_c1 = xyPlane_c1.GetWidth()

            next(sectionIt_c1)
    else:
        raise RuntimeError(
            f"Failed to load SimpleCT0001 \n{errorlog_c1.GetErrorLog().Get()}"
        )

    print(
        "Depth ",
        depth_size_c0,
        "Height ",
        height_size_c0,
        "Width ",
        width_size_c0,
        "NB_Sections",
        section_size_c0,
    )
    print(
        "Depth ",
        depth_size_c1,
        "Height ",
        height_size_c1,
        "Width ",
        width_size_c1,
        "NB_Sections",
        section_size_c1,
    )

    assert (
        depth_size_c0 == 40
        and height_size_c0 == 20
        and width_size_c0 == 10
        and section_size_c0 == 1
    ), "Simple CT Example original CT and read SimpleCT0000 are not equal"

    assert (
        depth_size_c1 == 256
        and height_size_c1 == 256
        and width_size_c1 == 256
        and section_size_c1 == 1
    ), "Simple CT Example original CT and read SimpleCT0001 are not equal"


if __name__ == "__main__":
    test_create_ct_files()
