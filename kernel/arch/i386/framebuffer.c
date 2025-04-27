/*   framebuffer.c - implements framebuffer functions
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

#include <kernel/multiboot2.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void draw_pixel(struct multiboot_tag_framebuffer *fb_tag, uint32_t x,
                uint32_t y, uint32_t colour) {
  uint32_t row = y * fb_tag->common.framebuffer_pitch;
  uint32_t col = x * fb_tag->common.framebuffer_bpp / 8;
  uintptr_t base_address = fb_tag->common.framebuffer_addr;
  uint32_t *pixel_position = (uint32_t *)(base_address + row + col);
  *pixel_position = colour;
}

void framebuffer_scroll(struct multiboot_tag_framebuffer *fb_tag,
                        uint32_t pixels) {
  uint8_t *fb_ptr = (uint8_t *)(uintptr_t)fb_tag->common.framebuffer_addr;
  uint32_t pitch = fb_tag->common.framebuffer_pitch;
  uint32_t fb_height = fb_tag->common.framebuffer_height;
  for (uint32_t i = pitch; i < pitch * fb_height; i++) {
    if (i + pitch * pixels < pitch * fb_height) {
      fb_ptr[i] = fb_ptr[i + pitch * pixels];
    } else {
      fb_ptr[i] = 0;
    }
  }
}
