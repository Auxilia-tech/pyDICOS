from pydicos import TDRLoader
import numpy as np
import pytest


@pytest.mark.order(after="tests/test_TDR_example.py::test_no_threat_tdr")
def test_loading_no_threat():
    # Example 1: Load TDR from a file
    tdr_object = TDRLoader(filename="TDRFiles/SimpleBaggageNoThreatTDR.dcs")


@pytest.mark.order(after="tests/test_TDR_example.py::test_baggage_tdr")
def test_loading_baggage():
    # Example 1: Load TDR from a file
    tdr_object = TDRLoader(filename="TDRFiles/SimpleBaggageNoThreatTDR.dcs")


@pytest.mark.order(after="tests/test_TDR_example.py::test_multiple_ptos_tdr")
def test_loading_multiple():
    # Example 1: Load TDR from a file
    tdr_object = TDRLoader(filename="TDRFiles/MultiplePTOsTDR.dcs")


if __name__ == "__main__":
    test_loading_no_threat()
    test_loading_baggage()
    test_loading_multiple()