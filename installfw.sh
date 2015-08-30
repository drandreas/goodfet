#!/bin/sh
export board=goodfet42
#export board=facedancer11
#export board=facedancer21
export CFLAGS=-Denableuart1
#export CFLAGS=-Denableavr

cd "$(dirname "$0")/firmware/"

#goodfet.bsl --dumpinfo >info.txt|| exit 1;
make clean all                   || exit 1;
make reinstall                   || exit 1;
make installinfo                 || exit 1;
