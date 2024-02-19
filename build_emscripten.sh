#!/bin/bash

emcmake cmake -B ./.build/emscripten -S ./ -DCMAKE_BUILD_TYPE=Release && cmake --build ./.build/emscripten

