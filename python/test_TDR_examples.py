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


def main():
    CreateNoThreatTDRForBaggageSimple()
if __name__ == "__main__":
    main()