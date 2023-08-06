extern void main() {
    *(char *)0xb8000 = 'A'; // Write A to the video memory
    return;
}