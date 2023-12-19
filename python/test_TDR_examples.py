from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import CustomMemoryManager
from pyDICOS import Section
from pyDICOS import TDR
from pyDICOS import CT
from pyDICOS import Folder
from pyDICOS import DcsString, DcsLongString
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
from pyDICOS import DcsLongText
from pyDICOS import Point3Dfloat
from pyDICOS import Bitmap
from pyDICOS import DcsUniqueIdentifier
from pyDICOS import DcsGUID
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
    
    dateTime = DcsTime.SetNow()
    tdr.SetPTOProcessingTime(PTOIdentifier0, dateTime, dateTime, float(0.0))


def main():
    CreateNoThreatTDRForBaggageSimple()
    CreateTDRForBaggageSimple()
if __name__ == "__main__":
    main()