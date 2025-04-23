#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/fieldos.kernel isodir/boot/fieldos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "fieldos" {
	multiboot2 /boot/fieldos.kernel
}
EOF
grub-mkrescue -o fieldos.iso isodir
