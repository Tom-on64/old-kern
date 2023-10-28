#include "system.h"
#include "screen.h"
#include "irq.h"
#include "keyboard.h"
#include "stdbool.h"

const char keyMap[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', 
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.', // Numpad
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
const char shiftKeyMap[128] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0, 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

bool shiftPressed = false;
bool altPressed = false;
bool ctrlPressed = false;

uint16_t bufferSize = 0;
char buffer[MAX_BUFFER_SIZE];
char bufferTerminator;
bool echo = false;
bool canBackspace = false;

void keyboardHandler(struct regs* r) {
    uint8_t scancode;
    scancode = inb(0x60);

    // Modifier key check
    if (scancode == LEFT_SHIFT_PRESS || scancode == RIGHT_SHIFT_PRESS) shiftPressed = true;
    else if (scancode == LEFT_SHIFT_RELEASE || scancode == RIGHT_SHIFT_RELEASE) shiftPressed = false;
    if (scancode == LEFT_ALT_PRESS || scancode == RIGHT_ALT_PRESS) altPressed = true;
    else if (scancode == LEFT_ALT_RELEASE || scancode == RIGHT_ALT_RELEASE) altPressed = false;
    if (scancode == LEFT_CTRL_PRESS || scancode == RIGHT_CTRL_PRESS) ctrlPressed = true;
    else if (scancode == LEFT_CTRL_RELEASE || scancode == RIGHT_CTRL_RELEASE) ctrlPressed = false;

    // Keymaps
    char character = keyMap[scancode];
    if (shiftPressed) character = shiftKeyMap[scancode];

    if (scancode & 0x80) { // Key released
    } else if (character != 0) {
        if (!canBackspace && character == '\b') return;
        if (echo) printc(character, 0x0f);
        buffer[bufferSize] = character;
        if (character == '\b') bufferSize--;
        else bufferSize++;
        if (bufferSize > 0) canBackspace = true;
        else canBackspace = false;
    }
}

void setupKeyboard() {
    installIrqHandler(1, keyboardHandler);
}

char* read(char terminator) {
    bufferSize = 0;
    echo = true;

    while(buffer[bufferSize-1] != terminator && bufferSize < MAX_BUFFER_SIZE);

    echo = false;
    canBackspace = false;
    buffer[bufferSize] = '\0';

    return &buffer[0];
}
