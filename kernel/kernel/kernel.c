/*   kernel.c - contains main kernel code
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

#include <kernel/multiboot2.h>
#include <kernel/tty.h>

void kernel_main(void *mbi) {
  struct multiboot_tag_framebuffer *fb =
      (struct multiboot_tag_framebuffer *)find_multiboot_tag(
          mbi, MULTIBOOT_TAG_TYPE_FRAMEBUFFER);

  terminal_initialise(fb);

  terminal_writestring("Hello, World!");
}
