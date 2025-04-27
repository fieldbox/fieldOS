%define MAGIC 0xE85250D6 ; multiboot magic number 
%define ARCH 0 ; architecture 0 is 32-bit i386 
%define HEADER_LENGTH multiboot_header_end - multiboot_header_start ; length of multiboot header 
%define CHECKSUM -(MAGIC + ARCH + HEADER_LENGTH) ; checksum to prove we are multiboot  

%define FRAMEBUFFER_TAG_TYPE 5
%define FRAMEBUFFER_TAG_FLAGS 0
%define FRAMEBUFFER_TAG_SIZE framebuffer_tag_end - framebuffer_tag_start 
%define FRAMEBUFFER_TAG_WIDTH 0
%define FRAMEBUFFER_TAG_HEIGHT 0
%define FRAMEBUFFER_TAG_DEPTH 0

; multiboot2 header, in its ownsection so we can put it in the first 8KiB of the kernel 
section .multiboot
align 8
multiboot_header_start:
dd MAGIC
dd ARCH
dd HEADER_LENGTH
dd CHECKSUM

align 8

framebuffer_tag_start:
dw FRAMEBUFFER_TAG_TYPE
dw FRAMEBUFFER_TAG_FLAGS
dd FRAMEBUFFER_TAG_SIZE
dd FRAMEBUFFER_TAG_WIDTH
dd FRAMEBUFFER_TAG_HEIGHT
dd FRAMEBUFFER_TAG_DEPTH
framebuffer_tag_end:

align 8

dd 0
dd 8
multiboot_header_end:

; defining the stack 
section .bss ; in its own section so we can mark it nobits to reduce kernel file size 
align 16 ; stack must be 16-byte aligned 
stack_bottom:
resb 16384 ; allocate 16KiB to the stack 
stack_top:

extern _init
extern kernel_main

section .text
global _start
_start:
	call _init

	push ebx
	call kernel_main

	cli
.loop:
	hlt
	jmp .loop 
