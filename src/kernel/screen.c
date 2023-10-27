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

int scroll(int offset) {
    if (offset < MAXROWS * MAXCOLS * 2) return offset;

    for (int i = 0; i < MAXROWS; i++) {
        memoryCopy((char*)getScreenOffset(0, i) + VIDEOADDRESS,
        (char*)getScreenOffset(0, i-1) + VIDEOADDRESS, 
        MAXCOLS * 2); 
    }

    char* lastLine = (char*)getScreenOffset(0, MAXROWS - 1) + VIDEOADDRESS;
    for (int i = 0; i < MAXCOLS * 2; i++) {
        lastLine[i] = 0;
    }

    offset -= 2 * MAXCOLS;
    return offset;
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
    offset = scroll(offset);
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
