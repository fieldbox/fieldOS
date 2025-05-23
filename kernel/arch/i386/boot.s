#    boot.asm - implements bootstrap stub 
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

.set MAGIC, 0xE85250D6 /* multiboot magic number */
.set ARCH, 0 /* architecture 0 is 32-bit i386 */
.set HEADER_LENGTH, multiboot_header_end - multiboot_header_start /* length of multiboot header */
.set CHECKSUM, -(MAGIC + ARCH + HEADER_LENGTH) /* checksum to prove we are multiboot */ 

.set FRAMEBUFFER_TAG_TYPE, 5
.set FRAMEBUFFER_TAG_FLAGS, 0
.set FRAMEBUFFER_TAG_SIZE, framebuffer_tag_end - framebuffer_tag_start 
.set FRAMEBUFFER_TAG_WIDTH, 0
.set FRAMEBUFFER_TAG_HEIGHT, 0
.set FRAMEBUFFER_TAG_DEPTH, 0

/* multiboot2 header, in its own section so we can put it in the first 8KiB of the kernel */
.section .multiboot
.align 8
multiboot_header_start:
.long MAGIC
.long ARCH
.long HEADER_LENGTH
.long CHECKSUM

.align 8

framebuffer_tag_start:
.short FRAMEBUFFER_TAG_TYPE
.short FRAMEBUFFER_TAG_FLAGS
.long FRAMEBUFFER_TAG_SIZE
.long FRAMEBUFFER_TAG_WIDTH
.long FRAMEBUFFER_TAG_HEIGHT
.long FRAMEBUFFER_TAG_DEPTH
framebuffer_tag_end:

.align 8

.long 0
.long 8
multiboot_header_end:

/* defining the stack */
.section .bss /* in its own section so we can mark it nobits to reduce kernel file size */
.align 16 /* stack must be 16-byte aligned */
stack_bottom:
.skip 16384 /* allocate 16KiB to the stack */
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	
	/* set up the stack by setting the stack pointer register esp*/
	mov $stack_top, %esp

	call _init

	push %ebx
	call kernel_main

	cli
1:	hlt
	jmp 1b

.size _start, . - _start
