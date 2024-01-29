from pyDICOS import CT, DX, TDR, Filename, ErrorLog


def read_dcs_ct(filename):
    """Read a DICOS file.

    Parameters
    ----------
    filename : str
        The name of the file to read.

    Returns
    -------
    ct : CT
        The CT object read from the file.
    """
    ct = CT()
    _err = ErrorLog()
    if not ct.Read(Filename(filename), _err, None):
        raise RuntimeError(f"Failed to read DICOS file: {filename}\n{_err.GetErrorLog().Get()}")
    return ct


def read_dcs_dx(filename):
    """Read a DICOS file.

    Parameters
    ----------
    filename : str
        The name of the file to read.

    Returns
    -------
    dx : DX
        The DX object read from the file.
    """
    dx = DX()
    _err = ErrorLog()
    if not dx.Read(Filename(filename), _err, None):
        raise RuntimeError(f"Failed to read DICOS file: {filename}\n{_err.GetErrorLog().Get()}")
    return dx


def read_dcs_tdr(filename):
    """Read a DICOS file.

    Parameters
    ----------
    filename : str
        The name of the file to read.

    Returns
    -------
    tdr : TDR
        The TDR object read from the file.
    """
    tdr = TDR()
    _err = ErrorLog()
    if not tdr.Read(Filename(filename), _err, None):
        raise RuntimeError(f"Failed to read DICOS file: {filename}\n{_err.GetErrorLog().Get()}")
    return tdr


def read_dcs(filename, dcs_type):
    """Read a DICOS file.

    Parameters
    ----------
    filename : str
        The name of the file to read.
    dcs_type : str
        The DICOS object type to read. Must be one of "CT", "DX", or "TDR".

    Returns
    -------
    dcs : DICOS
        The DICOS object read from the file.
    """
    if dcs_type == "CT":
        return read_dcs_ct(filename)
    elif dcs_type == "DX":
        return read_dcs_dx(filename)
    elif dcs_type == "TDR":
        return read_dcs_tdr(filename)
    else:
        raise ValueError(f"Invalid DICOS type: {dcs_type}")


def write_dcs(dcs, filename):
    """Write a DICOS file.

    Parameters
    ----------
    dcs : DICOS
        The DICOS object to write.
    filename : str
        The name of the file to write.
    """
    _err = ErrorLog()
    if type(dcs) == CT:
        res = dcs.Write(Filename(filename), _err, CT.TRANSFER_SYNTAX.enumLittleEndianExplicit)
    else:
        res = dcs.Write(Filename(filename), _err)
    if not res:
        raise RuntimeError(f"Failed to write DICOS file: {filename}\n{_err.GetErrorLog().Get()}")
