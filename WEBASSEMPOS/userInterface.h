#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include <vector>
#include <map>
#include <sstream> // For std::ostream&
#include <emscripten/emscripten.h> // For EMSCRIPTEN_KEEPALIVE

#include "kitchen.h"
#include "staff.h"
#include "order.h"

// Define Enum for the application's state machine FIRST
// This must come before any variables declared with this type.
enum AppState {
    STATE_INITIAL,
    STATE_ASK_PIN,
    STATE_VALIDATE_PIN,
    STATE_ASK_MAIN_MENU_CHOICE,
    STATE_MAIN_MENU_PROCESS,
    STATE_ASK_ROOM_CHOICE,
    STATE_SELECT_ROOM_PROCESS, // <--- THIS LINE HAS BEEN ADDED BACK
    STATE_ASK_TABLE_ID,
    STATE_PROCESS_TABLE_ID,
    STATE_ASK_PIZZA_MENU,
    STATE_SELECT_PIZZA_TYPE,
    STATE_ASK_PIZZA_SIZE,
    STATE_SELECT_PIZZA_SIZE,
    STATE_ASK_TOPPING,
    STATE_SELECT_TOPPING,
    STATE_PIZZA_DONE_ADD_ANOTHER,
    STATE_ADD_ANOTHER_PIZZA_PROCESS,
    STATE_FINAL_ORDER_CONFIRMATION,
    STATE_FINAL_ORDER_PROCESS,
    STATE_PAYMENT_PROMPT,
    STATE_PAYMENT_PROCESS,
    STATE_EXIT
};

// Define global state variables AFTER AppState enum is defined
extern AppState currentAppState;
extern Staff currentStaffUser;
extern std::string currentTableSelection;
extern std::vector<Pizza> currentPizzasInOrder;
extern Pizza currentPizzaBeingBuilt;
extern Order currentOrder; // Declare the global order object

// Function declarations
bool pinCheck(int pin);
void userInterface(); // Original main interface function, might not be used directly with Emscripten ccall

// Display functions (now take ostream& for capturing output)
void frontRoomDisplay(std::ostream& os);
void backRoomDisplay(std::ostream& os);
void barRoomDisplay(std::ostream& os);

// Emscripten-specific function for command processing
#ifdef __EMSCRIPTEN__
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    const char* processCommand(const char* js_input);
}
#endif

#endif // USERINTERFACE_H