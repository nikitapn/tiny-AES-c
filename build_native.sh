#!/bin/bash

cmake -B ./.build/native -S ./ -DCMAKE_BUILD_TYPE=Release && cmake --build ./.build/native

