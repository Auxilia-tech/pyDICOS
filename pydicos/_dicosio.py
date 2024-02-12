from pydicos import CTLoader, DXLoader, TDRLoader


def dcsread(filename: str, dcs_type: str = None, dcs = None):
    """Read a DICOS file.

    Parameters
    ----------
    filename : str
        The name of the file to read.
    dcs_type : str, optional
        The DICOS object type to read. Must be one of "CT", "DX", or "TDR".
    dcs : DX|TDR|CT, optional
        The DICOS object instance that will load the data in-place.

    Returns
    -------
    dcs : DICOS
        The DICOS object read from the file.
    """
    assert (
        dcs_type is not None or dcs is not None
    ), "A DICOS type or object must be provided"

    if dcs is not None:
        dcs.read(filename)
        return dcs

    if dcs_type == "CT":
        return CTLoader(filename)
    elif dcs_type == "DX":
        return DXLoader(filename)
    elif dcs_type == "TDR":
        return TDRLoader(filename)
    else:
        raise ValueError(f"Invalid DICOS type: {dcs_type}")


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
