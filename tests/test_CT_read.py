import numpy as np
import pytest

from pydicos import dcsread, dcswrite, CTLoader
from tests.test_utils import get_tdr_data_output_template, get_pto_data, set_alarm_decision


@pytest.mark.order(after="tests/test_CT_write.py::test_create_ct_files")
def test_loading_from_file():
    ct_object = dcsread("SimpleCT/SimpleCT0000.dcs")
    data = ct_object.get_data()
    assert len(data) == 1
    assert data[0].shape == (40, 20, 10)
    assert np.all(data[0] == 48879)

@pytest.mark.order(after="tests/test_CT_write.py::test_create_ct_files")
def test_loading_from_file_in_place():
    ct_object = dcsread("SimpleCT/SimpleCT0000.dcs")
    data = ct_object.get_data()
    assert len(data) == 1
    assert data[0].shape == (40, 20, 10)
    assert np.all(data[0] == 48879)
    dcswrite(ct_object, "SimpleCT/SimpleCT0000_2.dcs")

    ct_object_2 = dcsread("SimpleCT/SimpleCT0000_2.dcs")
    data2 = ct_object_2.get_data()
    assert len(data2) == 1
    assert data2[0].shape == (40, 20, 10)
    assert np.all(data2[0] == 48879)

    ct_object_3 = CTLoader()
    ct_object_3.set_data(data)
    data3 = ct_object_3.get_data()
    assert len(data3) == 1
    assert data3[0].shape == (40, 20, 10)
    assert np.all(data3[0] == 48879)


@pytest.mark.order(after="tests/test_TDR_write.py::test_ct_linked_tdr")
def test_generate_tdr():
    ct_object = dcsread("CTwithTDR/CT.dcs")
    tdr_data = get_tdr_data_output_template()
    tdr_data["PTOs"] = []
    tdr_data["PTOs"].append(get_pto_data(0, [5, 5, 5], [5, 5, 5], f"Label0", 0.7, np.ones((5, 5, 5)).astype(np.bool_).astype(np.uint8)))
    tdr_data["PTOs"].append(get_pto_data(1, [40, 40, 40], [5, 5, 5], f"Label1", 0.7, np.ones((5, 5, 5)).astype(np.bool_).astype(np.uint8)))
    set_alarm_decision(tdr_data)
    tdr_object = ct_object.generate_tdr(tdr_data, output_file = "CTwithTDR/TDR2.dcs")
    print(tdr_object.get_data())
    assert tdr_object.get_data()["PTOs"][0]["Assessment"]["probability"] == pytest.approx(0.7, 1e-6)
    assert tdr_object.get_data()["AlarmDecision"] == 1
    assert np.sum(tdr_object.get_data()["PTOs"][0]["Bitmap"]) == np.sum(np.ones((5, 5, 5)).astype(np.bool_).astype(np.uint8))
    assert np.sum(tdr_object.get_data()["PTOs"][1]["Bitmap"]) == np.sum(np.ones((5, 5, 5)).astype(np.bool_).astype(np.uint8))
