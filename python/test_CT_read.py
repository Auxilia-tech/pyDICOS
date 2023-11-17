from pyDICOS import Section
from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import CustomMemoryManager
from pyDICOS import CT
from pyDICOS import DcsString
from pyDICOS import MemoryBuffer
from pyDICOS import Array1D

CTObject = CT()
FS = Filename("/home/ahau/freelance/Louis/pyDICOS/pyDICOS/python/SimpleCT0000.dcs")
print(FS.GetFullPath())
EL = ErrorLog()
MM = CustomMemoryManager(512 * 512 * 8, 500)
DC = DcsString()

if CTObject.Read(FS, EL, MM):
    print("Loaded CT")
    buff = MM.m_vBuffers.GetSize()
    print("Preallocated buffers:", buff)
else:
    print("Failed to load CT")
    print(EL.GetErrorLog())


