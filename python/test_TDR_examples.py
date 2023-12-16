from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import CustomMemoryManager
from pyDICOS import Section
from pyDICOS import TDR
from pyDICOS import Folder
from pyDICOS import DcsString, DcsLongString
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
    
    tdr = TDR(TDR.ObjectOfInspectionModule.IdInfo.OBJECT_OF_INSPECTION_ID_TYPE.enumTypeBaggage,
              TDR.TDRTypes.ThreatDetectionReport.TDR_TYPE.enumMachine,
              TDRInstanceNumber)

def main():
    CreateNoThreatTDRForBaggageSimple()
if __name__ == "__main__":
    main()