from pydicos import TDRLoader
import numpy as np
import pytest


@pytest.mark.order(after="tests/test_TDR_example.py::test_no_threat_tdr")
def test_loading_no_threat():
    # Example 1: Load TDR from a file
    tdr_object = TDRLoader(filename="TDRFiles/SimpleBaggageNoThreatTDR.dcs")
    assert len(tdr_object) == 0
    data = tdr_object.get_data()
    assert data["InstanceNumber"] == 1234
    assert data["ATR"]["manufacturer"] == "Alchemy"
    assert data["ATR"]["version"] == "0.999"
    assert data["ATR"]["parameters"]["random"] == "true"
    assert data["ATR"]["parameters"]["magic"] == "true"


@pytest.mark.order(after="tests/test_TDR_example.py::test_baggage_tdr")
def test_loading_baggage():
    # Example 1: Load TDR from a file
    tdr_object = TDRLoader(filename="TDRFiles/SimpleBaggageTDR.dcs")
    assert len(tdr_object) == 1
    assert tdr_object.get_data()["InstanceNumber"] == 1234


@pytest.mark.order(after="tests/test_TDR_example.py::test_multiple_ptos_tdr")
def test_loading_multiple():
    # Example 1: Load TDR from a file
    tdr_object = TDRLoader(filename="TDRFiles/MultiplePTOsTDR.dcs")
    assert len(tdr_object) == 2
    assert tdr_object.get_data()["InstanceNumber"] == 1234


if __name__ == "__main__":
    test_loading_no_threat()
    test_loading_baggage()
    test_loading_multiple()