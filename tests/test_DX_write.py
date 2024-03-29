import math

import numpy as np
from pyDICOS import (
    CT,
    DX,
    Array1DS_UINT16,
    DcsLongString,
    ErrorLog,
    Filename,
    Folder,
    Point3Dfloat,
    Vector3Dfloat,
    Volume,
)


def test_create_dx_processing(session_cleanup):
    # The OBJECT_OF_INSPECTION_TYPE enumeration is situated in the binding code of the CT Module.
    # The PRESENTATION_INTENT_TYPE enumeration is situated in the binding code of the DX Module.
    # The PIXEL_DATA_CHARACTERISTICS enumeration is situated in the binding code of the DX Module.
    # The PHOTOMETRIC_INTERPRETATION enumeration is situated in the binding code of the CT Module.
    dx = DX(
        CT.OBJECT_OF_INSPECTION_TYPE.enumTypeCargo,
        DX.PRESENTATION_INTENT_TYPE.enumProcessing,
        DX.PIXEL_DATA_CHARACTERISTICS.enumOriginal,
        CT.PHOTOMETRIC_INTERPRETATION.enumMonochrome2,
    )

    width = 256
    height = 128

    dxData = dx.GetXRayData()
    # The IMAGE_DATA_TYPE enumeration is situated in the binding code of the Volume Module.
    dxData.Allocate(Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit, width, height)
    rawData = dxData.GetUnsigned16()

    count = 0
    for row in range(dxData.GetHeight()):
        for col in range(dxData.GetWidth()):
            rawData.Set(col, row, count)
            count = count + 1

    dx.SetKVP(1)
    # float in Vector3Dfloat means that the type of the components of Vector3D is float"
    # the supported types of Vector3D are : S_UINT8, S_INT8, S_UINT16, S_INT16, float
    dx.SetImageOrientation(Vector3Dfloat(1, 0, 0), Vector3Dfloat(0, 1, 0))
    # float in Point3Dfloat means that the type of the components of Point3D is float"
    # the supported types of Point3D are : S_UINT8, S_INT8, S_UINT16, S_INT16, float
    dx.SetImagePosition(Point3Dfloat(0, 0, 1))
    dx.SetXRayTubeCurrent(2.5)

    errorlog = ErrorLog()
    dxFolder = Folder("DXFiles")
    dxFilename = Filename(dxFolder, "SimpleProcessingDX.dcs")
    session_cleanup.append("DXFiles")

    # The TRANSFER_SYNTAX enumeration is situated in the binding code of the CT Module.
    assert dx.Write(
        dxFilename, errorlog, CT.TRANSFER_SYNTAX.enumLittleEndianExplicit
    ), f"Simple DX Template Example unable to write DICOS File {dxFilename}\n{errorlog.GetErrorLog().Get()}"

    errorlog = ErrorLog()
    dxRead = DX()
    # You should set 'None' for the unused argument of the 'Read' function.
    assert dxRead.Read(
        dxFilename, errorlog, None
    ), f"Unable to read DX file {dxFilename}\n{errorlog.GetErrorLog().Get()}"
    assert (
        dxRead == dx
    ), f"DX file loaded from {dxFilename} does not match original.\n{errorlog.GetErrorLog().Get()}"


def test_create_dx_presentation(session_cleanup):
    # The OBJECT_OF_INSPECTION_TYPE enumeration is situated in the binding code of the CT Module.
    # The PRESENTATION_INTENT_TYPE enumeration is situated in the binding code of the DX Module.
    # The PIXEL_DATA_CHARACTERISTICS enumeration is situated in the binding code of the DX Module.
    # The PHOTOMETRIC_INTERPRETATION enumeration is situated in the binding code of the CT Module.
    dx = DX(
        CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBioSample,
        DX.PRESENTATION_INTENT_TYPE.enumPresentation,
        DX.PIXEL_DATA_CHARACTERISTICS.enumOriginal,
        CT.PHOTOMETRIC_INTERPRETATION.enumMonochrome2,
    )

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
    result, windowCenter, windowWidth = dx.GetWindowCenterAndWidth(
        windowCenter, windowWidth
    )
    assert (
        windowCenter == 1234 and windowWidth == 500
    ), "Window Center and Width do not match"

    dx.SetWindowCenterAndWidthExplanation(
        DcsLongString("Window Center and Width for test screen")
    )

    # float in Array1DS_UINT16 means that the type of the elements of Array1D is float"
    # the supported types of Array1D are : S_UINT8, S_INT8, S_UINT16, S_INT16, float
    lut = Array1DS_UINT16()
    lutSize = 512
    lutMinValue = 1000
    lut.SetSize(lutSize, False)

    buff = np.array(lut, copy=False)
    for i in range(lutSize):
        buff[i] = lutMinValue + (math.sqrt(i))

    firstValueMapped = 2000
    dx.SetLUTData(lut, firstValueMapped)

    dx.SetKVP(1.0)
    dx.SetImageOrientation(Vector3Dfloat(1, 0, 0), Vector3Dfloat(0, 1, 0))
    dx.SetImagePosition(Point3Dfloat(0, 0, 1))
    dx.SetXRayTubeCurrent(2.5)

    errorlog = ErrorLog()
    dxFolder = Folder("DXFiles")
    dxFilename = Filename(dxFolder, "SimplePresentationDX.dcs")
    session_cleanup.append("DXFiles")

    assert dx.Write(
        dxFilename, errorlog
    ), f"Simple DX Template Example unable to write DICOS File {dxFilename}\n{errorlog.GetErrorLog().Get()}"

    errorlog = ErrorLog()
    dxRead = DX()
    # You should set 'None' for the unused argument of the 'Read' function.
    assert dxRead.Read(
        dxFilename, errorlog, None
    ), f"Unable to read DX file {dxFilename}\n{errorlog.GetErrorLog().Get()}"
    assert (
        dxRead == dx
    ), f"DX file loaded from {dxFilename} does not match original.\n{errorlog.GetErrorLog().Get()}"


def test_create_dx_palette(session_cleanup):
    # The OBJECT_OF_INSPECTION_TYPE enumeration is situated in the binding code of the CT Module.
    # The PRESENTATION_INTENT_TYPE enumeration is situated in the binding code of the DX Module.
    # The PIXEL_DATA_CHARACTERISTICS enumeration is situated in the binding code of the DX Module.
    # The PHOTOMETRIC_INTERPRETATION enumeration is situated in the binding code of the CT Module.
    dx = DX(
        CT.OBJECT_OF_INSPECTION_TYPE.enumTypeCargo,
        DX.PRESENTATION_INTENT_TYPE.enumProcessing,
        DX.PIXEL_DATA_CHARACTERISTICS.enumOriginal,
        CT.PHOTOMETRIC_INTERPRETATION.enumPaletteColor,
    )
    # The PRESENTATION_LUT_SHAPE enumeration is situated in the binding code of the DX Module.
    assert dx.SetPresentationLUTShape(
        DX.PRESENTATION_LUT_SHAPE.enumIdentity
    ), "Invalid Presentation LUT Shape"

    nWidth = 256
    nHeight = 128

    vRed = dx.GetRedLUT()
    vGreen = dx.GetGreenLUT()
    vBlue = dx.GetBlueLUT()

    vRed.SetSize(nHeight, False)
    vGreen.SetSize(nHeight, False)
    vBlue.SetSize(nHeight, False)

    pnRed = np.array(vRed, copy=False)
    pnGreen = np.array(vGreen, copy=False)
    pnBlue = np.array(vBlue, copy=False)

    nColor = 0
    for nIndex in range(nHeight):
        pnRed[nIndex] = nColor
        pnGreen[nIndex] = nColor / 2
        pnBlue[nIndex] = nColor
        nColor = nColor + 1

    imgPixelData = dx.GetXRayData()
    imgPixelData.Allocate(Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit, nWidth, nHeight)
    vIndexData = imgPixelData.GetUnsigned16()

    array2d = np.array(vIndexData, copy=False)
    for row in range(imgPixelData.GetHeight()):
        for col in range(imgPixelData.GetWidth()):
            array2d[row, col] = row

    dx.SetKVP(1.0)
    dx.SetImageOrientation(Vector3Dfloat(1, 0, 0), Vector3Dfloat(0, 1, 0))
    dx.SetImagePosition(Point3Dfloat(0, 0, 1))
    dx.SetXRayTubeCurrent(2.5)

    errorlog = ErrorLog()
    dxFolder = Folder("DXFiles")
    dxFilename = Filename(dxFolder, "SimpleColorPaletteDX.dcs")
    session_cleanup.append("DXFiles")

    assert dx.Write(
        dxFilename, errorlog
    ), f"Simple DX Template Example unable to write DICOS File {dxFilename}\n{errorlog.GetErrorLog().Get()}"

    errorlog = ErrorLog()
    dxRead = DX()
    # You should set 'None' for the unused argument of the 'Read' function.
    assert dxRead.Read(
        dxFilename, errorlog, None
    ), f"Unable to read DX file {dxFilename}\n{errorlog.GetErrorLog().Get()}"
    assert (
        dxRead == dx
    ), f"DX file loaded from {dxFilename} does not match original.\n{errorlog.GetErrorLog().Get()}"


if __name__ == "__main__":
    test_create_dx_processing([])
    test_create_dx_presentation([])
    test_create_dx_palette([])
