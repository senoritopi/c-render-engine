#!/bin/bash
cd build
make 
echo "Running C++ Render Engine"
./c-render-engine
open output.tga
cd ..