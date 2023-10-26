#ifndef OUTPUT_H
#define OUTPUT_H

#include "stdint.h"

// Initializes the screen output
void setupVideo();

// Prints a character to the output with color
void putch(char c, uint8_t color);

// Prints a string to the output with color
void puts(const char *str, uint8_t color);

// Moves down to a new line
void newLine();

#endif