# fieldOS

This is a small OS dev side project I'm making. I'm not really sure on what I want out of it right now - really I'm just using it to explore OS dev and improve my understanding of some lower-level stuff.

## Building

Building requires a cross-compiler to i686-elf, as well as GRUB to produce the final ISO (although, without GRUB, `build.sh` will still produce a .bin file for the kernel). Simply run `build.sh`, and `build/fieldOS.iso` will
contain GRUB along with the OS.

## Current features

Not much! Currently this OS has all the content from the [OSDev Wiki Bare Bones tutorial](https://wiki.osdev.org/Bare_Bones) implemented, albeit implemented with a framebuffer and a PSF font instead of using the VGA text mode
buffer.

## Planned features

I'm not 100% sure what kind of operating system I want to create. I at least plan to implement newlines and terminal scrolling and follow the [OSDev Meaty Skeleton tutorial](https://wiki.osdev.org/Meaty_Skeleton) (or at
least use it to help structure the OS better). After this, I plan to implement paging, interrupts, memory management, scheduling, userspace and a shell, although since this is a hobby project, I may not get that far.

## Attribution

Many thanks to the [OSDev Wiki](https://wiki.osdev.org/) for their invaluable OS resources.

`multiboot.h` acquired from the GRUB source code under MIT license.
