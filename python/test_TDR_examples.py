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
from pyDIVOS import Point3DFloat

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

    tdr.SetAlarmDecision(TDR.ALARM_DECISION.enumAlarm)

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

    ptoDims = Point3DFloat(50,50,100)
 
    SDICOS::Bitmap ptoMask(50,50,100);
    
    

def main():
    CreateNoThreatTDRForBaggageSimple()
if __name__ == "__main__":
    main()