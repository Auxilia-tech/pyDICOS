from pyDICOS import DcsClient
from pyDICOS import DcsString
from pyDICOS import Filename
from pyDICOS import DcsApplicationEntity


def main():
    client = DcsClient()
    client.SetServerPortandIP(1000, DcsString("1.1.1.1"))
    client.SetSourceApplication(DcsApplicationEntity("ClientExample"))
    client.SetDestinationApplication(DcsApplicationEntity("Server"))
    if client.Echo() :
        print("Echo success")
    else:
        print("Echo failed")
        print("Error log:")
        print(client.GetErrorLog().GetErrorLog().Get())
        client.GetErrorLog().WriteLog(Filename("ErrorLog - Echo Failed.txt"))
        return 1
    return 0

if __name__ == "__main__":
    main()
    
