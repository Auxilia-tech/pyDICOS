from ._loaders import CTLoader, DXLoader, TDRLoader
import logging
from pathlib import Path
from typing import Optional, Union


def dcsread(
    filename: Union[str, Path],
    dcs: Optional[Union[CTLoader, DXLoader, TDRLoader]] = None
) -> Union[CTLoader, DXLoader, TDRLoader]:
    """Read a DICOS file.

    Parameters
    ----------
    filename : str|Path
        The name of the file to read.
    dcs : DX|TDR|CT, optional
        The DICOS object instance that will load the data in-place.

    Returns
    -------
    dcs : DICOS
        The DICOS object read from the file.

    Raises
    ------
    ValueError
        If the DICOS file is invalid.
    """
    if dcs is not None:
        dcs.read(str(filename))
        return dcs

    for DCSLoader in [CTLoader, DXLoader, TDRLoader]:
        try:
            dcs_loader: Union[CTLoader, DXLoader, TDRLoader] = DCSLoader()
            dcs_loader.read(str(filename))
            return dcs_loader
        except:
            logging.debug(f"Loading failed with {DCSLoader}")
            pass

    raise ValueError(f"Invalid DICOS file: {filename}")


def dcswrite(dcs: Union[CTLoader, DXLoader, TDRLoader], filename: Union[str, Path]):
    """Write a DICOS file.

    Parameters
    ----------
    dcs : DICOS
        The DICOS object to write.
    filename : str|Path
        The name of the file to write.

    Raises
    ------
    RuntimeError
        If writing the DICOS file fails.
    """
    dcs.write(str(filename))
