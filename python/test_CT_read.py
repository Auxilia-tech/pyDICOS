from pyDICOS import Filename
from pyDICOS import CT

CTObject = CT()
FS = Filename("SimpleCT0000.dcs")
print(FS.GetExtension())
#success = CTObject.Read()


