from pyDICOS import DcsApplicationEntity, DcsClient, DcsString, Filename


def main():
    retVal = 0
    client = DcsClient()
    client.SetServerPortandIP(1000, DcsString("1.1.1.1"))
    client.SetSourceApplication(DcsApplicationEntity("ClientExample"))
    client.SetDestinationApplication(DcsApplicationEntity("Server"))
    if client.ConnectToServer() == True:
        print("Connected to server")
    else:
        print("Connecting to server failed")
        print("Error log")
        print(client.GetErrorLog().GetErrorLog().Get())
        client.GetErrorLog().WriteLog(
            Filename("ErrorLog - Server Connection Failed.txt")
        )
        retVal = 1

    if client.StartDicosSession(DcsClient.SOPCLASSUID.enumSopEcho) == True:
        print("DICOS session started")
    else:
        print("DICOS session failed")
        print("Error log:")
        print(client.GetErrorLog().GetErrorLog().Get())
        client.GetErrorLog().WriteLog(
            Filename("ErrorLog - DICOS Session Start Failed.txt")
        )
        retVal = 1

    if client.Echo() == True:
        print("Echo success")
    else:
        print("Echo failed")
        print("Error log:")
        print(client.GetErrorLog().GetErrorLog().Get())
        client.GetErrorLog().WriteLog(Filename("ErrorLog - Echo Failed.txt"))
        retVal = 1

    client.StopDicosSession()
    client.DisconnectFromServer()
    return retVal


if __name__ == "__main__":
    main()
