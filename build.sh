#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Create a release directory and enter it
mkdir -p release
cd release

# Configure the project with cmake as a release version
cmake -DCMAKE_BUILD_TYPE=Release ../

# Build the project
make

# Return back to original directory
cd -
