#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream> // For stringstream to capture output
#include <iomanip> // For std::fixed, std::setprecision
#include "kitchen.h"
#include "staff.h"
#include "userInterface.h"
#include "reciept.h"
#include "clear.h" // Include for clearScreen()
#include "order.h" // Include for Order class

// Define global state variables declared in userInterface.h
// These must be defined (not just declared) in one .cpp file
AppState currentAppState = STATE_INITIAL;
Staff currentStaffUser;
std::string currentTableSelection = "";
std::vector<Pizza> currentPizzasInOrder;
Pizza currentPizzaBeingBuilt;
Order currentOrder;

// Helper function to convert string to int with error handling
int stringToInt(const std::string& s) {
    try {
        return std::stoi(s);
    } catch (const std::invalid_argument& e) {
        return -1; // Indicate error
    } catch (const std::out_of_range& e) {
        return -1; // Indicate error
    }
}

// Map for table IDs for front, back, and bar rooms (copied from original)
std::map<int, std::string> tableID = {
    {1, "Table 1"}, {2, "Table 2"}, {3, "Table 3"}, {4, "Table 4"}, {5, "Table 5"}, {6, "Table 6"}, {7, "Table 7"},
    {8, "Table 8"}, {9, "Table 9"}, {10, "Table 10"}, {11, "Table 11"}, {12, "Table 12"}, {13, "Table 13"}, {14, "Table 14"},
    {15, "Table 15"}, {16, "Table 16"}, {17, "Table 17"}, {18, "Table 18"}, {19, "Table 19"}, {20, "Table 20"},
    {21, "Table 21"}, {22, "Table 22"}, {23, "Table 23"}, {24, "Table 24"}, {25, "Table 25"}, {26, "Table 26"},
    {27, "Table 27"}, {28, "Table 28"}, {29, "Table 29"}, {30, "Table 30"}
};

std::map<int, std::string> barSeatId = {
    {1, "Bar Seat 1"}, {2, "Bar Seat 2"}, {3, "Bar Seat 3"}, {4, "Bar Seat 4"}, {5, "Bar Seat 5"},
    {6, "Bar Seat 6"}, {7, "Bar Seat 7"}, {8, "Bar Seat 8"}, {9, "Bar Seat 9"}, {10, "Bar Seat 10"},
    {11, "Bar Seat 11"}, {12, "Bar Seat 12"}, {13, "Bar Seat 13"}, {14, "Bar Seat 14"}, {15, "Bar Seat 15"},
    {16, "Bar Seat 16"}, {17, "Bar Seat 17"}, {18, "Bar Seat 18"}, {19, "Bar Seat 19"}, {20, "Bar Seat 20"}
};


// --- Display Functions (now take ostream& to capture output) ---
void frontRoomDisplay(std::ostream& os) {
    os << R"(+----+    +--------------+
| 1  |    |    Table 7   |
|    |    |              |
+----+    +--------------+
+----+    +--------------+
| 2  |    |    Table 6   |
|    |    |              |
+----+    +--------------+
+----+    +--------------+
| 3  |    |    Table 5   |
|    |    |              |
+----+    +--------------+
+----+
| 4  |
|    |
+----+                    )" << std::endl;
}

void backRoomDisplay(std::ostream& os) {
    os << R"(                +------+      +------+
+------+        | Table|      | Table|
|      |        |  23  |      |  24  |
|Table |        +------+      +------+
| 25   |                              
|      |        +------+        +----+
+------+        | Table|        | 16 |
                |   21 |        |    |
+------+        +------+        +----+
|      |        +------+      +------+
|Table |        | Table|      | Table|
| 26   |        |   20 |      |   14 |
|      |        +------+      +------+
+------+        +------+      +------+
                | Table|      | Table|
+------+        |   19 |      |   12 |
|      |        +------+      +------+
|Table |        +------+      +------+
| 27   |        | Table|      | Table|
|      |        |   18 |      |   10 |
+------+        +------+      +------+
                                      
      *****                           
    **     **                         
   *         *                        
  *   Table   *                       
  *    17     *                       
   *         *                        
    **     **                         
      *****                           )" << std::endl;
}

void barRoomDisplay(std::ostream& os) {
    os << R"(    +---++---++---++---++---+                                        
    | 5 || 4 || 3 || 2 || 1 |                                        
    +---++---++---++---++---+                                        
+---+                                                                
| 6 |                                                                
+---+                                                                
+---+                                                       +-------+
| 7 |                                                       |       |
+---+                                                       |   65  |
+---+                                                       +-------+
| 8 |                                                       +-------+
+---+                +---+       +-----+       +--------+   |       |
+---+                |32 |       |     |       |        |   |   64  |
| 9 |                |   |       |  40 |       |   53   |   +-------+
+---+                +---+       |     |       |        |   +-------+
+---+                +---+       +-----+       +--------+   |       |
| 10|                |31 |       +-----+       +--------+   |   63  |
+---+                |   |       |     |       |        |   +-------+
+---+                +---+       |  41 |       |   50   |   +-------+
| 11|                +---+       |     |       |        |   |       |
+---+                |30 |       +-----+       +--------+   |   62  |
+---+                |   |                                  +-------+
| 12|                +---+                                  +-------+
+---+                                                       |       |
+---+                                                       |   61  |
| 13|                                                       +-------+
+---+                                                       +-------+
+---+                                                       |       |
| 14|                                                       |   60  |
+---+                                                       +-------+
+---+                                                                
| 15|                                                                
+---+                                                                
+---+                                                                
| 16|                                                                
+---+                                                                
+---+                                                                
| 17|                                                                
+---+                                                                
+---+ +---++---+                                                     
| 18| | 19|| 20|                                                     
+---+ +---++---+                                                     )" << std::endl;
}


// --- Main Command Processing Function ---
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    const char* processCommand(const char* js_input) {
        std::string input_str(js_input);
        static std::string s_persistent_output_buffer; // Static string to hold output
        std::stringstream output_ss; // Use a local stringstream to build output
        int int_choice = -1; // Initialize with an invalid choice
        std::string string_choice;

        // ONLY attempt to parse input as an integer if the string is not empty
        if (!input_str.empty()) {
            try {
                int_choice = std::stoi(input_str);
            } catch (const std::invalid_argument& e) {
                // Not an integer, keep int_choice as -1
            } catch (const std::out_of_range& e) {
                // Too large/small for int, keep as -1
            }
        }
        string_choice = input_str; // Always keep the string version too

        // State Machine Logic
        switch (currentAppState) {
            case STATE_INITIAL: // This state is usually only briefly entered once
            case STATE_ASK_PIN: {
                output_ss << "\nPlease Enter your Pin" << std::endl;
                currentAppState = STATE_VALIDATE_PIN;
                break;
            }
            case STATE_VALIDATE_PIN: {
                if (pinCheck(int_choice)) {
                    // Set staff details based on valid pin
                    if (int_choice == 4493) {
                        currentStaffUser.setName("Oli");
                        currentStaffUser.setPosition("Manager");
                        currentStaffUser.setPin(4493); // Set pin too for completeness
                        currentStaffUser.isAdmin = true;
                    } else if (int_choice == 1739) {
                        currentStaffUser.setName("Francesco");
                        currentStaffUser.setPosition("Server");
                        currentStaffUser.setPin(1739); // Set pin too for completeness
                        currentStaffUser.isAdmin = false;
                    }
                    output_ss << "\nWelcome " << currentStaffUser.getName() << std::endl;
                    currentAppState = STATE_ASK_MAIN_MENU_CHOICE;
                    // Immediately transition to next prompt
                    // No break here, fall through to display menu
                } else {
                    output_ss << "\nInvalid Pin, please try again" << std::endl;
                    currentAppState = STATE_ASK_PIN; // Go back to asking pin explicitly
                    // No break here, fall through to prompt for pin again
                }
            } // End STATE_VALIDATE_PIN case
            case STATE_ASK_MAIN_MENU_CHOICE: { // New state for main menu
                output_ss << "\n--- Main Menu ---" << std::endl;
                output_ss << "1. Create Order" << std::endl;
                output_ss << "2. View Orders" << std::endl;
                output_ss << "3. Manage Staff (Not Implemented)" << std::endl;
                output_ss << "4. Exit" << std::endl;
                output_ss << "Please select an option: " << std::endl;
                currentAppState = STATE_MAIN_MENU_PROCESS;
                break;
            }
            case STATE_MAIN_MENU_PROCESS: {
                if (int_choice == 1) {
                    currentAppState = STATE_ASK_ROOM_CHOICE;
                    // Fall through to STATE_ASK_ROOM_CHOICE to display its prompt
                } else if (int_choice == 2) {
                    output_ss << "\nViewing orders (Not fully implemented yet)." << std::endl;
                    currentOrder.displayOrder(output_ss); // Assuming displayOrder takes ostream&
                    currentAppState = STATE_ASK_MAIN_MENU_CHOICE; // Loop back
                    break;
                } else if (int_choice == 3) {
                    output_ss << "\nStaff management not yet implemented." << std::endl;
                    currentAppState = STATE_ASK_MAIN_MENU_CHOICE; // Loop back
                    break;
                } else if (int_choice == 4) {
                    output_ss << "\nExiting application. Goodbye!" << std::endl;
                    currentAppState = STATE_EXIT;
                    break;
                } else {
                    output_ss << "\nInvalid choice, please enter 1, 2, 3, or 4." << std::endl;
                    currentAppState = STATE_ASK_MAIN_MENU_CHOICE; // Re-prompt
                    break;
                }
            } // End STATE_MAIN_MENU_PROCESS case
            case STATE_ASK_ROOM_CHOICE: {
                output_ss << "\n--- Select Room ---" << std::endl;
                output_ss << "1. Front Room" << std::endl;
                output_ss << "2. Back Room" << std::endl;
                output_ss << "3. Bar Room" << std::endl;
                output_ss << "Please select a room: " << std::endl;
                currentAppState = STATE_SELECT_ROOM_PROCESS;
                break;
            }
            case STATE_SELECT_ROOM_PROCESS: {
                if (int_choice >= 1 && int_choice <= 3) {
                    currentOrder.setRoomChoice(int_choice); // Store room choice
                    currentAppState = STATE_ASK_TABLE_ID; // Transition to new state to display tables
                    break; // Crucial break: ensures next call processes table ID
                } else {
                    output_ss << "\nInvalid room choice. Please enter 1, 2, or 3." << std::endl;
                    currentAppState = STATE_ASK_ROOM_CHOICE; // Re-prompt
                    break;
                }
            } // End STATE_SELECT_ROOM_PROCESS case
            case STATE_ASK_TABLE_ID: { // NEW STATE: Displays room maps and asks for table ID
                output_ss << "\n--- Select Table/Seat ---" << std::endl;
                if (currentOrder.getRoomChoice() == 1) {
                    frontRoomDisplay(output_ss);
                } else if (currentOrder.getRoomChoice() == 2) {
                    backRoomDisplay(output_ss);
                } else if (currentOrder.getRoomChoice() == 3) {
                    barRoomDisplay(output_ss);
                }
                output_ss << "\nPlease select a table/seat ID: " << std::endl;
                currentAppState = STATE_PROCESS_TABLE_ID; // Transition to new state to process table input
                break;
            }
            case STATE_PROCESS_TABLE_ID: { // NEW STATE: Processes the entered table ID
                int table_seat_id = int_choice; // This IS the table ID input from the user

                bool valid_selection = false;

                if (currentOrder.getRoomChoice() == 1) { // Front Room
                    // Assuming front room tables 1-10
                    if (tableID.count(table_seat_id) && table_seat_id >= 1 && table_seat_id <= 10) {
                        currentTableSelection = tableID[table_seat_id];
                        valid_selection = true;
                    }
                } else if (currentOrder.getRoomChoice() == 2) { // Back Room
                    // Assuming back room tables 11-30
                    if (tableID.count(table_seat_id) && table_seat_id >= 11 && table_seat_id <= 30) {
                        currentTableSelection = tableID[table_seat_id];
                        valid_selection = true;
                    }
                } else if (currentOrder.getRoomChoice() == 3) { // Bar Room
                    // Bar room has two sets of IDs: 1-20 (barSeatId) and 55-65 (tableID)
                    if (barSeatId.count(table_seat_id) && table_seat_id >= 1 && table_seat_id <= 20) {
                        currentTableSelection = barSeatId[table_seat_id];
                        valid_selection = true;
                    } else if (tableID.count(table_seat_id) && table_seat_id >= 55 && table_seat_id <= 65) {
                        currentTableSelection = tableID[table_seat_id];
                        valid_selection = true;
                    }
                }

                if (valid_selection) {
                    currentOrder.setTable(currentTableSelection);
                    currentOrder.setServer(currentStaffUser); // Assign the current logged-in staff
                    output_ss << "\nYou have selected " << currentTableSelection << std::endl;
                    currentAppState = STATE_ASK_PIZZA_MENU;
                    break; // Move to the next phase of order creation
                } else {
                    output_ss << "\nInvalid table/seat ID for the selected room. Please try again." << std::endl;
                    currentAppState = STATE_ASK_TABLE_ID; // Go back to display maps and re-prompt
                    break;
                }
            } // End STATE_PROCESS_TABLE_ID case
            case STATE_ASK_PIZZA_MENU: {
                output_ss << "\n--- Pizza Menu ---" << std::endl;
                Pizza::displayPizzaMenu(output_ss); // Corrected call with scope resolution
                output_ss << "Please select a pizza type (1-10): " << std::endl;
                currentAppState = STATE_SELECT_PIZZA_TYPE;
                break;
            }
            case STATE_SELECT_PIZZA_TYPE: {
                if (int_choice >= 1 && int_choice <= 10) { // Assuming 10 pizza types
                    currentPizzaBeingBuilt = Pizza::createPizza(int_choice); // Use static factory method
                    if (currentPizzaBeingBuilt.getType() != "Unknown") {
                        output_ss << "\nYou selected: " << currentPizzaBeingBuilt.getType() << std::endl;
                        currentAppState = STATE_ASK_PIZZA_SIZE;
                        // Fall through to STATE_ASK_PIZZA_SIZE
                    } else {
                        output_ss << "\nInvalid pizza selection. Please try again." << std::endl;
                        currentAppState = STATE_ASK_PIZZA_MENU; // Re-prompt
                        break;
                    }
                } else {
                    output_ss << "\nInvalid pizza selection. Please enter a number between 1 and 10." << std::endl;
                    currentAppState = STATE_ASK_PIZZA_MENU; // Re-prompt
                    break;
                }
            } // End STATE_SELECT_PIZZA_TYPE case
            case STATE_ASK_PIZZA_SIZE: {
                output_ss << "\n--- Select Pizza Size ---" << std::endl;
                output_ss << "1. 12 inches (Standard)" << std::endl;
                output_ss << "2. 16 inches" << std::endl;
                output_ss << "Please select a size: " << std::endl;
                currentAppState = STATE_SELECT_PIZZA_SIZE;
                break;
            }
            case STATE_SELECT_PIZZA_SIZE: {
                if (int_choice == 1) {
                    currentPizzaBeingBuilt.setSize(12);
                    output_ss << "\nSize set to 12 inches." << std::endl;
                    currentAppState = STATE_ASK_TOPPING;
                    // Fall through to STATE_ASK_TOPPING
                } else if (int_choice == 2) {
                    currentPizzaBeingBuilt.setSize(16);
                    output_ss << "\nSize set to 16 inches." << std::endl;
                    currentAppState = STATE_ASK_TOPPING;
                    // Fall through to STATE_ASK_TOPPING
                } else {
                    output_ss << "\nInvalid size choice. Please enter 1 or 2." << std::endl;
                    currentAppState = STATE_ASK_PIZZA_SIZE; // Re-prompt
                    break;
                }
            } // End STATE_SELECT_PIZZA_SIZE case
            case STATE_ASK_TOPPING: {
                output_ss << "\n--- Select Toppings ---" << std::endl;
                Pizza::displayPizzaToppingsOptions(output_ss); // Corrected call with scope resolution
                output_ss << "Enter topping ID (or 0 to finish adding toppings): " << std::endl;
                currentAppState = STATE_SELECT_TOPPING;
                break;
            }
            case STATE_SELECT_TOPPING: {
                if (int_choice == 0) {
                    currentAppState = STATE_PIZZA_DONE_ADD_ANOTHER;
                    // Fall through to STATE_PIZZA_DONE_ADD_ANOTHER
                } else if (int_choice >= 1 && int_choice <= currentPizzaBeingBuilt.getToppingsMap().size()) {
                    currentPizzaBeingBuilt.addTopping(int_choice);
                    output_ss << "\nAdded: " << currentPizzaBeingBuilt.getToppingsMap()[int_choice] << std::endl;
                    currentAppState = STATE_ASK_TOPPING; // Ask for another topping
                    // Fall through to STATE_ASK_TOPPING to re-display options
                } else {
                    output_ss << "\nInvalid topping ID. Please enter a valid number or 0 to finish." << std::endl;
                    currentAppState = STATE_ASK_TOPPING; // Re-prompt
                    break;
                }
            } // End STATE_SELECT_TOPPING case
            case STATE_PIZZA_DONE_ADD_ANOTHER: {
                output_ss << "\nYour pizza is ready!" << std::endl;
                output_ss << "Type: " << currentPizzaBeingBuilt.getType() << std::endl;
                output_ss << "Size: " << currentPizzaBeingBuilt.getSize() << " inches" << std::endl;
                output_ss << "Toppings: ";
                if (currentPizzaBeingBuilt.getToppings().empty()) {
                    output_ss << "None." << std::endl;
                } else {
                    for (const auto& topping : currentPizzaBeingBuilt.getToppings()) {
                        output_ss << topping << ", ";
                    }
                    output_ss << std::endl;
                }
                output_ss << "Price: $" << std::fixed << std::setprecision(2) << currentPizzaBeingBuilt.getPrice() << std::endl;

                currentOrder.addPizza(currentPizzaBeingBuilt);
                currentPizzasInOrder.push_back(currentPizzaBeingBuilt); // Keep track for display/receipt

                output_ss << "\nAdd another pizza? (Y/N): " << std::endl;
                currentAppState = STATE_ADD_ANOTHER_PIZZA_PROCESS;
                break;
            }
            case STATE_ADD_ANOTHER_PIZZA_PROCESS: {
                if (string_choice == "Y" || string_choice == "y") {
                    currentPizzaBeingBuilt = Pizza(); // Reset for a new pizza
                    currentAppState = STATE_ASK_PIZZA_MENU; // Go back to start pizza creation
                    // Fall through to STATE_ASK_PIZZA_MENU
                } else if (string_choice == "N" || string_choice == "n") {
                    currentAppState = STATE_FINAL_ORDER_CONFIRMATION;
                    // Fall through to STATE_FINAL_ORDER_CONFIRMATION
                } else {
                    output_ss << "\nInvalid choice. Please enter Y or N." << std::endl;
                    currentAppState = STATE_PIZZA_DONE_ADD_ANOTHER; // Re-prompt
                    break;
                }
            } // End STATE_ADD_ANOTHER_PIZZA_PROCESS case
            case STATE_FINAL_ORDER_CONFIRMATION: {
                output_ss << "\n--- Order Summary ---" << std::endl;
                currentOrder.displayOrder(output_ss); // Display the full order
                output_ss << "\nConfirm order and proceed to payment? (Y/N): " << std::endl;
                currentAppState = STATE_FINAL_ORDER_PROCESS;
                break;
            }
            case STATE_FINAL_ORDER_PROCESS: {
                if (string_choice == "Y" || string_choice == "y") {
                    currentAppState = STATE_PAYMENT_PROMPT;
                    // Fall through to STATE_PAYMENT_PROMPT
                } else if (string_choice == "N" || string_choice == "n") {
                    output_ss << "\nOrder cancelled. Returning to main menu." << std::endl;
                    currentOrder = Order(); // Clear the order
                    currentPizzasInOrder.clear(); // Clear pizzas
                    currentAppState = STATE_ASK_MAIN_MENU_CHOICE; // Go back to main menu
                    break;
                } else {
                    output_ss << "\nInvalid choice. Please enter Y or N." << std::endl;
                    currentAppState = STATE_FINAL_ORDER_CONFIRMATION; // Re-prompt
                    break;
                }
            } // End STATE_FINAL_ORDER_PROCESS case
            case STATE_PAYMENT_PROMPT: {
                output_ss << "\n--- Payment ---" << std::endl;
                double total_cost = currentOrder.calculateTotal();
                double tax = total_cost * 0.08; // Example tax rate
                double grand_total_before_tip = total_cost + tax;

                output_ss << "Order Total: $" << std::fixed << std::setprecision(2) << total_cost << std::endl;
                output_ss << "Tax (8%):    $" << std::fixed << std::setprecision(2) << tax << std::endl;
                output_ss << "Grand Total (before tip): $" << std::fixed << std::setprecision(2) << grand_total_before_tip << std::endl;
                output_ss << "\nEnter tip amount (e.g., 5.00 for $5.00, or 0 for no tip): " << std::endl;
                currentAppState = STATE_PAYMENT_PROCESS;
                break;
            }
            case STATE_PAYMENT_PROCESS: {
                double tip_amount;
                try {
                    tip_amount = std::stod(input_str);
                    if (tip_amount < 0) throw std::invalid_argument("Negative tip");
                } catch (const std::exception& e) {
                    output_ss << "\nInvalid tip amount. Please enter a positive number." << std::endl;
                    currentAppState = STATE_PAYMENT_PROMPT; // Re-prompt
                    break;
                }

                double total_cost = currentOrder.calculateTotal();
                double tax = total_cost * 0.08;
                double grand_total = total_cost + tax + tip_amount;

                Reciept final_reciept(total_cost, tax, tip_amount, grand_total, currentOrder.getTable());
                output_ss << "\n--- Final Receipt ---" << std::endl;
                final_reciept.displayReciept(output_ss); // Display the final receipt

                // Reset for a new order
                currentOrder = Order();
                currentPizzasInOrder.clear();
                currentAppState = STATE_ASK_MAIN_MENU_CHOICE; // Go back to main menu

                break;
            }
            case STATE_EXIT: {
                output_ss << "\nApplication exited. Please close this window." << std::endl;
                // No state change, essentially halts
                break;
            }
        }

        s_persistent_output_buffer = output_ss.str(); // Store the generated output
        return s_persistent_output_buffer.c_str(); // Return C-style string
    }
}