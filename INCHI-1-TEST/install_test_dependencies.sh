#!/bin/bash

python -m pip install --upgrade --break-system-packages pip
python -m pip install --break-system-packages -e .[invariance-tests]

#Install Googletest library 
wget -O googletest.zip https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
unzip googletest.zip -d .. && mv ../googletest-03597a01ee50ed33e9dfd640b249b4be3799d395 ../googletest && rm googletest.zip

