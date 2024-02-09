from pyDICOS import DcsApplicationEntity, DcsClient, DcsServer, DcsString, Filename, IDcsServer, DataProcessingMultipleConnections
import pytest
from xprocess import ProcessStarter
from pathlib import Path

FILE = Path(__file__).resolve()
ROOT = FILE.parent

@pytest.fixture
def localServer(xprocess):

    class Starter(ProcessStarter):
        pattern = "Server has started at *"
        timeout = 20
        args = ["python", str(ROOT) + "/localserver.py"]

    logfile = xprocess.ensure("localServer", Starter)
    print(f"logfile : {logfile}")
    yield 
    xprocess.getinfo("localserver").terminate()


def test_echo(localServer):
    client = DcsClient()
    client.SetServerPortandIP((1000), DcsString("127.0.0.1"))
    client.SetSourceApplication(DcsApplicationEntity("ClientExample"))
    client.SetDestinationApplication(DcsApplicationEntity("ServerExample"))

    if client.ConnectToServer():
        print("Connected to server")
    else:
        print("Connecting to server failed")
        print("Error log")
        print(client.GetErrorLog().GetErrorLog().Get())
        client.GetErrorLog().WriteLog(
            Filename("ErrorLog - Server Connection Failed.txt")
        )
        return 1

    if client.StartDicosSession(DcsClient.SOPCLASSUID.enumSopEcho):
        print("DICOS session started")
    else:
        print("DICOS session failed")
        print("Error log:")
        print(client.GetErrorLog().GetErrorLog().Get())
        client.GetErrorLog().WriteLog(
            Filename("ErrorLog - DICOS Session Start Failed.txt")
        )
        return 1

    if client.Echo():
        print("Echo success")
    else:
        print("Echo failed")
        print("Error log:")
        print(client.GetErrorLog().GetErrorLog().Get())
        client.GetErrorLog().WriteLog(Filename("ErrorLog - Echo Failed.txt"))
        return 1
    return 0


if __name__ == "__main__":
    test_echo(None)
