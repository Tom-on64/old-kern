#ifndef KEYBOARD_H
#define KEYBOARD_H

// Keycodes
#define BACKSPACE 0x0E
#define TAB 0x0F
#define LEFT_SHIFT_PRESS 0x2a
#define LEFT_SHIFT_RELEASE 0xaa
#define RIGHT_SHIFT_PRESS 0x36
#define RIGHT_SHIFT_RELEASE 0xb6
#define LEFT_CTRL_PRESS 0x1D
#define LEFT_CTRL_RELEASE 0x9D
#define RIGHT_CTRL_PRESS 0x1D
#define RIGHT_CTRL_RELEASE 0x9D
#define LEFT_ALT_PRESS 0x38
#define LEFT_ALT_RELEASE 0xB8
#define RIGHT_ALT_PRESS 0x38
#define RIGHT_ALT_RELEASE 0xB8

#define MAX_BUFFER_SIZE 256

void setupKeyboard();
char* read(char terminator);

#endif 

/*
unsigned char keyboardUS[128] = 
{
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*',
    0, ' ',
    0,                            // Caps lock
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // F1 - F10
    0,                            // Num lock
    0,                            // Scroll lock
    0,                            // Home
    0,                            // Up Arrow
    0,                            // Page up
    '-',
    0, // Left Arrow
    0,
    0, // Right Arrow
    '+',
    0, // End key
    0, // Down Arrow
    0, // Page Down
    0, // Insert Key
    0, // Delete Key
    0, 0, 0,
    0, 0, // F11, F12
    0,    // All other keys are undefined
};
*/
