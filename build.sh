#!/usr/local/bin/bash

nasm -f bin ./src/boot/boot.asm -o ./build/boot.bin
nasm -f elf32 ./src/kernel/entry.asm -o ./build/entry.o
i386-elf-gcc -m32 -ffreestanding -c ./src/kernel/kernel.c -o ./build/kernel.o

i386-elf-ld -o "build/full_kernel.bin" -Ttext 0x1000 build/*.o --oformat binary

cat ./build/boot.bin ./build/full_kernel.bin > ./build/os.bin

qemu-system-x86_64 -drive format=raw,file="./build/os.bin",index=0 -m 128M
