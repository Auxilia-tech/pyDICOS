import numpy as np
import pytest

from pydicos import CTLoader


@pytest.mark.order(after="tests/test_CT_write.py::test_create_ct_files")
def test_loading_from_file():
    # Example 1: Load CT from a file
    ct_object = CTLoader(filename="SimpleCT/SimpleCT0000.dcs")
    data = ct_object.get_data()
    assert len(data) == 1
    assert data[0].shape == (40, 20, 10)
    assert np.all(data[0] == 48879)


if __name__ == "__main__":
    test_loading_from_file()
