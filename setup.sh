#!/bin/bash
OS="`uname`"
case $OS in
  'Linux')
    OS='Linux'
    PACKAGE_COMMAND='python3 setup.py bdist'
    ;;
  *) 
    OS='Unknown'
    PACKAGE_COMMAND='echo "Unknown OS."'
    ;;
esac

echo "Detected OS: $OS"
echo "Running package command: $PACKAGE_COMMAND"
$PACKAGE_COMMAND