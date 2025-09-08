#!/bin/bash

set -e

(
    cd INCHI-1-TEST
    ./install_test_dependencies.sh
)

./INCHI-1-TEST/install_build_dependencies.sh
./INCHI-1-TEST/build_with_cmake.sh all
