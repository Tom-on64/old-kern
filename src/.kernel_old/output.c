#include "output.h"
#include "stdint.h"

// Memory-mapped I/O base address for text mode screen buffer
#define SCREEN_BASE_ADDRESS 0xb8000

// I/O port addresses for VGA screen
#define VGA_CTRL_REGISTER 0x3D4
#define VGA_DATA_REGISTER 0x3D5
#define CURSOR_HIGH_BYTE 14
#define CURSOR_LOW_BYTE 15

// VGA properties
#define VGA_ROWS 25
#define VGA_COLUMNS 80

// Function to write a value to an I/O port
void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %0, %1" ::"a"(value), "Nd"(port));
}

// Read a byte from an I/O port
uint8_t inb(uint16_t port) {
    uint8_t result;
    asm volatile("inb %1, %0"
        : "=a"(result)
        : "Nd"(port));
    return result;
}

// Scrolls down
void scroll() {
    // Scroll the screen up by copying each row's content to the row above
    for (int row = 0; row < VGA_ROWS - 1; row++) {
        for (int col = 0; col < VGA_COLUMNS; col++) {
            uint16_t* screenBuffer = (uint16_t*)SCREEN_BASE_ADDRESS;
            uint16_t offset = (row * VGA_COLUMNS) + col;
            uint16_t nextOffset = ((row + 1) * VGA_COLUMNS) + col;
            screenBuffer[offset] = screenBuffer[nextOffset];
        }
    }

    // Clear the last row
    for (int col = 0; col < VGA_COLUMNS; col++) {
        uint16_t* screenBuffer = (uint16_t*)SCREEN_BASE_ADDRESS;
        uint16_t offset = ((VGA_ROWS - 1) * VGA_COLUMNS) + col;
        screenBuffer[offset] = (' ' | (0b00000111 << 8));
    }
}

// Sets the position of the cursor
void setCursorPosition(uint8_t row, uint8_t col) {
    uint16_t position = (row * VGA_COLUMNS) + col;

    // Send command to VGA control register
    outb(VGA_CTRL_REGISTER, CURSOR_HIGH_BYTE);
    // Send high byte of position
    outb(VGA_DATA_REGISTER, (position >> 8) & 0xFF);

    // Send command to VGA control register
    outb(VGA_CTRL_REGISTER, CURSOR_LOW_BYTE);
    // Send low byte of position
    outb(VGA_DATA_REGISTER, position & 0xFF);
}

// Gets the position of the cursor
void getCursorPosition(uint8_t* row, uint8_t* column) {
    // Read the cursor location from the VGA control registers
    outb(VGA_CTRL_REGISTER, CURSOR_HIGH_BYTE);
    *row = inb(VGA_DATA_REGISTER);

    outb(VGA_CTRL_REGISTER, CURSOR_LOW_BYTE);
    *column = inb(VGA_DATA_REGISTER);
}

// Moves down to a new line
void newLine() {
    uint8_t currentRow, currentCol;
    getCursorPosition(&currentRow, &currentCol);

    // Check if we need to scroll the screen up
    if (currentRow >= VGA_ROWS - 1) {
        scroll();
    } else {
        // Move to the next row
        setCursorPosition(currentRow + 1, 0);
    }
}

// Initializes the screen output
void setupVideo() {
    setCursorPosition(0, 0);

    // Clear the screen by writing spaces to every character cell
    for (int i = 0; i < VGA_COLUMNS * VGA_ROWS; ++i) {
        volatile char* vidmem = (char*)SCREEN_BASE_ADDRESS;
        vidmem[i * 2] = ' ';
        vidmem[i * 2 + 1] = 0b00000111; // Light gray on black background
    }
}

// Prints a character to the output
void putch(char c, uint8_t color) {
    // Get the current cursor position
    uint8_t currentRow, currentColumn;
    getCursorPosition(&currentRow, &currentColumn);

    // Calculate the linear offset for the current cursor position
    uint16_t offset = (currentRow * VGA_COLUMNS) + currentColumn;

    // Calculate the memory-mapped I/O address for the screen buffer
    uint16_t* screenBuffer = (uint16_t*)SCREEN_BASE_ADDRESS;

    // Combine the character and attribute to form the screen buffer entry
    uint16_t screenEntry = (uint16_t)c | ((uint16_t)color << 8);

    // Write the character to the screen buffer
    screenBuffer[offset] = screenEntry;

    // Move the cursor to the next column
    currentColumn++;

    // If we've reached the end of the line, move to the next row
    if (currentColumn >= VGA_COLUMNS) {
        currentColumn = 0;
        currentRow++;
    }

    // Update the cursor position
    setCursorPosition(currentRow, currentColumn);
}

// Prints a string to the output
void puts(const char* str, uint8_t color) {
    int i = 0;
    while (str[i] != 0) // Breaks at null
    {
        char c = str[i];

        if (c == '\n')
            newLine();
        else
            putch(c, color);

        i++;
    }
}
