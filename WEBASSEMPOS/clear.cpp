#include <iostream>
#include "clear.h"

void clearScreen() {
    // This function can be implemented to clear the screen based on the environment.
    // For web (Emscripten), clearing the console is typically handled by JavaScript.
    // For command line, you might use system("cls") on Windows or system("clear") on Unix-like.
    // In this web context, it might be left empty or trigger a JS function.
}