from pyDICOS import Filename
from pyDICOS import ErrorLog
from pyDICOS import CustomMemoryManager
from pyDICOS import CT

CTObject = CT()
FS = Filename("SimpleCT0000.dcs")
EL = ErrorLog()
MM = CustomMemoryManager(512 * 512 * 8, 500)
success = CTObject.Read(FS, EL, MM)
print(success)


