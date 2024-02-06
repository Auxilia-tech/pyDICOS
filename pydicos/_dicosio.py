from pyDICOS import CT, DX, TDR, ErrorLog, Filename


def read_dcs_ct(filename: str, ct : CT = None):
    """Read a DICOS file.

    Parameters
    ----------
    filename : str
        The name of the file to read.
    ct : CT
        The CT object instance that will load the data.

    Returns
    -------
    ct : CT
        The CT object read from the file.
    """
    if ct is None:
        ct = CT()
    _err = ErrorLog()
    if not ct.Read(Filename(filename), _err, None):
        raise RuntimeError(f"Failed to read DICOS file: {filename}\n{_err.GetErrorLog().Get()}")
    return ct


def read_dcs_dx(filename: str, dx : DX = None):
    """Read a DICOS file.

    Parameters
    ----------
    filename : str
        The name of the file to read.
    dx : DX
        The DX object instance that will load the data.

    Returns
    -------
    dx : DX
        The DX object read from the file.
    """
    if dx is None:
        dx = DX()
    _err = ErrorLog()
    if not dx.Read(Filename(filename), _err, None):
        raise RuntimeError(f"Failed to read DICOS file: {filename}\n{_err.GetErrorLog().Get()}")
    return dx


def read_dcs_tdr(filename: str, tdr : TDR = None):
    """Read a DICOS file.

    Parameters
    ----------
    filename : str
        The name of the file to read.
    tdr : TDR
        The TDR object instance that will load the data.

    Returns
    -------
    tdr : TDR
        The TDR object read from the file.
    """
    if tdr is None:
        tdr = TDR()
    _err = ErrorLog()
    if not tdr.Read(Filename(filename), _err, None):
        raise RuntimeError(f"Failed to read DICOS file: {filename}\n{_err.GetErrorLog().Get()}")
    return tdr


def read_dcs(filename: str, dcs_type: str = None, dcs: DX|TDR|CT = None):
    """Read a DICOS file.

    Parameters
    ----------
    filename : str
        The name of the file to read.
    dcs_type : str
        The DICOS object type to read. Must be one of "CT", "DX", or "TDR".
    dcs : DX|TDR|CT
        The DICOS object instance that will load the data

    Returns
    -------
    dcs : DICOS
        The DICOS object read from the file.
    """
    assert dcs_type is not None or dcs is not None, "A DICOS type or object must be provided"

    if dcs is not None:
        if issubclass(type(dcs), CT):
            return read_dcs_ct(filename, ct=dcs)
        elif issubclass(type(dcs), DX):
            return read_dcs_dx(filename, dx=dcs)
        elif issubclass(type(dcs), TDR):
            return read_dcs_tdr(filename, tdr=dcs)
        else : 
            raise TypeError(f"Invalid DICOS object: {dcs}")
    
    if dcs_type == "CT":
        return read_dcs_ct(filename)
    elif dcs_type == "DX":
        return read_dcs_dx(filename)
    elif dcs_type == "TDR":
        return read_dcs_tdr(filename)
    else:
        raise ValueError(f"Invalid DICOS type: {dcs_type}")


def write_dcs(dcs, filename: str):
    """Write a DICOS file.

    Parameters
    ----------
    dcs : DICOS
        The DICOS object to write.
    filename : str
        The name of the file to write.
    """
    _err = ErrorLog()
    if issubclass(type(dcs), CT):
        res = dcs.Write(Filename(filename), _err, CT.TRANSFER_SYNTAX.enumLittleEndianExplicit)
    else:
        res = dcs.Write(Filename(filename), _err)
    if not res:
        raise RuntimeError(f"Failed to write DICOS file: {filename}\n{_err.GetErrorLog().Get()}")
