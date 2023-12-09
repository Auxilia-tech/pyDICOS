from pyDICOS import Section
from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import DX
from pyDICOS import Array1DS_UINT16
from pyDICOS import Array1DPairBoolMemBuff
from pyDICOS import Array3DLargeS_UINT16
from pyDICOS import Volume
import numpy as np


DXObject = DX()

filename_ = Filename("SimpleDX/SimpleProcessingDX.dcs")
errorlog_ = ErrorLog()

if DXObject.Read(filename_, errorlog_, None):
    print("Loaded DX")
else:
    print("Failed to load CT")