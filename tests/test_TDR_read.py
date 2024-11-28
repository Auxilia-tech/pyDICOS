import pytest
from datetime import datetime
import numpy as np
import pydicos
from pathlib import Path
from pydicos import dcsread, TDR_DATA_TEMPLATE


@pytest.mark.order(after="tests/test_TDR_write.py::test_no_threat_tdr")
def test_loading_no_threat():
    now = datetime.now()
    tdr_object = dcsread(filename=Path("TDRFiles", "SimpleBaggageNoThreatTDR.dcs"))
    assert len(tdr_object) == 0
    data = tdr_object.get_data()
    assert data["InstanceNumber"] == 1234
    assert data["ProcessingTime"] == 0
    assert data["ScanType"] == 1
    assert data["ContentDateAndTime"]["date"] == (now.year, now.month, now.day)
    assert data["ContentDateAndTime"]["time"][:3] == (now.hour, now.minute, pytest.approx(now.second, 10))
    assert data["AlarmDecision"] == 2
    assert data["AlarmDecisionDateTime"]["date"] == (1944, 6, 6)
    assert data["AlarmDecisionDateTime"]["time"] == (6, 30, 0, 0)
    assert data["ImageScaleRepresentation"] == 10
    assert data["TDRType"] == 1
    assert data["ATR"]["manufacturer"] == "Alchemy"
    assert data["ATR"]["version"] == "0.999"
    assert data["ATR"]["parameters"]["random"] == "true"
    assert data["ATR"]["parameters"]["magic"] == "true"
    assert data["PTOs"] == []


@pytest.mark.order(after="tests/test_TDR_write.py::test_baggage_tdr")
def test_loading_baggage():
    now = datetime.now()
    tdr_object = dcsread(filename=Path("TDRFiles", "SimpleBaggageTDR.dcs"))
    assert len(tdr_object) == 1
    data = tdr_object.get_data()
    assert data["InstanceNumber"] == 1234
    assert data["ProcessingTime"] == 500
    assert data["ScanType"] == 1
    assert (datetime(*(data["ContentDateAndTime"]["date"] + data["ContentDateAndTime"]["time"][:3])) - now).total_seconds() <= 30
    assert data["AlarmDecision"] == 2
    assert data["AlarmDecisionDateTime"]["date"] == (1944, 6, 6)
    assert data["AlarmDecisionDateTime"]["time"] == (6, 30, 0, 0)
    assert data["ImageScaleRepresentation"] == 10
    assert data["TDRType"] == 1
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
    assert data["PTOs"][0]["Assessment"]["description"] == "Flammable Liquid"
    assert data["PTOs"][0]["Assessment"]["probability"] == -1
    assert data["PTOs"][0]["Polygon"] == []
    assert data["PTOs"][0]["ReferencedInstance"]["SopClassUID"] == "1.2.840.10008.5.1.4.1.1.501.3"


@pytest.mark.order(after="tests/test_TDR_write.py::test_multiple_ptos_tdr")
def test_loading_multiple():
    now = datetime.now()
    tdr_object = dcsread(filename="TDRFiles/MultiplePTOsTDR.dcs")
    assert len(tdr_object) == 2
    data = tdr_object.get_data()
    assert data["InstanceNumber"] == 1234
    assert data["ProcessingTime"] == 500
    assert data["ScanType"] == 1
    assert (datetime(*(data["ContentDateAndTime"]["date"] + data["ContentDateAndTime"]["time"][:3])) - now).total_seconds() <= 30
    assert data["AlarmDecision"] == 1
    assert data["AlarmDecisionDateTime"]["date"] == (1944, 6, 6)
    assert data["AlarmDecisionDateTime"]["time"] == (6, 30, 0, 0)
    assert data["ImageScaleRepresentation"] == 10
    assert data["TDRType"] == 1
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
    assert data["PTOs"][0]["Assessment"]["description"] == ""
    assert data["PTOs"][0]["Assessment"]["probability"] == -1
    assert data["PTOs"][0]["Polygon"][0]["x"] == 1
    assert data["PTOs"][0]["Polygon"][0]["y"] == 2
    assert data["PTOs"][0]["Polygon"][0]["z"] == 3
    assert data["PTOs"][0]["Polygon"][1]["x"] == 3
    assert data["PTOs"][0]["Polygon"][1]["y"] == 4
    assert data["PTOs"][0]["Polygon"][1]["z"] == 5
    assert data["PTOs"][0]["Polygon"][2]["x"] == 5
    assert data["PTOs"][0]["Polygon"][2]["y"] == 6
    assert data["PTOs"][0]["Polygon"][2]["z"] == 7
    assert data["PTOs"][0]["ReferencedInstance"]["SopClassUID"] == "1.2.840.10008.5.1.4.1.1.501.3"

    assert data["PTOs"][1]["Base"]["x"] == 12
    assert data["PTOs"][1]["Base"]["y"] == 23
    assert data["PTOs"][1]["Base"]["z"] == 45
    assert data["PTOs"][1]["Extent"]["x"] == 50
    assert data["PTOs"][1]["Extent"]["y"] == 50
    assert data["PTOs"][1]["Extent"]["z"] == 100
    assert data["PTOs"][1]["ID"] == 9001
    assert data["PTOs"][1]["Assessment"]["description"] == "Flammable Liquid"
    assert data["PTOs"][1]["Assessment"]["probability"] == -1
    assert data["PTOs"][1]["Polygon"] == []
    assert data["PTOs"][1]["ReferencedInstance"]["SopClassUID"] == "1.2.840.10008.5.1.4.1.1.501.3"


@pytest.mark.order(after="tests/test_TDR_write.py::test_ct_linked_tdr")
def test_loading_tdr_linked_ct():
    now = datetime.now()
    tdr_object = dcsread(filename="CTwithTDR/TDR.dcs")
    assert len(tdr_object) == 2
    data = tdr_object.get_data()
    assert data["InstanceNumber"] == 0
    assert data["ProcessingTime"] == 50
    assert data["ScanType"] == 1
    assert (datetime(*(data["ContentDateAndTime"]["date"] + data["ContentDateAndTime"]["time"][:3])) - now).total_seconds() <= 30
    assert data["AlarmDecision"] == 1
    assert (datetime(*(data["AlarmDecisionDateTime"]["date"] + data["AlarmDecisionDateTime"]["time"][:3])) - now).total_seconds() <= 30
    assert data["ImageScaleRepresentation"] == 1
    assert data["TDRType"] == 1
    assert data["OOIType"] == 3
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
    assert data["PTOs"][0]["Assessment"]["description"] == "Weapon"
    assert data["PTOs"][0]["Assessment"]["probability"] == pytest.approx(0.98, 1e-6)
    assert data["PTOs"][0]["Polygon"][0]["x"] == -250
    assert data["PTOs"][0]["Polygon"][0]["y"] == -250
    assert data["PTOs"][0]["Polygon"][0]["z"] == -250
    assert data["PTOs"][0]["Polygon"][1]["x"] == -200
    assert data["PTOs"][0]["Polygon"][1]["y"] == -230
    assert data["PTOs"][0]["Polygon"][1]["z"] == -50
    assert data["PTOs"][0]["ReferencedInstance"]["SopClassUID"] == "1.2.840.10008.5.1.4.1.1.501.3"

    assert data["PTOs"][1]["Base"]["x"] == 210
    assert data["PTOs"][1]["Base"]["y"] == 210
    assert data["PTOs"][1]["Base"]["z"] == 210
    assert data["PTOs"][1]["Extent"]["x"] == 81
    assert data["PTOs"][1]["Extent"]["y"] == 81
    assert data["PTOs"][1]["Extent"]["z"] == 81
    assert data["PTOs"][1]["ID"] == 1
    assert data["PTOs"][1]["Assessment"]["description"] == ""
    assert data["PTOs"][1]["Assessment"]["probability"] == -1
    assert data["PTOs"][1]["Polygon"][0]["x"] == -40
    assert data["PTOs"][1]["Polygon"][0]["y"] == -40
    assert data["PTOs"][1]["Polygon"][0]["z"] == -40
    assert data["PTOs"][1]["Polygon"][1]["x"] == 40
    assert data["PTOs"][1]["Polygon"][1]["y"] == 40
    assert data["PTOs"][1]["Polygon"][1]["z"] == 40
    assert data["PTOs"][1]["ReferencedInstance"]["SopClassUID"] == "1.2.840.10008.5.1.4.1.1.501.3"


def test_set_data():
    tdr_object = pydicos.TDRLoader()
    tdr_object.set_data(TDR_DATA_TEMPLATE)
    data = tdr_object.get_data()
    for pto_template, pto_data in zip(TDR_DATA_TEMPLATE["PTOs"], data["PTOs"]):
        assert np.all(pto_template.pop("Bitmap") == pto_data.pop("Bitmap"))
        pto_template.pop("ReferencedInstance")
        pto_data.pop("ReferencedInstance")
    assert data == TDR_DATA_TEMPLATE


if __name__ == "__main__":
    test_loading_no_threat()
    test_loading_baggage()
    test_loading_multiple()
    test_loading_tdr_linked_ct()
    test_set_data()
