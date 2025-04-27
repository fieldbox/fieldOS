/*   tty.h - defines terminal functions in kernel
 *   Copyright (C) 2025  fieldbox
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *   This file contains material from the OSDev Wiki
 *   <https://wiki.osdev.org/>, which is licensed under CC0 (public domain
 *   dedication).
 */

#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include "multiboot2.h"
#include <stddef.h>

void terminal_initialise(struct multiboot_tag_framebuffer *fb_tag);
void terminal_putchar(char c);
void terminal_write(const char *data, size_t size);
void terminal_writestring(const char *data);

#endif
