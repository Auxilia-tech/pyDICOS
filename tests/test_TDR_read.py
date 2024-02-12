import pytest
from datetime import datetime
from pydicos import TDRLoader


@pytest.mark.order(after="tests/test_TDR_write.py::test_no_threat_tdr")
def test_loading_no_threat():
    now = datetime.now()
    tdr_object = TDRLoader(filename="TDRFiles/SimpleBaggageNoThreatTDR.dcs")
    assert len(tdr_object) == 0
    data = tdr_object.get_data()
    assert data["InstanceNumber"] == 1234
    assert data["ProcessingTime"] == 0
    assert data["ScanType"] == 1
    assert data["ScanStartDateTime"]["date"] == (now.year, now.month, now.day)
    assert data["ScanStartDateTime"]["time"][:3] == (now.hour, now.minute, pytest.approx(now.second, 10))
    assert data["AlarmDecision"] == 2
    assert data["AlarmDecisionDateTime"]["date"] == (1944, 6, 6)
    assert data["AlarmDecisionDateTime"]["time"] == (6, 30, 0, 0)
    assert data["ImageScaleRepresentation"] == 10
    assert data["ATR"]["manufacturer"] == "Alchemy"
    assert data["ATR"]["version"] == "0.999"
    assert data["ATR"]["parameters"]["random"] == "true"
    assert data["ATR"]["parameters"]["magic"] == "true"
    assert data["PTOs"] == []


@pytest.mark.order(after="tests/test_TDR_write.py::test_baggage_tdr")
def test_loading_baggage():
    now = datetime.now()
    tdr_object = TDRLoader(filename="TDRFiles/SimpleBaggageTDR.dcs")
    assert len(tdr_object) == 1
    data = tdr_object.get_data()
    assert data["InstanceNumber"] == 1234
    assert data["ProcessingTime"] == 500
    assert data["ScanType"] == 1
    assert data["ScanStartDateTime"]["date"] == (now.year, now.month, now.day)
    assert data["ScanStartDateTime"]["time"][:3] == (now.hour, now.minute, pytest.approx(now.second, 10))
    assert data["AlarmDecision"] == 2
    assert data["AlarmDecisionDateTime"]["date"] == (1944, 6, 6)
    assert data["AlarmDecisionDateTime"]["time"] == (6, 30, 0, 0)
    assert data["ImageScaleRepresentation"] == 10
    assert data["ATR"]["manufacturer"] == "Alchemy"
    assert data["ATR"]["version"] == "0.999"
    assert data["ATR"]["parameters"]["random"] == "true"
    assert data["ATR"]["parameters"]["magic"] == "true"

    assert data["PTOs"][0]["Base"]["x"] == 12
    assert data["PTOs"][0]["Base"]["y"] == 23
    assert data["PTOs"][0]["Base"]["z"] == 45
    assert data["PTOs"][0]["Extent"]["x"] == 50
    assert data["PTOs"][0]["Extent"]["y"] == 50
    assert data["PTOs"][0]["Extent"]["z"] == 100
    assert data["PTOs"][0]["ID"] == 9001
    assert data["PTOs"][0]["Description"] == "Flammable Liquid"
    assert data["PTOs"][0]["Probability"] == -1
    assert data["PTOs"][0]["Polygon"] == []


@pytest.mark.order(after="tests/test_TDR_write.py::test_multiple_ptos_tdr")
def test_loading_multiple():
    now = datetime.now()
    tdr_object = TDRLoader(filename="TDRFiles/MultiplePTOsTDR.dcs")
    assert len(tdr_object) == 2
    data = tdr_object.get_data()
    assert data["InstanceNumber"] == 1234
    assert data["ProcessingTime"] == 500
    assert data["ScanType"] == 1
    assert data["ScanStartDateTime"]["date"] == (now.year, now.month, now.day)
    assert data["ScanStartDateTime"]["time"][:3] == (now.hour, now.minute, pytest.approx(now.second, 10))
    assert data["AlarmDecision"] == 1
    assert data["AlarmDecisionDateTime"]["date"] == (1944, 6, 6)
    assert data["AlarmDecisionDateTime"]["time"] == (6, 30, 0, 0)
    assert data["ImageScaleRepresentation"] == 10
    assert data["ATR"]["manufacturer"] == "Alchemy"
    assert data["ATR"]["version"] == "0.999"
    assert data["ATR"]["parameters"]["random"] == "true"
    assert data["ATR"]["parameters"]["magic"] == "true"

    assert data["PTOs"][0]["Base"]["x"] == 1
    assert data["PTOs"][0]["Base"]["y"] == 23
    assert data["PTOs"][0]["Base"]["z"] == 95
    assert data["PTOs"][0]["Extent"]["x"] == 22
    assert data["PTOs"][0]["Extent"]["y"] == 33
    assert data["PTOs"][0]["Extent"]["z"] == 444
    assert data["PTOs"][0]["ID"] == 2002
    assert data["PTOs"][0]["Description"] == ""
    assert data["PTOs"][0]["Probability"] == -1
    assert data["PTOs"][0]["Polygon"][0]["x"] == 1
    assert data["PTOs"][0]["Polygon"][0]["y"] == 2
    assert data["PTOs"][0]["Polygon"][0]["z"] == 3
    assert data["PTOs"][0]["Polygon"][1]["x"] == 3
    assert data["PTOs"][0]["Polygon"][1]["y"] == 4
    assert data["PTOs"][0]["Polygon"][1]["z"] == 5
    assert data["PTOs"][0]["Polygon"][2]["x"] == 5
    assert data["PTOs"][0]["Polygon"][2]["y"] == 6
    assert data["PTOs"][0]["Polygon"][2]["z"] == 7

    assert data["PTOs"][1]["Base"]["x"] == 12
    assert data["PTOs"][1]["Base"]["y"] == 23
    assert data["PTOs"][1]["Base"]["z"] == 45
    assert data["PTOs"][1]["Extent"]["x"] == 50
    assert data["PTOs"][1]["Extent"]["y"] == 50
    assert data["PTOs"][1]["Extent"]["z"] == 100
    assert data["PTOs"][1]["ID"] == 9001
    assert data["PTOs"][1]["Description"] == "Flammable Liquid"
    assert data["PTOs"][1]["Probability"] == -1
    assert data["PTOs"][1]["Polygon"] == []


@pytest.mark.order(after="tests/test_TDR_write.py::test_ct_linked_tdr")
def test_loading_tdr_linked_ct():
    now = datetime.now()
    tdr_object = TDRLoader(filename="CTwithTDR/TDR.dcs")
    assert len(tdr_object) == 2
    data = tdr_object.get_data()
    assert data["InstanceNumber"] == 0
    assert data["ProcessingTime"] == 50
    assert data["ScanType"] == 1
    assert data["ScanStartDateTime"]["date"] == (now.year, now.month, now.day)
    assert data["ScanStartDateTime"]["time"][:3] == (now.hour, now.minute, pytest.approx(now.second, 10))
    assert data["AlarmDecision"] == 1
    assert data["AlarmDecisionDateTime"]["date"] == (now.year, now.month, now.day)
    assert data["AlarmDecisionDateTime"]["time"][:3] == (now.hour, now.minute, pytest.approx(now.second, 10))
    assert data["ImageScaleRepresentation"] == 1
    assert data["ATR"]["manufacturer"] == "ATR Manufacturer"
    assert data["ATR"]["version"] == "ATR Version"
    assert data["ATR"]["parameters"] == {}

    assert data["PTOs"][0]["Base"]["x"] == 1
    assert data["PTOs"][0]["Base"]["y"] == 2
    assert data["PTOs"][0]["Base"]["z"] == 3
    assert data["PTOs"][0]["Extent"]["x"] == 50
    assert data["PTOs"][0]["Extent"]["y"] == 20
    assert data["PTOs"][0]["Extent"]["z"] == 200
    assert data["PTOs"][0]["ID"] == 0
    assert data["PTOs"][0]["Description"] == "Weapon"
    assert data["PTOs"][0]["Probability"] == pytest.approx(0.98, 1e-6)
    assert data["PTOs"][0]["Polygon"][0]["x"] == -250
    assert data["PTOs"][0]["Polygon"][0]["y"] == -250
    assert data["PTOs"][0]["Polygon"][0]["z"] == -250
    assert data["PTOs"][0]["Polygon"][1]["x"] == -200
    assert data["PTOs"][0]["Polygon"][1]["y"] == -230
    assert data["PTOs"][0]["Polygon"][1]["z"] == -50

    assert data["PTOs"][1]["Base"]["x"] == 210
    assert data["PTOs"][1]["Base"]["y"] == 210
    assert data["PTOs"][1]["Base"]["z"] == 210
    assert data["PTOs"][1]["Extent"]["x"] == 81
    assert data["PTOs"][1]["Extent"]["y"] == 81
    assert data["PTOs"][1]["Extent"]["z"] == 81
    assert data["PTOs"][1]["ID"] == 1
    assert data["PTOs"][1]["Description"] == ""
    assert data["PTOs"][1]["Probability"] == -1
    assert data["PTOs"][1]["Polygon"][0]["x"] == -40
    assert data["PTOs"][1]["Polygon"][0]["y"] == -40
    assert data["PTOs"][1]["Polygon"][0]["z"] == -40
    assert data["PTOs"][1]["Polygon"][1]["x"] == 40
    assert data["PTOs"][1]["Polygon"][1]["y"] == 40
    assert data["PTOs"][1]["Polygon"][1]["z"] == 40


if __name__ == "__main__":
    test_loading_no_threat()
    test_loading_baggage()
    test_loading_multiple()
    test_loading_tdr_linked_ct()
