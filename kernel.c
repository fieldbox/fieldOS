#include "multiboot2.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern char _binary_font_psfu_start[];
struct multiboot_tag_framebuffer* fb;

#define PSF_FONT_MAGIC 0x864ab572

typedef struct {
  uint32_t magic;
  uint32_t version;
  uint32_t headersize;
  uint32_t flags;
  uint32_t numglyph;
  uint32_t bytesperglyph;
  uint32_t height;
  uint32_t width;
} PSF_font;

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

void draw_pixel(struct multiboot_tag_framebuffer* fb_tag, uint32_t x,
                uint32_t y, uint32_t colour) {
  uint32_t row = y * fb_tag->common.framebuffer_pitch;
  uint32_t col = x * fb_tag->common.framebuffer_bpp / 8;
  uintptr_t base_address = fb_tag->common.framebuffer_addr;
  uint32_t* pixel_position = (uint32_t*)(base_address + row + col);
  *pixel_position = colour;
}

size_t str_len(const char* str) {
  size_t len = 0;
  while (str[len])
    len++;
  return len;
}

size_t cursor_x;
size_t cursor_y;
uint32_t terminal_fg;
uint32_t terminal_bg;

void terminal_initialise(void) {
  cursor_x = 0;
  cursor_y = 0;
  terminal_fg = 0xFFFFFF;
  terminal_bg = 0x000000;
}

void terminal_setcolour(uint32_t fg, uint32_t bg) {
  terminal_fg = fg;
  terminal_bg = bg;
}

void terminal_putentryat(char c, int cx, int cy, uint32_t fg, uint32_t bg) {
  PSF_font* font = (PSF_font*)&_binary_font_psfu_start;
  char* table = (char*)&_binary_font_psfu_start + font->headersize;
  char* glyph = table + c * font->bytesperglyph;
  uint32_t y = cy * font->height;
  for (uint32_t i = 0; i < font->height; i++) {
    uint32_t x = cx * (font->width + 1);
    for (uint32_t j = 0; j < font->width; j++) {
      uint8_t bit = (glyph[i] >> (font->width - 1 - j)) & 0x1;
      uint32_t colour = bit == 0x1 ? fg : bg;
      draw_pixel(fb, x + j, y + i, colour);
    }
  }
}

void terminal_putchar(char c) {
  terminal_putentryat(c, cursor_x, cursor_y, terminal_fg, terminal_bg);
  if (++cursor_x == fb->common.framebuffer_width) {
    cursor_x = 0;
    if (++cursor_y == fb->common.framebuffer_height) {
      cursor_y = 0;
    }
  }
}

void terminal_write(const char* data, size_t size) {
  for (size_t i = 0; i < size; i++)
    terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
  terminal_write(data, str_len(data));
}

void kernel_main(void* mbi) {
  fb = (struct multiboot_tag_framebuffer*)find_multiboot_tag(
      mbi, MULTIBOOT_TAG_TYPE_FRAMEBUFFER);

  terminal_initialise();

  terminal_writestring("Hello, kernel World!\n");
}
