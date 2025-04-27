# fieldOS

fieldOS is a small side-project/hobby OS. This project is primarily for teaching me operating system concepts and improving my knowledge of C and x86 assembly.

## Building

Building requires a cross-compiler to i686-elf, and optionally GRUB to produce a final bootable ISO and QEMU to run it. Run `clean.sh` to clean the working directory if the OS has been built before, then run `build.sh` 
to create a kernel bin file or `iso.sh` to produce an ISO file containing GRUB. `qemu.sh` will produce an ISO and run it in QEMU.

## Current features

Currently this project implements the [OSDev Wiki Meaty Skeleton tutorial](https://wiki.osdev.org/Meaty_Skeleton), using a framebuffer and PC Screen Font to display text instead of the VGA text buffer.

## Planned features

Currently moving to the x86_64 architecture. 

## Attribution

This project is licensed under the GPLv3 license or any later version. See COPYING for more info. All GPLv3 licensed files contain a header at the top of the file that explains their licensing in more detail.

`kernel/include/kernel/multiboot.h` was acquired from the GRUB source code under the MIT license. See https://opensource.org/license/mit and the file itself for more info.

This project incorporates content from the [OSDev Wiki](https://wiki.osdev.org), which is licensed under [CC0](https://creativecommons.org/publicdomain/zero/1.0/) (public domain dedication). While CC0 does not
require attribution, files containing significant portions or which are entirely made up of OSDev Wiki code are attributed in the GPLv3 licensing header located at the top of the file.
