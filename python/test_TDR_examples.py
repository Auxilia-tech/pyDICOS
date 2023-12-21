from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import CustomMemoryManager
from pyDICOS import Section
from pyDICOS import TDR
from pyDICOS import CT
from pyDICOS import Folder
from pyDICOS import DcsString, DcsLongString, DcsShortString
from pyDICOS import Array1DDcsLongString
from pyDICOS import CustomArray1DDcsLongString
from pyDICOS import DcsDate
from pyDICOS import DcsTime
from pyDICOS import MemoryBuffer
from pyDICOS import Array1DS_UINT16
from pyDICOS import Array1DArray2DS_UINT16
from pyDICOS import Array2DS_UINT16
from pyDICOS import Vector3Dfloat
from pyDICOS import Volume
from pyDICOS import Array3DLargeS_UINT16
from pyDICOS import Point3DS_UINT16
from pyDICOS import DicosFileListing
from pyDICOS import DcsLongText, DcsShortText
from pyDICOS import DcsDateTime
from pyDICOS import Point3Dfloat
from pyDICOS import Bitmap
from pyDICOS import DcsUniqueIdentifier
from pyDICOS import DcsGUID
from pyDICOS import Array1DPoint3Dfloat
from pyDICOS import GeneralSeriesModule
import pyDICOS

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
    bRes = bRes and ct.SetSeriesDateAndTime(strDate, strTime)
    bRes = bRes and ct.SetSeriesAcquisitionStatus(GeneralSeriesModule.ACQUISITION_STATUS.enumSuccessful)
    bRes = bRes and ct.SetDeviceCalibrationDateAndTime(strDate, strTime)
    bRes = bRes and ct.SetDeviceSerialNumber(DcsLongString("123456987 ID"))
    bRes = bRes and ct.SetMachineAddress(DcsShortText("Scan ID"))
    bRes = bRes and ct.SetMachineLocation(DcsLongString("Machine Address"))
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
 
    

def main():
    CreateNoThreatTDRForBaggageSimple()
    CreateTDRForBaggageSimple()
    CreateTDRWithMultiplePTOS()
    CreateCTAndLinkItToTDR()
if __name__ == "__main__":
    main()