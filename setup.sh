#!/bin/bash
OS="`uname`"
case $OS in
  'Linux')
    OS='Linux'
    PACKAGE_COMMAND='python3 setup.py bdist_wheel'
    ;;
  *) 
    OS='Unknown'
    PACKAGE_COMMAND='echo "Unknown OS."'
    ;;
esac

# Change DICOS SDK path if needed
export SDICOS_PATH="/opt/stratovan/sdicos"

echo "Using DICOS SDK path : $SDICOS_PATH"
# Check if DICOS SDK path exists
if [ ! -d "$SDICOS_PATH" ]; then
  echo "DICOS SDK path does not exist. Please set the SDICOS_PATH environment variable to the path of the DICOS SDK."
  exit 1
fi

echo "Detected OS: $OS"
echo "Running package command: $PACKAGE_COMMAND"
$PACKAGE_COMMAND