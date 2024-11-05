#!/usr/bin/env bash

set -e -o pipefail

rm -rf deps
mkdir -p deps

# Setup AIGER
rm -rf aiger-1.9.9.tar.gz
wget https://fmv.jku.at/aiger/aiger-1.9.9.tar.gz
tar xf aiger-1.9.9.tar.gz
mv aiger-1.9.9 deps/aiger
rm deps/aiger/VERSION

# Setup Boolector
git clone https://github.com/yvizel/boolector.git deps/boolector

cd deps/boolector
git checkout bitblast-api

./contrib/setup-btor2tools.sh
./contrib/setup-lingeling.sh
./configure.sh --prefix $(pwd)/../install
cd build

make -j$(nproc) install
