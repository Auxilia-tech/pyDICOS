import pytest
import os, shutil

REM_FOLDERS = [
    "SimpleCT",
    "CTwithTDR",
    "DXFiles",
    "TDRFiles"
]

@pytest.fixture(scope="session")
def session_cleanup():
    to_delete = []
    yield to_delete
    for folder in to_delete:
        if os.path.isdir(folder):
            shutil.rmtree(folder)

def test_remove(session_cleanup):
    session_cleanup.extend(REM_FOLDERS)
    assert True