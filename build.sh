i686-elf-as boot.s -o build/boot.o
i686-elf-gcc -c kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
objcopy -O elf32-i386 -B i386 -I binary font.psfu build/font.o
i686-elf-gcc -T linker.ld -o build/fieldOS.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o build/font.o -lgcc
cp build/fieldOS.bin build/iso/boot/fieldOS.bin
if grub-file --is-x86-multiboot2 build/iso/boot/fieldOS.bin; then
	grub-mkrescue -o build/fieldOS.iso build/iso
else
	echo no multiboot header found
fi
