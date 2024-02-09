from pyDICOS import (
    DataProcessingMultipleConnections,
    DataProcessingConnectsSpecificClientApps,
    DcsServer, 
    DcsApplicationEntity, 
    IDcsServer, 
    AuthenticationCallbackConnectionsFromClientsValidUserName,
    AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode,
    AuthenticationCallbackConnectsSpecificClientApps,
    AuthenticationCallbackClientsPresentValidUserNamePasscode
)
import argparse


def launch(opt):
    icallback = find_data_callback(opt)
    authcallback = find_auth_callback(opt)

    server = DcsServer()
    server.SetPort(1023)
    server.SetApplicationName(DcsApplicationEntity("ServerExample"))
    server.DisableDataCompression()
    server.PrioritizeDataCompression(False)

    if server.StartListening(
            icallback, 
            authcallback, 
            IDcsServer.RETRIEVE_METHOD.enumMethodUserAPI, 
            False
        ):
        print(
            f"Failed to start DICOS server at {server.GetIP().Get()}:{server.GetPort()}"
        )
        return 1
    
    try:
        input(f"Server has started at {server.GetIP().Get() or 'localhost'}:{server.GetPort()}\n")
    except EOFError:
        pass
    print("Stopping server")
    server.StopListening()
    

def parse_opt():
    parser = argparse.ArgumentParser()
    parser.add_argument('--appauth', action='store_true', help='Server will only accept some app connexions')
    parser.add_argument('--userauth', action='store_true', help='Server will only accept some ID connexions')
    parser.add_argument('--passauth', action='store_true', help='Server will also require password')

    return parser.parse_args()


def find_auth_callback(opt):
    if opt.appauth and opt.userauth:
        return AuthenticationCallbackAllowConnectsFromSpecificClientsPresentValidUserNamePasscode()
    if opt.appauth:
        return AuthenticationCallbackConnectsSpecificClientApps()
    if opt.userauth:
        if opt.passauth:
            return AuthenticationCallbackClientsPresentValidUserNamePasscode()
        return AuthenticationCallbackConnectionsFromClientsValidUserName()
    return None


def find_data_callback(opt):
    if opt.appauth:
        return DataProcessingConnectsSpecificClientApps()
    return DataProcessingMultipleConnections()


if __name__ == "__main__":
    opt = parse_opt()
    launch(opt)