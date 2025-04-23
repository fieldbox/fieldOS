#!/bin/sh
set -e
. ./headers.sh

objcopy -O elf32-i386 -B i386 -I binary kernel/arch/i386/font.psfu kernel/arch/i386/font.o

for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install)
done
