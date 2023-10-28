#ifndef SCREEN_H
#define SCREEN_H

#include "stdint.h"

#define VIDEOADDRESS 0xb8000
#define MAXROWS 25
#define MAXCOLS 80
#define CURSOR_HIGH_BYTE 14
#define CURSOR_LOW_BYTE 15
#define CTRLREG 0x3d4
#define DATAREG 0x3d5

int getScreenOffset(int col, int row);
int getCursor();
void setCursor(int offset);
void putc(char character, int col, int row, uint8_t attrByte);
void puts(char* string, int col, int row, uint8_t attrByte);
void print(char* string, uint8_t attrByte);
void clear(uint8_t attrByte);

#endif
