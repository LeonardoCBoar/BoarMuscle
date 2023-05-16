#!/usr/bin/bash

cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_PREFIX_PATH="vcpkg/packages/sfml_x64-linux" -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE
cmake --build build -j`nproc`

cp build/Examples .