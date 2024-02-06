from pyDICOS import (
    CT,
    TDR,
    DcsApplicationEntity,
    DcsDate,
    DcsLongString,
    DcsShortString,
    DcsShortText,
    DcsString,
    DcsTime,
    DcsUniqueIdentifier,
    ErrorLog,
    GeneralSeriesModule,
    Section,
    Vector3Dfloat,
    Volume,
)


def Init(ct_object=None):
    strDate = DcsDate.Today()
    strTime = DcsTime.Now()
    vecRowOrientation = Vector3Dfloat()
    vecColumnOrientation = Vector3Dfloat()
    ct_object.FreeMemory()

    vecRowOrientation.Set(1, 0, 0)
    vecColumnOrientation.Set(0, 1, 0)

    ct_object.SetFrameOfReferenceUID(DcsUniqueIdentifier("4.4.6.6.0.0.8.8.7"))
    ct_object.SetImageAcquisitionDateAndTime(strDate, strTime)
    ct_object.SetBurnedInAnnotation(False)
    ct_object.SetPhotometricInterpretation(
        CT.PHOTOMETRIC_INTERPRETATION.enumMonochrome2
    )
    ct_object.SetImageType(CT.OOI_IMAGE_CHARACTERISTICS.enumPhotoelectric)
    ct_object.SetImageAcquisitionDuration(5000)
    ct_object.SetContentDateAndTime(strDate, strTime)
    ct_object.SetOOIID(DcsLongString("10"))
    ct_object.SetOOIIDAssigningAuthority(DcsLongString("OOI ID Assigning Authority"))
    ct_object.SetOOIIDType(TDR.OBJECT_OF_INSPECTION_ID_TYPE.enumRFID)
    ct_object.SetOOIType(CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBaggage)
    ct_object.SetScanID(DcsShortString("Scan ID"))
    ct_object.GenerateScanInstanceUID()
    ct_object.SetScanStartDateAndTime(strDate, strTime)
    ct_object.SetScanType(CT.SCAN_TYPE.enumOperational)

    ct_object.GenerateSeriesInstanceUID()
    ct_object.SetSeriesDateAndTime(strDate, strTime)
    ct_object.SetSeriesAcquisitionStatus(
        GeneralSeriesModule.ACQUISITION_STATUS.enumSuccessful
    )
    ct_object.SetDeviceCalibrationDateAndTime(strDate, strTime)
    ct_object.SetDeviceSerialNumber(DcsLongString("123456987"))
    ct_object.SetMachineAddress(DcsShortText("Machine Address"))
    ct_object.SetMachineLocation(DcsLongString("Machine Location"))
    ct_object.SetMachineID(DcsShortString("Machine ID"))
    ct_object.SetDeviceManufacturer(DcsLongString("Device Manufacturer"))
    ct_object.SetDeviceManufacturerModelName(
        DcsLongString("Device Manufacturer Model Name")
    )
    ct_object.SetDeviceSoftwareVersion(DcsLongString("Device Software Version"))
    ct_object.SetSopInstanceCreationDateAndTime(strDate, strTime)
    ct_object.GenerateSopInstanceUID()

    ct_object.SetNumberOfSections(1)
    psection = ct_object.GetSectionByIndex(0)

    psection.SetFilterMaterial(Section.FILTER_MATERIAL.enumAluminum)
    psection.SetFocalSpotSizeInMM(10)
    psection.SetKVP(7000)
    psection.SetPlaneOrientation(vecRowOrientation, vecColumnOrientation)
    psection.SetPositionInMM(0, 0, 2000)
    psection.SetSpacingInMM(1, 1, 1)
    psection.GetPixelData().Allocate(
        Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit, 500, 500, 500
    )
    psection.GetPixelData().GetUnsigned16().Zero(20)


def main():
    CTObject = CT()
    errorlog = ErrorLog()
    Init(CTObject)

    if (
        CTObject.SendOverNetwork(
            1000,  # Port
            DcsString("1.1.1.1"),  # IP Address
            DcsApplicationEntity(
                "SrcApp"
            ),  # Source Application Name. Name of application using calling this function.
            DcsApplicationEntity(
                "DstApp"
            ),  # Destination Application Name. Name of application accepting the client's connection.
            errorlog,
            DcsString(""),
            DcsString(""),
        )
        == False
    ):
        print("Failed to send data across network:")
        print(errorlog.GetErrorLog().Get())
        return 1
    return 0


if __name__ == "__main__":
    main()
