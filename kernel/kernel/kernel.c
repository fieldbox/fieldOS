#include <stdio.h>

#include <kernel/multiboot2.h>
#include <kernel/tty.h>

void kernel_main(void *mbi) {
  struct multiboot_tag_framebuffer *fb =
      (struct multiboot_tag_framebuffer *)find_multiboot_tag(
          mbi, MULTIBOOT_TAG_TYPE_FRAMEBUFFER);

  terminal_initialise(fb);

  terminal_writestring("Hello, World!");
}
