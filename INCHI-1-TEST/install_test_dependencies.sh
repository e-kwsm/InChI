#!/bin/bash

python -m pip install --upgrade --break-system-packages pip
python -m pip install --break-system-packages -e .[invariance-tests]


git clone https://www.github.com/google/googletest

