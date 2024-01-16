
from pyDICOS import DcsApplicationEntity
from pyDICOS import DataProcessing
from pyDICOS import DcsServer
from pyDICOS import IDcsServer


def main():
   icallback = DataProcessing()
   server = DcsServer()
   server.SetPort(1000)
   server.SetApplicationName(DcsApplicationEntity("ServerExample"))

   server.DisableDataCompression()
   server.PrioritizeDataCompression(False)

   if server.StartListening(icallback, None, IDcsServer.RETRIEVE_METHOD.enumMethodUserAPI, False) == True :
     print("Failed to start DICOS server. IP:Port: ", server.GetIP(), ":", server.GetPort())
     return 1
    
   print("Press enter to stop server")
   server.StopListening()

if __name__ == "__main__":
    main()
    
