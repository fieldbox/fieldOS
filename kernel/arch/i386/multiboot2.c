/*   multiboot2.c - implements multiboot tag function
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

void *find_multiboot_tag(void *mbi, multiboot_uint32_t tag_type) {
  struct multiboot_tag *tag = (struct multiboot_tag *)(uintptr_t)mbi + 8;
  while (true) {
    if (tag->type == 0 && tag->size == 8) {
      return NULL;
    }

    if (tag->type == tag_type) {
      return tag;
    }

    uintptr_t next = (uintptr_t)tag + tag->size;
    int remainder = next % 8;
    next = remainder == 0 ? next : next + (8 - remainder);
    tag = (struct multiboot_tag *)next;
  }
}
