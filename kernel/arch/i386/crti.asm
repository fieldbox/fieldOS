#    crti.asm 
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


section .init
global _init
_init:
	push ebp
	mov ebp, esp

section .fini
global _fini
_fini:
	push ebp
	mov ebp, esp
