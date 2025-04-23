#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/framebuffer.h>
#include <kernel/psf.h>
#include <kernel/tty.h>

extern char _binary_kernel_arch_i386_font_psfu_start[];

struct multiboot_tag_framebuffer *fb;

struct PSF_font *font =
    (struct PSF_font *)&_binary_kernel_arch_i386_font_psfu_start;

size_t cursor_x;
size_t cursor_y;
uint32_t terminal_fg;
uint32_t terminal_bg;

void terminal_initialise(struct multiboot_tag_framebuffer *fb_tag) {
  cursor_x = 0;
  cursor_y = 0;
  terminal_fg = 0xFFFFFF;
  terminal_bg = 0x000000;
  fb = fb_tag;
}

void terminal_setcolour(uint32_t fg, uint32_t bg) {
  terminal_fg = fg;
  terminal_bg = bg;
}

void terminal_putentryat(char c, int cx, int cy, uint32_t fg, uint32_t bg) {
  char *table =
      (char *)&_binary_kernel_arch_i386_font_psfu_start + font->headersize;
  char *glyph = table + c * font->bytesperglyph;
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

void terminal_scroll(void) { framebuffer_scroll(fb, font->height); }

void terminal_putchar(char c) {
  if (c == '\n') {
    cursor_x = 0;
    if (++cursor_y * font->height + font->height >=
        fb->common.framebuffer_height) {
      terminal_scroll();
      cursor_y--;
    }
  } else {
    terminal_putentryat(c, cursor_x, cursor_y, terminal_fg, terminal_bg);
    if (++cursor_x * (font->width + 1) + font->width >=
        fb->common.framebuffer_width) {
      cursor_x = 0;
      if (++cursor_y * font->height + font->height >=
          fb->common.framebuffer_height) {
        terminal_scroll();
        cursor_y--;
      }
    }
  }
}

void terminal_write(const char *data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    terminal_putchar(data[i]);
  }
}

void terminal_writestring(const char *data) {
  terminal_write(data, strlen(data));
}
