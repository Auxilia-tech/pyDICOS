
# Contributing

## Setup dev environment

For new contributors, you need to install g++, cmake, and pybind11 before starting your development

```
pip install -r requirements.txt
```

Install the [Stratovan toolkit](https://www.stratovan.com/products/dicos-toolkit) in the `opt` folder.
```
chmod +x ./sdicos_lin_ubuntu-20-{version}.run
./sdicos_lin_ubuntu-20-{version}.run --unattendedmodeui none --mode unattended --prefix /opt/stratovan/sdicos
```
Then, you should launch the setup.sh script :
 
```
bash setup.sh
```

To generate a python wheel :

```
python setup.py bdist_wheel
```

That's it !

## Testing 
To test the python scripts, run any example in python folder:

```
python file_name.py
```