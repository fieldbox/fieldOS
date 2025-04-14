.set MAGIC, 0xE85250D6 /* multiboot magic number */
.set ARCH, 0 /* architecture 0 is 32-bit i386 */
.set LENGTH, 24 /* length of multiboot header */
.set CHECKSUM, -(MAGIC + ARCH + LENGTH) /* checksum to prove we are multiboot */ 

/* multiboot2 header, in its own section so we can put it in the first 8KiB of the kernel */
.section .multiboot
.align 4
.long MAGIC
.long ARCH
.long LENGTH
.long CHECKSUM
.long 0
.long 8

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

	call kernel_main

	cli
1:	hlt
	jmp 1b

.size _start, . - _start
