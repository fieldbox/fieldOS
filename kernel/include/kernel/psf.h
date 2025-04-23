#ifndef _KERNEL_PSF_H
#define _KERNEL_PSF_H

#include <stdint.h>

struct PSF_font {
  uint32_t magic;
  uint32_t version;
  uint32_t headersize;
  uint32_t flags;
  uint32_t numglyph;
  uint32_t bytesperglyph;
  uint32_t height;
  uint32_t width;
};

#endif
