#!/usr/bin/env bash

qmake6 -project -o 1lab.pro &&
qmake6 &&
printf "QT += widgets gui core printsupport" >> 1lab.pro &&
make &&
./1lab
