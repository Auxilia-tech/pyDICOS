import numpy as np
from pydicos import DXLoader
import pytest


@pytest.mark.order(after="tests/test_DX_write.py::test_create_dx_processing")
def test_loading_from_file_processing():
    # Example 1: Load DX from a file
    dx_object = DXLoader(filename="DXFiles/SimpleProcessingDX.dcs")
    data = dx_object.get_data()
    assert data.shape == (128, 256)
    suite = np.array([i for i in range(128*256)]).reshape(128, 256)
    assert np.all(data == suite)


@pytest.mark.order(after="tests/test_DX_write.py::test_create_dx_processing")
def test_loading_from_object_processing():
    # Example 2: Load DX from an existing DX object
    dx_object_1 = DXLoader(filename="DXFiles/SimpleProcessingDX.dcs")
    dx_object_2 = DXLoader(dx_object=dx_object_1.dx_object)
    data = dx_object_2.get_data()
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


@pytest.mark.order(after="tests/test_DX_write.py::test_create_dx_presentation")
def test_loading_from_object_presentation():
    # Example 4: Load DX from an existing DX object
    dx_object_1 = DXLoader(filename="DXFiles/SimplePresentationDX.dcs")
    dx_object_2 = DXLoader(dx_object=dx_object_1.dx_object)
    data = dx_object_2.get_data()
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


@pytest.mark.order(after="tests/test_DX_write.py::test_create_dx_palette")
def test_loading_from_object_palette():
    # Example 6: Load DX from an existing DX object
    dx_object_1 = DXLoader(filename="DXFiles/SimpleColorPaletteDX.dcs")
    dx_object_2 = DXLoader(dx_object=dx_object_1.dx_object)
    data = dx_object_2.get_data()
    assert data.shape == (128, 256)
    suite = np.array([[i]*256 for i in range(128)])
    assert np.all(data == suite)


if __name__ == "__main__":
    test_loading_from_object_processing()
    test_loading_from_file_processing()
    test_loading_from_object_presentation()
    test_loading_from_file_presentation()
    test_loading_from_object_palette()
    test_loading_from_file_palette()
