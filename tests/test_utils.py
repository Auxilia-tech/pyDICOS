from pydicos import DicosDateTime
from pyDICOS import DcsDateTime
from datetime import datetime


def test_datetime():
    t = DicosDateTime()
    assert str(t) == "0-00-00 00:00:00.0"
    assert repr(t) == "DicosDateTime({'date': (0, 0, 0), 'time': (0, 0, 0, 0)})"

    now = DcsDateTime()
    now.SetNow()
    pynow = str(datetime.now())
    t = str(DicosDateTime(datetime=now))
    assert t[-5] == pynow[-5]


if __name__ == "__main__":
    test_datetime()