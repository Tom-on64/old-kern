#include "screen.h"
#include "keyboard.h"
#include "system.h"
#include "stdint.h"
#include "stdbool.h"

typedef struct {
    char* command;
    void (*function)(char*);
} command_t;

void clearCommand(char* args) {
    clear(0x00);
}
void echoCommand(char* args) {
    print(args, 0x0b);
    printc('\n', 0x0b);
}
void helpCommand(char* args) {
    print(" --- Help ---\n", 0x0f);
    print("clear  - Clears the screen\n", 0x0f);
    print("echo   - Prints out the input\n", 0x0f);
    print("help   - Shows this help page\n", 0x0f);
}

command_t commands[] = {
    { "clear", clearCommand }, 
    { "echo", echoCommand }, 
    { "help", helpCommand }, 
};

void runCommand(char* input) {
    input = strtok(input, '\n');
    char* command = strtok(input, ' ');
    char* args = strtok(NULL, '\n');

    bool commandExists = false;
    for (uint32_t i = 0; i < sizeof(commands); i++) {
        if (strcmp(command, commands[i].command) == 0) {
            commands[i].function(args);
            commandExists = true;
            break;
        }
    }

    if (!commandExists) {
        print("Command '", 0x0c);
        print(command, 0x0c);
        print("' not found! Use 'help' for a list of commands.\n", 0x0c);
    }
}
