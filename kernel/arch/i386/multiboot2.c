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
