#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include "framebuffer.h"
#include "multiboot2.h"
#include "psf.h"
#include <stddef.h>

void terminal_initialise(struct multiboot_tag_framebuffer *fb_tag);
void terminal_putchar(char c);
void terminal_write(const char *data, size_t size);
void terminal_writestring(const char *data);

#endif
