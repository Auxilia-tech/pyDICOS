from ._loaders import CTLoader, DXLoader, TDRLoader
import logging


def dcsread(filename: str, dcs = None):
    """Read a DICOS file.

    Parameters
    ----------
    filename : str
        The name of the file to read.
    dcs : DX|TDR|CT, optional
        The DICOS object instance that will load the data in-place.

    Returns
    -------
    dcs : DICOS
        The DICOS object read from the file.
    """
    if dcs is not None:
        dcs.read(filename)
        return dcs

    for DCSLoader in [CTLoader, DXLoader, TDRLoader]:
        try:
            dcs = DCSLoader()
            dcs.read(filename)
            return dcs
        except:
            logging.debug(f"Loading failed with {DCSLoader}")
            pass

    raise ValueError(f"Invalid DICOS file: {filename}")


def dcswrite(dcs, filename: str):
    """Write a DICOS file.

    Parameters
    ----------
    dcs : DICOS
        The DICOS object to write.
    filename : str
        The name of the file to write.
    """
    dcs.write(filename)
