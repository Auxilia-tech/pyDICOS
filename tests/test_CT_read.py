import numpy as np
import pytest

from pydicos import dcsread, dcswrite, CTLoader


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
    tdr_object = ct_object.generate_tdr([{
        "label": "razorblade",
        "point1": [23, 45, 67],
        "point2": [50, 100, 150],
        "confidence": 0.78,
        "mask": None
    }], output_file = "CTwithTDR/TDR2.dcs")
    print(tdr_object.get_data())
    # TODO: write assert tests


if __name__ == "__main__":
    test_loading_from_file()
    test_loading_from_file_in_place()
    test_generate_tdr()
