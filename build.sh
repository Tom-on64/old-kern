#!/usr/local/bin/bash

nasm -f bin ./src/boot/boot.asm -o ./build/boot.bin
nasm -f elf32 ./src/kernel/entry.asm -o ./build/entry.o
for file in ./src/kernel/*.c; do
    filename=$(basename "$file" .c)
    echo $file
    echo $filename
    i386-elf-gcc -m32 -ffreestanding -c "$file" -o "./build/$filename.o"
done

i386-elf-ld -o "build/full_kernel.bin" -Ttext 0x1000 build/*.o --oformat binary

cat ./build/boot.bin ./build/full_kernel.bin > ./build/os.bin

qemu-system-x86_64 -drive format=raw,file="./build/os.bin",index=0 -m 128M
