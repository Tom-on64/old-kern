#include "screen.h"
#include "lowend.h"

int getScreenOffset(int col, int row) {
    return (row * MAXCOLS + col) * 2;
}

int getCursor() {
    outb(CTRLREG, CURSOR_HIGH_BYTE);
    int offset = (int)inb(DATAREG) << 8;
    outb(CTRLREG, CURSOR_LOW_BYTE);
    offset += inb(DATAREG);

    return offset * 2;
}

void setCursor(int offset) {
    offset /= 2;
    outb(CTRLREG, CURSOR_HIGH_BYTE);
    outb(DATAREG, (uint8_t)(offset >> 8));
    outb(CTRLREG, CURSOR_LOW_BYTE);
    outb(DATAREG, (uint8_t)(offset));
}

void putc(char character, int col, int row, uint8_t attrByte) {
    uint8_t* videomem = (uint8_t*)VIDEOADDRESS;

    int offset;
    if (col >= 0 && col >= 0) offset = getScreenOffset(col, row);
    else offset = getCursor();

    if (character == '\n') {
        int rows = offset / (2 * MAXCOLS);
        offset = getScreenOffset(MAXCOLS - 1, rows);
    }
    else {
        *(videomem + offset) = character;
        *(videomem + offset + 1) = attrByte;
    }

    offset += 2;
    setCursor(offset);
}

void puts(char* string, int col, int row, uint8_t attrByte) {
    if (col >= 0 && row >= 0) setCursor(getScreenOffset(col, row));
    int i = 0;
    while (string[i] != 0) putc(string[i++], col, row, attrByte);
}

void print(char* string, uint8_t attrByte) {
    puts(string, -1, -1, attrByte);
}

void clear(uint8_t attrByte) {
    for (int row = 0; row < MAXROWS; row++) {
        for (int col = 0; col < MAXCOLS; col++) {
            putc(' ', col, row, attrByte);
        }
    }

    setCursor(getScreenOffset(0, 0));
}
