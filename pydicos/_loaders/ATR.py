from pyDICOS import CustomArray1DDcsLongString, DcsLongString


# Handles the ATR metadata.
class ATRSettings:
    def __init__(
        self, manufacturer: str = None, version: str = None, parameters: dict = None
    ) -> None:
        """Initialize the ATR class.

        Parameters
        ----------
        manufacturer : str
            The manufacturer of the ATR.
        version : str
            The version of the ATR.
        parameters : dict
            The parameters of the ATR. ex. {"threshold": "0.5", "quantized": "True"...}
        """
        self.manufacturer = DcsLongString(manufacturer)
        self.version = DcsLongString(version)
        self.parameters = (
            CustomArray1DDcsLongString(len(parameters))
            if parameters is not None
            else CustomArray1DDcsLongString(0)
        )
        if parameters is not None:
            for i, (key, value) in enumerate(parameters.items()):
                self.parameters.SetBuffer(i, DcsLongString(f"-{key}={value}"))

    def __str__(self) -> str:
        """Get the string representation of the ATR class.

        Returns
        -------
        str
            The string representation of the ATR class.
        """
        return f"ATRSettings({self.as_dict()})"

    def __repr__(self) -> str:
        """Get the string representation of the ATR class.

        Returns
        -------
        str
            The string representation of the ATR class.
        """
        return self.__str__()

    def as_dict(self) -> dict:
        """Get the ATR settings as a dictionary.

        Returns
        -------
        dict
            The ATR settings as a dictionary.
        """
        return {
            "manufacturer": self.manufacturer.Get(),
            "version": self.version.Get(),
            "parameters": {
                self.parameters[i].Get().split("=")[0].strip("-"): self.parameters[i]
                .Get()
                .split("=")[1]
                for i in range(self.parameters.GetSize())
            },
        }
