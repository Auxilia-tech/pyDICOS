from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import Section
from pyDICOS import TDR
from pyDICOS import CT
from pyDICOS import Folder
from pyDICOS import DcsLongString, DcsShortString
from pyDICOS import CustomArray1DDcsLongString
from pyDICOS import DcsDate
from pyDICOS import DcsTime
from pyDICOS import Vector3Dfloat
from pyDICOS import Volume
from pyDICOS import Point3DS_UINT16
from pyDICOS import DcsLongText, DcsShortText
from pyDICOS import DcsDateTime
from pyDICOS import Point3Dfloat
from pyDICOS import Bitmap
from pyDICOS import DcsUniqueIdentifier
from pyDICOS import DcsGUID
from pyDICOS import Array1DPoint3Dfloat
from pyDICOS import GeneralSeriesModule

import numpy as np

def CreateNoThreatTDRForBaggageSimple():
    TDRInstanceNumber = 1234
    tdr = TDR(CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBaggage,
              TDR.TDR_TYPE.enumMachine,
              TDRInstanceNumber)
    
    TDRCreationStartDate = DcsDate.Today()
    TDRCreationStartTime = DcsTime.Now()
    tdr.SetContentDateAndTime(TDRCreationStartDate,TDRCreationStartTime)

    atrManufacturer = DcsLongString("Alchemy")
    atrVersion = DcsLongString("0.999")

    ATR_Parameters = CustomArray1DDcsLongString(2)
    item1 = DcsLongString("-random=true")
    item2 = DcsLongString("-magic=true")
    ATR_Parameters.SetBuffer(0, item1)
    ATR_Parameters.SetBuffer(1, item2)
    tdr.SetTDRTypeATR(atrManufacturer, atrVersion, ATR_Parameters)
    
    tdr.SetImageScaleRepresentation(10.0)

    tdr.SetAlarmDecision(TDR.ALARM_DECISION.enumClear)
    alarmDecisionDate = DcsDate(1944, 6, 6) 
    alarmDecisionTime = DcsTime(6, 30, 0, 0)
    tdr.SetAlarmDecisionDateTime(alarmDecisionDate, alarmDecisionTime)
        
    tdr.SetAbortFlag(TDR.ABORT_FLAG.enumSuccess)
    uidSopInstanceCT = DcsUniqueIdentifier(DcsGUID.GenerateAsDecimalString())
    uidSopClassCT = DcsUniqueIdentifier(pyDICOS.GetCT())
    tdr.AddReferencedSopInstance(uidSopInstanceCT, uidSopClassCT)

    errorlog = ErrorLog()
    tdrFolder = Folder("TDRFiles")
    tdrFilename = Filename(tdrFolder,"SimpleBaggageNoThreatTDR.dcs")

    if tdr.Write(tdrFilename, errorlog) != True :
        print("Simple TDR Template Example unable to write DICOS File : ", tdrFilename)
        print(errorlog.GetErrorLog().Get())
        return False
    else:
        print("Wrote file to", tdrFilename)
        tdrRead = TDR()
        errorlog = ErrorLog()

        if tdrRead.Read(tdrFilename, errorlog, None): 
            if tdrRead == tdr:
                print("Successfully read and compared TDR files")
                return True 
            else:
                print("TDR file loaded from", tdrFilename, "does not match original.")
                return False 
        else:
            print("Unable to read TDR file", tdrFilename)
            print(errorlog)
            return False
    return True       


def CreateTDRForBaggageSimple():
    TDRInstanceNumber = 1234
    tdr = TDR(CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBaggage,
              TDR.TDR_TYPE.enumMachine,
              TDRInstanceNumber)
    
    TDRCreationStartDate = DcsDate.Today()
    TDRCreationStartTime = DcsTime.Now()
    tdr.SetContentDateAndTime(TDRCreationStartDate,TDRCreationStartTime)

    atrManufacturer = DcsLongString("Alchemy")
    atrVersion = DcsLongString("0.999")
    
    ATR_Parameters = CustomArray1DDcsLongString(2)
    item1 = DcsLongString("-random=true")
    item2 = DcsLongString("-magic=true")
    ATR_Parameters.SetBuffer(0, item1)
    ATR_Parameters.SetBuffer(1, item2)
    tdr.SetTDRTypeATR(atrManufacturer, atrVersion, ATR_Parameters)
    
    tdr.SetImageScaleRepresentation(10.0)

    tdr.SetAlarmDecision(TDR.ALARM_DECISION.enumClear)
    alarmDecisionDate = DcsDate(1944, 6, 6) 
    alarmDecisionTime = DcsTime(6, 30, 0, 0)
    tdr.SetAlarmDecisionDateTime(alarmDecisionDate, alarmDecisionTime)
        
    tdr.SetAbortFlag(TDR.ABORT_FLAG.enumSuccess)

    tdr.SetTotalProcessingTimeInMS(500.0)
        
    PTOIdentifier0 = 9001
    tdr.AddPotentialThreatObject(PTOIdentifier0, TDR.ThreatType.enumThreatTypeBaggage)

    threatDescription = DcsLongText("Flammable Liquid")
    tdr.AddPTOAssessment(PTOIdentifier0, 
                         TDR.ASSESSMENT_FLAG.enumThreat, 
                         TDR.THREAT_CATEGORY.enumProhibitedItem, 
                         TDR.ABILITY_ASSESSMENT.enumNoInterference,
                         threatDescription, 
                         -1.0)
    
    tdr.SetBaggagePTODetails(PTOIdentifier0, 50.0, 7000.0, 0)

    ptoDims = Point3Dfloat(50,50,100)
    ptoMask = Bitmap(50,50,100)

    for d in range(int(ptoDims.z)):
        if d > 30 and d < 70:
            continue
        for h in range(int(ptoDims.y)):
            if h > 10 and d < 40:
                continue
            for w in range(int(ptoDims.x)):
                index = w + h*int(ptoDims.x) + d*int(ptoDims.x*ptoDims.y)
                value = None
                if w > 10 and w < 20:
                    value = False
                else:
                    value = True
                ptoMask.SetBit(w, h, d, value)
                if value != ptoMask.GetBit(index):
                    print("Failed to validate threat bitmask(", w, ",", h, ",", d, ")")

    tdr.SetThreatRegionOfInterest(PTOIdentifier0,
                                  Point3Dfloat(12,23,45),
                                  ptoDims,
                                  ptoMask,
                                  0)
    
    dateTime = DcsDateTime()
    dateTime.SetNow()
    tdr.SetPTOProcessingTime(PTOIdentifier0, dateTime, dateTime, float(0.0))

    CTReferenceUID = DcsUniqueIdentifier("1235.23456.568678.34546")
    uidSopClassCT = DcsUniqueIdentifier(pyDICOS.GetCT())
    tdr.AddReferencedInstance(PTOIdentifier0, uidSopClassCT, CTReferenceUID, 0)

    errorlog = ErrorLog()
    tdrFolder = Folder("TDRFiles")
    tdrFilename = Filename(tdrFolder,"SimpleBaggageTDR.dcs")

    if tdr.Write(tdrFilename, errorlog) != True :
        print("Simple TDR Template Example unable to write DICOS File : ", tdrFilename)
        print(errorlog.GetErrorLog().Get())
        return False
    else:
        print("Wrote file to", tdrFilename)
        tdrRead = TDR()
        errorlog = ErrorLog()

        if tdrRead.Read(tdrFilename, errorlog, None): 
            if tdrRead == tdr:
                print("Successfully read and compared TDR files")
                return True 
            else:
                print("TDR file loaded from", tdrFilename, "does not match original.")
                return False 
        else:
            print("Unable to read TDR file", tdrFilename)
            print(errorlog)
            return False
    return True        

def CreateTDRWithMultiplePTOS():

    TDRInstanceNumber = 1234
    tdr = TDR(CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBaggage,
              TDR.TDR_TYPE.enumMachine,
              TDRInstanceNumber)
    
    OOIIdentifier = DcsLongString("12345-35345324-6326342-345")
    tdr.SetOOIID(OOIIdentifier)
    tdr.SetOOIIDAssigningAuthority(DcsLongString("TSA"))
    tdr.SetOOIIDType(TDR.OBJECT_OF_INSPECTION_ID_TYPE.enumRFID)


    TDRCreationStartDate = DcsDate.Today()
    TDRCreationStartTime = DcsTime.Now()
    tdr.SetContentDateAndTime(TDRCreationStartDate,TDRCreationStartTime)

    atrManufacturer = DcsLongString("Alchemy")
    atrVersion = DcsLongString("0.999")
    
    ATR_Parameters = CustomArray1DDcsLongString(2)
    item1 = DcsLongString("-random=true")
    item2 = DcsLongString("-magic=true")
    ATR_Parameters.SetBuffer(0, item1)
    ATR_Parameters.SetBuffer(1, item2)
    tdr.SetTDRTypeATR(atrManufacturer, atrVersion, ATR_Parameters)
    
    tdr.SetImageScaleRepresentation(10.0)

    tdr.SetAlarmDecision(TDR.ALARM_DECISION.enumAlarm)
    alarmDecisionDate = DcsDate(1944, 6, 6) 
    alarmDecisionTime = DcsTime(6, 30, 0, 0)
    tdr.SetAlarmDecisionDateTime(alarmDecisionDate, alarmDecisionTime)
        
    tdr.SetAbortFlag(TDR.ABORT_FLAG.enumSuccess)

    tdr.SetTotalProcessingTimeInMS(float(500.0))

    PTOIdentifier0 = 9001
    tdr.AddPotentialThreatObject(PTOIdentifier0, TDR.ThreatType.enumThreatTypeBaggage)

    threatDescription = DcsLongText("Flammable Liquid")
    tdr.AddPTOAssessment(PTOIdentifier0, 
                         TDR.ASSESSMENT_FLAG.enumHighThreat, 
                         TDR.THREAT_CATEGORY.enumProhibitedItem, 
                         TDR.ABILITY_ASSESSMENT.enumNoInterference,
                         threatDescription, 
                         -1.0)
    
    tdr.SetBaggagePTODetails(PTOIdentifier0, float(50.0), float(7000.0), 0)


    tdr.SetThreatRegionOfInterest(PTOIdentifier0,
                                  Point3Dfloat(12,23,45),
                                  Point3Dfloat(50,50,100),
                                  Bitmap(),
                                  0)
    
    dateTime = DcsDateTime()
    dateTime.SetNow()
    tdr.SetPTOProcessingTime(PTOIdentifier0, dateTime, dateTime, float(0.0))

    PTOIdentifier1 = 2002
    tdr.AddPotentialThreatObject(PTOIdentifier1, TDR.ThreatType.enumThreatTypeBaggage)

    tdr.AddPTOAssessment(PTOIdentifier1, 
                        TDR.ASSESSMENT_FLAG.enumNoThreat,
                        TDR.THREAT_CATEGORY.enumAnomaly, 
                        TDR.ABILITY_ASSESSMENT.enumNoInterference,
                        DcsLongText(""), 
                        float(-10))
 
    tdr.SetBaggagePTODetails(PTOIdentifier1, float(100.0), float(40.0), 0)

    tdr.SetThreatRegionOfInterest(PTOIdentifier1, 
                                  Point3Dfloat(1,23,95),
                                  Point3Dfloat(22,33,444),
                                  Bitmap(),
                                  0)
    
    tdr.SetPTOProcessingTime(PTOIdentifier1, dateTime, dateTime, float(0.0))

    bp = Array1DPoint3Dfloat()
    bp.SetSize(3, False)

    bp[0].Set(1,2,3)
    bp[1].Set(3,4,5)
    bp[2].Set(5,6,7)
    tdr.SetThreatBoundingPolygon(PTOIdentifier1, bp, 0)

    CTReferenceUID = DcsUniqueIdentifier("1235.23456.568678.34546")
    uidSopClassCT = DcsUniqueIdentifier(pyDICOS.GetCT())
    tdr.AddReferencedInstance(PTOIdentifier0, uidSopClassCT, CTReferenceUID, 0)
    tdr.AddReferencedInstance(PTOIdentifier1, uidSopClassCT, CTReferenceUID, 0)

    errorlog = ErrorLog()
    tdrFolder = Folder("TDRFiles")
    tdrFilename = Filename(tdrFolder,"MultiplePTOsTDR.dcs")

    if tdr.Write(tdrFilename, errorlog) != True :
        print("Simple TDR Template Example unable to write DICOS File : ", tdrFilename)
        print(errorlog.GetErrorLog().Get())
        return False
    else:
        print("Wrote file to", tdrFilename)
        tdrRead = TDR()
        errorlog = ErrorLog()

        if tdrRead.Read(tdrFilename, errorlog, None): 
            if tdrRead == tdr:
                print("Successfully read and compared TDR files")
                return True 
            else:
                print("TDR file loaded from", tdrFilename, "does not match original.")
                return False 
        else:
            print("Unable to read TDR file", tdrFilename)
            print(errorlog)
            return False
    return True        
    
def CreateCTAndLinkItToTDR():
    bRes = True
    ct = CT()
    tdr = TDR()
    strDate = DcsDate(DcsDate.Today())
    strTime = DcsTime(DcsTime.Now())
    vecRowOrientation = Vector3Dfloat()
    vecColumnOrientation = Vector3Dfloat()
    nPTOIdentifier1 = 0
    nPTOIdentifier2 = 1

    bRes = bRes and ct.SetOOIID(DcsLongString("10"))
    ct.GenerateSopInstanceUID()
    ct.GenerateScanInstanceUID()
    ct.GenerateSeriesInstanceUID()

    bRes = bRes and ct.SetImageAcquisitionDateAndTime(strDate, strTime)
    ct.SetBurnedInAnnotation(False);  

    bRes = bRes and ct.SetPhotometricInterpretation(CT.PHOTOMETRIC_INTERPRETATION.enumMonochrome2)

    bRes = bRes and ct.SetImageType(CT.OOI_IMAGE_CHARACTERISTICS.enumPhotoelectric)
    bRes = bRes and ct.SetImageAcquisitionDuration(5000)
    bRes = bRes and ct.SetContentDateAndTime(strDate, strTime)
    bRes = bRes and ct.SetOOIIDAssigningAuthority(DcsLongString("OOI ID Assigning Authority"))
    bRes = bRes and ct.SetOOIIDType(TDR.OBJECT_OF_INSPECTION_ID_TYPE.enumRFID)
    bRes = bRes and ct.SetOOIType(CT.OBJECT_OF_INSPECTION_TYPE.enumTypeBaggage)
    bRes = bRes and ct.SetScanID(DcsShortString("Scan ID"))
    bRes = bRes and ct.SetScanStartDateAndTime(strDate, strTime)
    bRes = bRes and ct.SetScanType(CT.SCAN_TYPE.enumOperational)
    bRes = bRes and ct.SetSeriesDateAndTime(strDate, strTime)
    bRes = bRes and ct.SetSeriesAcquisitionStatus(GeneralSeriesModule.ACQUISITION_STATUS.enumSuccessful)
    bRes = bRes and ct.SetDeviceCalibrationDateAndTime(strDate, strTime)
    bRes = bRes and ct.SetDeviceSerialNumber(DcsLongString("123456987"))
    bRes = bRes and ct.SetMachineAddress(DcsShortText("Machine Address"))
    bRes = bRes and ct.SetMachineLocation(DcsLongString("Machine Location"))
    bRes = bRes and ct.SetMachineID(DcsShortString("Machine ID"))
    bRes = bRes and ct.SetDeviceManufacturer(DcsLongString("Device Manufacturer"))
    bRes = bRes and ct.SetDeviceManufacturerModelName(DcsLongString("Device Manufacturer Model Name"))
    bRes = bRes and ct.SetDeviceSoftwareVersion(DcsLongString("Device Software Version"))
    bRes = bRes and ct.SetSopInstanceCreationDateAndTime(strDate, strTime)

    ct.SetNumberOfSections(1)
    psection = ct.GetSectionByIndex(0)

    psection.SetFilterMaterial(Section.FILTER_MATERIAL.enumAluminum); 
    psection.SetFocalSpotSizeInMM(10)
    psection.SetKVP(7000); 
 
    vecRowOrientation.Set(1,0,0)
    vecColumnOrientation.Set(0,1,0)

    psection.SetPlaneOrientation(vecRowOrientation, vecColumnOrientation)

    psection.GetPixelData().Allocate(Volume.IMAGE_DATA_TYPE.enumUnsigned16Bit, 500, 500, 500)
    psection.GetPixelData().GetUnsigned16().Zero(0)

    ptFirstFrameTopLeft = Point3Dfloat(-250,-250,-250)

    psection.SetPositionInMM(ptFirstFrameTopLeft)
    psection.SetSpacingInMM(float(1.0), float(1.0), float(1.0))

    ptCenter = Point3DS_UINT16(250,250,250)

    nWhite = 0xFFFF
    vVolume = psection.GetPixelData().GetUnsigned16()
    ptPos = Point3DS_UINT16()

    for ptPos.z in range(200):
        pSlice = vVolume.GetSlice(ptPos.z)
        for ptPos.y in range(20):
            for ptPos.x in range(50):
                 pSlice.Set(ptPos.y, ptPos.x , nWhite)

    for ptPos.z in range(ptCenter.z - 40, ptCenter.z + 40):
        pSlice = vVolume.GetSlice(ptPos.z)
        for ptPos.y in range(ptCenter.y - 40, ptCenter.y + 40):
            for ptPos.x in range(ptCenter.x - 40, ptCenter.x + 40):
                pSlice.Set(ptPos.y, ptPos.x , nWhite)

    for ptPos.z in range(ptCenter.z - 5, ptCenter.z + 5):
        pSlice = vVolume.GetSlice(ptPos.z)
        for ptPos.y in range(ptCenter.y - 5, ptCenter.y + 5):
            for ptPos.x in range(ptCenter.x + 41, ptCenter.x + 51):
                pSlice.Set(ptPos.y, ptPos.x , nWhite)

    if (bRes == False):
        print("Error setting CT values")
        return 10
 
    bRes = True

    bRes = bRes and tdr.SetOOIID(ct.GetOOIID())                         
    bRes = bRes and tdr.SetScanInstanceUID(ct.GetScanInstanceUID())
    bRes = bRes and tdr.SetSeriesInstanceUID(ct.GetSeriesInstanceUID())

    tdr.GenerateSopInstanceUID()

    bRes = bRes and tdr.SetFrameOfReferenceUID(ct.GetFrameOfReferenceUID())

    bRes = bRes and tdr.AddPotentialThreatObject(nPTOIdentifier1, TDR.ThreatType.enumThreatTypeBaggage)
    bRes = bRes and tdr.AddPotentialThreatObject(nPTOIdentifier2, TDR.ThreatType.enumThreatTypeBaggage)

    bRes = bRes and tdr.AddReferencedInstance(nPTOIdentifier1, ct.GetSopClassUID(), ct.GetSopInstanceUID(), 0)
    bRes = bRes and tdr.AddReferencedInstance(nPTOIdentifier2, ct.GetSopClassUID(), ct.GetSopInstanceUID(), 0)

    bRes = bRes and tdr.AddPTOAssessment(nPTOIdentifier1, 
                                        TDR.ASSESSMENT_FLAG.enumThreat, 
                                        TDR.THREAT_CATEGORY.enumProhibitedItem, 
                                        TDR.ABILITY_ASSESSMENT.enumNoInterference,
                                        DcsLongText("Weapon"), 
                                        float(98.0 / 100.0))
    
    bRes = bRes and tdr.AddPTOAssessment(nPTOIdentifier2, 
                                        TDR.ASSESSMENT_FLAG.enumNoThreat,  
                                        TDR.THREAT_CATEGORY.enumAnomaly, 
                                        TDR.ABILITY_ASSESSMENT.enumNoInterference,
                                        DcsLongText(""), 
                                        float(-10))
 
    bounds = Array1DPoint3Dfloat()
    bounds.SetSize(2, False)
    bounds[0].Set(-250, -250, -250)
    bounds[1].Set(-200, -230, -50)

    bRes = bRes and tdr.SetThreatBoundingPolygon(0, bounds, 0)

    bounds[0].Set(float(-40), float(-40), float(-40))
    bounds[1].Set(float(40), float(40), float(40))

    bRes = bRes and tdr.SetThreatBoundingPolygon(1, bounds, 0)

    ptBase = Point3Dfloat()
    ptExtents = Point3Dfloat()
 
    ptBase.Set(1, 2, 3)
    ptExtents.Set(50, 20, 200)

    bRes = bRes and tdr.SetThreatRegionOfInterest(nPTOIdentifier1, ptBase, ptExtents, Bitmap(), 0)
    bRes = bRes and tdr.SetBaggagePTODetails(nPTOIdentifier1, 1000, 5000, 0)
    bRes = bRes and tdr.SetBaggagePTOLocationDescription(nPTOIdentifier1, DcsShortText("Corner Object"), 0)

    ptBase.Set(210, 210, 210)
    ptExtents.Set(81, 81, 81)

    bRes = bRes and tdr.SetThreatRegionOfInterest(nPTOIdentifier2, ptBase, ptExtents, Bitmap(), 0)
    bRes = bRes and tdr.SetBaggagePTODetails(nPTOIdentifier2, 20, 2, 0)
    bRes = bRes and tdr.SetBaggagePTOLocationDescription(nPTOIdentifier2, DcsShortText("Corner Object"), 0)

    bRes = bRes and tdr.SetProcessingStartTime(nPTOIdentifier1, DcsDateTime(DcsDate.Today(), DcsTime.Now()))
    bRes = bRes and tdr.SetProcessingEndTime(nPTOIdentifier1, DcsDateTime(DcsDate.Today(), DcsTime.Now()))
    bRes = bRes and tdr.SetProcessingStartTime(nPTOIdentifier2, DcsDateTime(DcsDate.Today(), DcsTime.Now()))
    bRes = bRes and tdr.SetProcessingEndTime(nPTOIdentifier2, DcsDateTime(DcsDate.Today(), DcsTime.Now()))

    bRes = bRes and tdr.SetInstanceNumber(0)
    bRes = tdr.SetContentDateAndTime(strDate, strTime)
    bRes = bRes and tdr.SetTDRType(TDR.TDR_TYPE.enumMachine)
    bRes = bRes and tdr.SetTDRTypeATR(DcsLongString("ATR Manufacturer"), DcsLongString("ATR Version"))
    
    bRes = bRes and tdr.SetImageScaleRepresentation(1) 

    bRes = bRes and tdr.SetAlarmDecision(TDR.ALARM_DECISION.enumAlarm)
    bRes = bRes and tdr.SetAlarmDecisionDateTime(strDate, strTime)
    bRes = bRes and tdr.SetAbortFlag(TDR.ABORT_FLAG.enumSuccess)
    bRes = bRes and tdr.SetTotalProcessingTimeInMS(50)
    bRes = bRes and tdr.SetOOIIDAssigningAuthority(ct.GetOOIIDAssigningAuthority())
    bRes = bRes and tdr.SetOOIIDType(ct.GetOOIIDType())
    bRes = bRes and tdr.SetOOIType(ct.GetOOIType())
    bRes = bRes and tdr.SetScanID(ct.GetScanID())
    bRes = bRes and tdr.SetScanStartDateAndTime(ct.GetScanStartDate(), ct.GetScanStartTime())
    bRes = bRes and tdr.SetScanType(ct.GetScanType())
    bRes = bRes and tdr.SetSeriesDateAndTime(ct.GetSeriesDate(), ct.GetSeriesTime())
    bRes = bRes and tdr.SetSeriesAcquisitionStatus(ct.GetSeriesAcquisitionStatus())
    bRes = bRes and tdr.SetDeviceCalibrationDateAndTime(strDate, strTime)
    bRes = bRes and tdr.SetDeviceSerialNumber(DcsLongString("TDR Serial Number"))
    bRes = bRes and tdr.SetMachineAddress(DcsShortText("TDR machine address"))
    bRes = bRes and tdr.SetMachineLocation(DcsLongString("TDR machine location"))
    bRes = bRes and tdr.SetMachineID(DcsShortString("TDR machine ID"))
    bRes = bRes and tdr.SetDeviceManufacturer(DcsLongString("TDR device manufacturer"))
    bRes = bRes and tdr.SetDeviceManufacturerModelName(DcsLongString("TDR model name"))
    bRes = bRes and tdr.SetDeviceSoftwareVersion(DcsLongString("TDR software version"))
    bRes = bRes and tdr.SetSopInstanceCreationDateAndTime(strDate, strTime)

    if bRes == False:
       print("Error setting TDR values")

    folder = Folder("CTwithTDR")
    filenameCT = Filename(folder,"CT.dcs")
    filenameTDR = Filename(folder,"TDR.dcs")

    errorlogCT = ErrorLog()
    errorlogTDR = ErrorLog()
 
    if ct.Write(filenameCT, errorlogCT) != True :
        print("Failed writing CT (CTwithTDR): ", filenameCT)
        print(errorlogCT.GetErrorLog().Get())
        return 1
    else:
        print("CT write completed (CTwithTDR)")
 
    if tdr.Write(filenameTDR, errorlogTDR,  CT.TRANSFER_SYNTAX.enumLittleEndianExplicit) != True:
        print("Failed writing TDR (CTwithTDR)")
        print(errorlogTDR.GetErrorLog().Get())
        return 2
    else:
        print("TDR write completed (CTwithTDR)")
 
    if bRes == 0:
        return 3

def main():
    CreateNoThreatTDRForBaggageSimple()
    CreateTDRForBaggageSimple()
    CreateTDRWithMultiplePTOS()
    CreateCTAndLinkItToTDR()
if __name__ == "__main__":
    main()