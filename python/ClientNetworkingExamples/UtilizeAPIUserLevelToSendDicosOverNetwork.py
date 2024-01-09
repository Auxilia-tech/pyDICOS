from pyDICOS import Vector3Dfloat
from pyDICOS import CT, ErrorLog
from pyDICOS import DcsLongString, DcsShortString, DcsUniqueIdentifier, DcsDate, DcsTime
from pyDICOS import TDR


def Init(ct_object=None):

    strDate = DcsDate.Today()
    strTime = DcsTime.Now()
    vecRowOrientation = Vector3Dfloat()
    vecColumnOrientation = Vector3Dfloat()
    ct_object.FreeMemory()

    vecRowOrientation.Set(1,0,0)
    vecColumnOrientation.Set(0,1,0)
    
    ct_object.SetFrameOfReferenceUID(DcsUniqueIdentifier("4.4.6.6.0.0.8.8.7"))
    ct_object.SetImageAcquisitionDateAndTime(strDate, strTime)
    ct_object.SetBurnedInAnnotation(False)
    ct_object.SetPhotometricInterpretation(CT.PHOTOMETRIC_INTERPRETATION.enumMonochrome2)
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

    """ct_object.GenerateSeriesInstanceUID();
    ct_object.SetSeriesDateAndTime(strDate, strTime);
    ct_object.SetSeriesAcquisitionStatus(SDICOS::GeneralSeriesModule::enumSuccessful);
    ct_object.SetDeviceCalibrationDateAndTime(strDate, strTime);
    ct_object.SetDeviceSerialNumber("123456987");
    ct_object.SetMachineAddress("Machine Address");
    ct_object.SetMachineLocation("Machine Location");
    ct_object.SetMachineID("Machine ID");
    ct_object.SetDeviceManufacturer("Device Manufacturer");
    ct_object.SetDeviceManufacturerModelName("Device Manufacturer Model Name");
    ct_object.SetDeviceSoftwareVersion("Device Software Version");
    ct_object.SetSopInstanceCreationDateAndTime(strDate, strTime);
    ct_object.GenerateSopInstanceUID();
    """



def main():
    CTObject = CT()
    errorlog_ = ErrorLog()
    Init(CTObject)

if __name__ == "__main__":
    main()
    
