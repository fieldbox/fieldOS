/*   memset.c - implements memset function in libc
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

#include <string.h>

void *memset(void *bufptr, int value, size_t size) {
  unsigned char *buf = (unsigned char *)bufptr;
  for (size_t i = 0; i < size; i++)
    buf[i] = (unsigned char)value;
  return bufptr;
}
