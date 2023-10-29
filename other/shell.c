#include "screen.h"
#include "stdbool.h"

char command[256];
char currentArg[256];
char* args[256];
uint8_t commandLength = 0;
uint8_t argc = 0;

void moveToBuffer(char* string) {
    int i = 0;
    bool inCommand = true;
    commandLength = 0;
    argc = 0;

    while (*(string + i) != '\0') {
        char character = *(string + i);
        if (character == ' ' && inCommand) { inCommand = false; return; }
        else if (character == ' ') {
            args
        }

        if (inCommand) { 
            command[i] = character;
            commandLength++;
        } else {
            currentArg[]
        }
    }
}

void eval(char* cmd) {
    moveToBuffer(cmd);


}
