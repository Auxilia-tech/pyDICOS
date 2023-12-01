from pyDICOS import Section
from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import CustomMemoryManager
from pyDICOS import CT
from pyDICOS import DcsString
from pyDICOS import MemoryBuffer
from pyDICOS import Array1DS_UINT16
from pyDICOS import Array1DPairBoolMemBuff
import numpy

numpy.set_printoptions(suppress=True, formatter={'float_kind':'{:0.2f}'.format}) 

CTObject = CT()
FS = Filename("/home/ahau/freelance/Louis/pyDICOS/pyDICOS/python/CTUserAPI.dcs")
print(FS.GetFullPath())
EL = ErrorLog()
MM = CustomMemoryManager()
DC = DcsString()

if CTObject.Read(FS, EL, MM):
    print(EL.GetErrorLog())
    print("Loaded CT")
    numpy_array = numpy.array(MM.getData())
    print(numpy_array)
else:
    print("Failed to load CT")
    print(EL.GetErrorLog())


