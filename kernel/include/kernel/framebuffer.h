#ifndef _KERNEL_FRAMEBUFFER_H
#define _KERNEL_FRAMEBUFFER_H

#include "multiboot2.h"
#include <stdint.h>

void draw_pixel(struct multiboot_tag_framebuffer *fb_tag, uint32_t x,
                uint32_t y, uint32_t colour);

void framebuffer_scroll(struct multiboot_tag_framebuffer *fb_tag,
                        uint32_t pixels);

#endif
