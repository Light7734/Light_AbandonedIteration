#!/bin/bash

for f in $(find `pwd` -name "*.cppE"); do
    rm "${f}"
done
