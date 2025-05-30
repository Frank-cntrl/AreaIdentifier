#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For std::fixed, std::setprecision

#include "kitchen.h"
#include "staff.h"
#include "order.h"

// Constructor implementations
Order::Order() noexcept : table(""), server(Staff()), roomChoice(0) {}

Order::Order(std::string table, Staff server) noexcept
    : table(table), server(server), roomChoice(0) {}

Order::Order(std::string table, Staff server, std::vector<Pizza> pizzas) noexcept
    : table(table), server(server), pizzas(pizzas), roomChoice(0) {}

// Setters
void Order::setTable(std::string table) {
    this->table = table;
}

void Order::setServer(Staff server) {
    this->server = server;
}

void Order::addPizza(Pizza pizza) {
    pizzas.push_back(pizza);
}

void Order::setRoomChoice(int choice) {
    this->roomChoice = choice;
}

// Getters
std::string Order::getTable() const {
    return table;
}

Staff Order::getServer() const {
    return server;
}

std::vector<Pizza> Order::getPizzas() const {
    return pizzas;
}

int Order::getRoomChoice() const {
    return roomChoice;
}

// Other methods
double Order::calculateTotal() const {
    double total = 0.0;
    for (const auto& pizza : pizzas) {
        total += pizza.getPrice();
    }
    return total;
}

// Updated to take std::ostream&
void Order::displayOrder(std::ostream& os) const {
    os << "Table Number: " << table << std::endl;
    os << "Server: " << server.getName() << std::endl;
    os << "Pizzas in this order:" << std::endl;
    if (pizzas.empty()) {
        os << "  No pizzas added yet." << std::endl;
    } else {
        for (size_t i = 0; i < pizzas.size(); ++i) {
            os << "  " << (i + 1) << ". " << pizzas[i].getType() << " (" << pizzas[i].getSize() << " inches) - $";
            os << std::fixed << std::setprecision(2) << pizzas[i].getPrice();
            os << std::endl;
            os << "     Toppings: ";
            const auto& toppings = pizzas[i].getToppings();
            if (toppings.empty()) {
                os << "None" << std::endl;
            } else {
                for (size_t j = 0; j < toppings.size(); ++j) {
                    os << toppings[j];
                    if (j < toppings.size() - 1) {
                        os << ", ";
                    }
                }
                os << std::endl;
            }
        }
    }
    os << "----------------------------------" << std::endl;
    os << "Order Subtotal: $" << std::fixed << std::setprecision(2) << calculateTotal() << std::endl;
}