/*   framebuffer.h - defines framebuffer functions for kernel
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
 */

#ifndef _KERNEL_FRAMEBUFFER_H
#define _KERNEL_FRAMEBUFFER_H

#include "multiboot2.h"
#include <stdint.h>

void draw_pixel(struct multiboot_tag_framebuffer *fb_tag, uint32_t x,
                uint32_t y, uint32_t colour);

void framebuffer_scroll(struct multiboot_tag_framebuffer *fb_tag,
                        uint32_t pixels);

#endif
