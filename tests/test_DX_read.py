import numpy as np
import pytest
import pydicos
from pathlib import Path
from pydicos import dcsread, dcswrite


@pytest.mark.order(after="tests/test_DX_write.py::test_create_dx_processing")
def test_loading_from_file_processing():
    # Test 1: Load DX from a file written with pyDICOS
    dx_object = pydicos.DXLoader(filename=Path("DXFiles", "SimpleProcessingDX.dcs"))
    data = dx_object.get_data()
    suite = np.array([i for i in range(128 * 256)]).reshape(128, 256)
    assert data.shape == (128, 256)
    assert np.all(data == suite)
    dcswrite(dx_object, Path("DXFiles","SimpleProcessingDX2.dcs"))

    # Test 2: Load DX from a file written with pydicos
    dx_object_2 = dcsread(filename=Path("DXFiles", "SimpleProcessingDX2.dcs"))
    data = dx_object_2.get_data()
    assert data.shape == (128, 256)
    assert np.all(data == suite)
    
    # Test 3: Load DX data from a file written with set_data
    dx_object_3 = pydicos.DXLoader()
    dx_object_3.set_data(suite.astype(np.uint16))
    data = dx_object_3.get_data()
    assert data.shape == (128, 256)
    assert np.all(data == suite)


@pytest.mark.order(after="tests/test_DX_write.py::test_create_dx_presentation")
def test_loading_from_file_presentation():
    # Test 4: Load DX from a file written with pyDICOS
    dx_loader_file = dcsread(filename=Path("DXFiles", "SimplePresentationDX.dcs"))
    data = dx_loader_file.get_data()
    assert data.shape == (128, 256)
    suite = np.array([i for i in range(128 * 256)]).reshape(128, 256)
    assert np.all(data == suite)


@pytest.mark.order(after="tests/test_DX_write.py::test_create_dx_palette")
def test_loading_from_file_palette():
    # Test 5: Load DX from a file written with pyDICOS
    dx_loader_file = dcsread(filename="DXFiles/SimpleColorPaletteDX.dcs")
    data = dx_loader_file.get_data()
    assert data.shape == (128, 256)
    suite = np.array([[i] * 256 for i in range(128)])
    assert np.all(data == suite)


if __name__ == "__main__":
    test_loading_from_file_processing()
    test_loading_from_file_presentation()
    test_loading_from_file_palette()
