from pydicos import CTLoader
import numpy as np
import pytest


@pytest.mark.order(after="tests/test_CT_write.py::test_create_ct_files")
def test_loading_from_file():
    # Example 1: Load CT from a file
    ct_object = CTLoader(filename="SimpleCT/SimpleCT0000.dcs")
    data = ct_object.get_data()
    assert len(data) == 1
    assert data[0].shape == (40, 20, 10)
    assert np.all(data[0] == 48879)


@pytest.mark.order(after="tests/test_CT_write.py::test_create_ct_files")
def test_loading_from_object():
    # Example 2: Load CT from an existing CT object
    ct_object_1 = CTLoader(filename="SimpleCT/SimpleCT0000.dcs")
    ct_object_2 = CTLoader(ct_object=ct_object_1.ct_object)
    data = ct_object_2.get_data()
    assert len(data) == 1
    assert data[0].shape == (40, 20, 10)
    assert np.all(data[0] == 48879)


if __name__ == "__main__":
    test_loading_from_file()
    test_loading_from_object()
