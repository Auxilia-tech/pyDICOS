from pyDICOS import DcsDate, DcsDateTime, DcsTime


class DicosDateTime:
    def __init__(
            self, date: DcsDate = None, time: DcsTime = None, datetime: DcsDateTime = None
    ) -> None:
        """Initialize the DicosDateTime class.

        Parameters
        ----------
        date : DcsDate
            The date.
        time : DcsTime
            The time.
        datetime : DcsDateTime
            The date and time concatenated object.
        """
        if datetime is not None:
            self.__init__(
                datetime.Get(DcsDate(), DcsTime(), 0)[1],
                datetime.Get(DcsDate(), DcsTime(), 0)[2],
            )
        else:
            if date is None:
                date = DcsDate()
            if time is None:
                time = DcsTime()
            self.date = date
            self.time = time

    def __str__(self) -> str:
        """Get the string representation of the DicosDateTime class.

        Returns
        -------
        str
            The string representation of the DicosDateTime class.
        """
        dct = self.as_dict()
        return f"{dct['date'][0]}-{dct['date'][1]:02}-{dct['date'][2]:02} {dct['time'][0]:02}:{dct['time'][1]:02}:{dct['time'][2]:02}.{dct['time'][3]}"

    def __repr__(self) -> str:
        """Get the string representation of the DicosDateTime class.

        Returns
        -------
        str
            The string representation of the DicosDateTime class.
        """
        return f"DicosDateTime({self.as_dict()})"

    def __sub__(self, other) -> int:
        """Get the substraction of two DateTimes in ms

        Returns
        -------
        int
            The substraction of two DateTimes in ms
        """
        assert type(other) == DicosDateTime, \
            "You can only substract DicosDateTimes objects from each other"
        dct1 = self.as_dict()
        dct2 = other.as_dict()
        diffms = dct1["time"][3] - dct2["time"][3]
        diffsec = dct1["time"][2] - dct2["time"][2]
        diffmin = dct1["time"][1] - dct2["time"][1]
        diffhour = dct1["time"][0] - dct2["time"][0]
        diffday = dct1["date"][2] - dct2["date"][2]
        diffmonth = dct1["date"][1] - dct2["date"][1]
        diffyear = dct1["date"][0] - dct2["date"][0]
        return diffms + 1000 * (diffsec + 60 * (diffmin + 60 * (diffhour + 24 * (diffday + 30 * (diffmonth + 12 * diffyear)))))

    def as_dict(self) -> dict:
        """Get the DicosDateTime class as a dictionary.

        Returns
        -------
        dict
            The DicosDateTime class as a dictionary.
        """
        return {
            "date": self.date.Get(0, 0, 0)[1:],
            "time": self.time.Get(0, 0, 0, 0)[1:],
        }
