#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "multiboot2.h"

void* find_multiboot_tag(void* mbi, multiboot_uint32_t tag_type) {
	struct multiboot_tag* tag = (struct multiboot_tag*)(uintptr_t)mbi + 8;
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
		tag = (struct multiboot_tag*)next;
	}
}

void draw_pixel(struct multiboot_tag_framebuffer* fb_tag, uint32_t x, uint32_t y, uint32_t color) {
	uint32_t row = y * fb_tag->common.framebuffer_pitch;
	uint32_t col = x * fb_tag->common.framebuffer_bpp / 8;
	uintptr_t base_address = fb_tag->common.framebuffer_addr;
	uint32_t* pixel_position = (uint32_t*) (base_address + row + col);
	*pixel_position = color;
}

void kernel_main(void* mbi)
{
	struct multiboot_tag_framebuffer* fb_tag = (struct multiboot_tag_framebuffer*)find_multiboot_tag(mbi, MULTIBOOT_TAG_TYPE_FRAMEBUFFER);
	uint32_t width = fb_tag->common.framebuffer_width;
	uint32_t height = fb_tag->common.framebuffer_height;
	for (uint32_t i = 0; i <= width; i++) {
		for (uint32_t j = 0; j <= height; j++) {
			draw_pixel(fb_tag, i, j, 0xFF0000);
		}
	}
}
