#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "kitchen.h"
#include "staff.h"
#include "reciept.h"
#include "clear.h"
#include "userInterface.h"
#include "order.h" // Include order.h for Order class


// The main function will serve as an entry point for Emscripten,
// but the core logic will be driven by processCommand from userInterface.cpp
int main()
{
    // You might call userInterface() here if you were building a traditional console app.
    // For Emscripten, the JS frontend will call processCommand.
    // If you need main to run some setup, you can keep it, but it might be unused
    // unless you export it as `_main` and call it from JS.
    std::cout << "C++ application initialized. Waiting for commands from JavaScript..." << std::endl;
    return 0;
}