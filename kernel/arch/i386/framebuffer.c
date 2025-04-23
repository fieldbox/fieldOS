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
