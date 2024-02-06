from pyDICOS import DcsApplicationEntity, DcsClient, DcsString, Filename


def main():
    client = DcsClient()
    client.DisableDataCompression()
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
        return 1

    if (
        client.StartDicosSession(
            DcsClient.SOPCLASSUID.enumSopEcho
            | DcsClient.SOPCLASSUID.enumSopCT
            | DcsClient.SOPCLASSUID.enumSopTDR
        )
        == True
    ):
        print("DICOS session started")
    else:
        print("DICOS session failed")
        print("Error log:")
        print(client.GetErrorLog().GetErrorLog().Get())
        client.GetErrorLog().WriteLog(
            Filename("ErrorLog - DICOS Session Start Failed.txt")
        )
        return 1

    # All API's can be used when sending DATA to the server.

    #   Send User-Level API DICOS data using:
    #  -CT::SendOverNetwork(DcsClient &, ErrorLog &)
    #  -AIT2D::SendOverNetwork(DcsClient &, ErrorLog &)
    #  -AIT3D::SendOverNetwork(DcsClient &, ErrorLog &)
    #  -DX::SendOverNetwork(DcsClient &, ErrorLog &)
    #  -TDR::SendOverNetwork(DcsClient &, ErrorLog &)

    #   Send Module-Level API DICOS data using:
    #  -DcsClient::Store(CT &, ErrorLog &)
    #  -DcsClient::Store(AIT2D &, ErrorLog &)
    #  -DcsClient::Store(AIT3D &, ErrorLog &)
    #  -DcsClient::Store(DX &, ErrorLog &)
    #  -DcsClient::Store(QR &, ErrorLog &)
    #  -DcsClient::Store(TDR &, ErrorLog &)

    # Send Tag-Level API DICOS data using:
    #  -DcsClient::Store(AttributeManager &, ErrorLog &)

    client.StopDicosSession()

    if (
        client.StartDicosSession(
            DcsClient.SOPCLASSUID.enumSopDX | DcsClient.SOPCLASSUID.enumSopTDR
        )
        == True
    ):
        print("DICOS session 2 started")
    else:
        print("DICOS session 2 failed")
        print("Error log:")
        print(client.GetErrorLog().GetErrorLog().Get())
        client.GetErrorLog().WriteLog(
            Filename("ErrorLog - DICOS Session 2 Start Failed.txt")
        )
        return 1

    # All API's can be used when sending DATA to the server.

    #   Send User-Level API DICOS data using:
    #  -CT::SendOverNetwork(DcsClient &, ErrorLog &)
    #  -AIT2D::SendOverNetwork(DcsClient &, ErrorLog &)
    #  -AIT3D::SendOverNetwork(DcsClient &, ErrorLog &)
    #  -DX::SendOverNetwork(DcsClient &, ErrorLog &)
    #  -TDR::SendOverNetwork(DcsClient &, ErrorLog &)

    #   Send Module-Level API DICOS data using:
    #  -DcsClient::Store(CT &, ErrorLog &)
    #  -DcsClient::Store(AIT2D &, ErrorLog &)
    #  -DcsClient::Store(AIT3D &, ErrorLog &)
    #  -DcsClient::Store(DX &, ErrorLog &)
    #  -DcsClient::Store(QR &, ErrorLog &)
    #  -DcsClient::Store(TDR &, ErrorLog &)

    # Send Tag-Level API DICOS data using:
    #  -DcsClient::Store(AttributeManager &, ErrorLog &)

    client.StopDicosSession()
    client.DisconnectFromServer()

    return 0


if __name__ == "__main__":
    main()
