#!/bin/sh

#    build.sh - builds kernel file for fieldOS 
#    Copyright (C) 2025  fieldbox
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.
#    
#    This file is based on material from the OSDev Wiki 
#    (<https://wiki.osdev.org/>), which is licensed under CC0 (public domain
#    dedication).
    
set -e
. ./headers.sh

objcopy -O elf32-i386 -B i386 -I binary kernel/arch/i386/font.psfu kernel/arch/i386/font.o

for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install)
done
