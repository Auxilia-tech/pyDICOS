import numpy as np
import pytest

from pydicos import DXLoader


@pytest.mark.order(after="tests/test_DX_write.py::test_create_dx_processing")
def test_loading_from_file_processing():
    # Example 1: Load DX from a file
    dx_object = DXLoader(filename="DXFiles/SimpleProcessingDX.dcs")
    data = dx_object.get_data()
    assert data.shape == (128, 256)
    suite = np.array([i for i in range(128*256)]).reshape(128, 256)
    assert np.all(data == suite)


@pytest.mark.order(after="tests/test_DX_write.py::test_create_dx_presentation")
def test_loading_from_file_presentation():
    # Example 3: Load DX from a file
    dx_loader_file = DXLoader(filename="DXFiles/SimplePresentationDX.dcs")
    data = dx_loader_file.get_data()
    assert data.shape == (128, 256)
    suite = np.array([i for i in range(128*256)]).reshape(128, 256)
    assert np.all(data == suite)


@pytest.mark.order(after="tests/test_DX_write.py::test_create_dx_palette")
def test_loading_from_file_palette():
    # Example 5: Load DX from a file
    dx_loader_file = DXLoader(filename="DXFiles/SimpleColorPaletteDX.dcs")
    data = dx_loader_file.get_data()
    assert data.shape == (128, 256)
    suite = np.array([[i]*256 for i in range(128)])
    assert np.all(data == suite)


if __name__ == "__main__":
    test_loading_from_file_processing()
    test_loading_from_file_presentation()
    test_loading_from_file_palette()
