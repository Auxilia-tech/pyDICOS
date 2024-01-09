from pyDICOS import DcsDate
from pyDICOS import DcsTime
from pyDICOS import Vector3Dfloat
from pyDICOS import CT, ErrorLog
from pyDICOS import DcsUniqueIdentifier


def Init(ct_object=None):

    strDate = DcsDate.Today()
    strTime = DcsTime.Now()
    vecRowOrientation = Vector3Dfloat()
    vecColumnOrientation = Vector3Dfloat()
    ct_object.FreeMemory()

    vecRowOrientation.Set(1,0,0)
    vecColumnOrientation.Set(0,1,0)
    
    ct_object.SetFrameOfReferenceUID(DcsUniqueIdentifier("4.4.6.6.0.0.8.8.7"))
    """ct_object.SetImageAcquisitionDateAndTime(strDate, strTime);
    ct_object.SetBurnedInAnnotation(false);
    ct_object.SetPhotometricInterpretation(SDICOS::ImagePixelMacro::enumMonochrome2);
    ct_object.SetImageType(SDICOS::CTTypes::CTImage::enumPhotoelectric);
    ct_object.SetImageAcquisitionDuration(5000);
    ct_object.SetContentDateAndTime(strDate, strTime);
    ct_object.SetOOIID("10");
    ct_object.SetOOIIDAssigningAuthority("OOI ID Assigning Authority");
    ct_object.SetOOIIDType(SDICOS::ObjectOfInspectionModule::IdInfo::enumRFID);
    ct_object.SetOOIType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage);
    ct_object.SetScanID("Scan ID");
    ct_object.GenerateScanInstanceUID();
    ct_object.SetScanStartDateAndTime(strDate, strTime);
    ct_object.SetScanType(SDICOS::GeneralScanModule::enumOperational);
    ct_object.GenerateSeriesInstanceUID();
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
    
