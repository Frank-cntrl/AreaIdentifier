#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <ostream> // For std::ostream

#include "kitchen.h" // For Pizza
#include "staff.h"   // For Staff

class Order {
private:
    std::string table;
    Staff server;
    std::vector<Pizza> pizzas;
    int roomChoice; // New member to store room choice

public:
    // Constructors
    Order() noexcept;
    Order(std::string table, Staff server) noexcept;
    Order(std::string table, Staff server, std::vector<Pizza> pizzas) noexcept;

    // Setters
    void setTable(std::string table);
    void setServer(Staff server);
    void addPizza(Pizza pizza);
    void setRoomChoice(int choice); // Setter for roomChoice

    // Getters
    std::string getTable() const;
    Staff getServer() const;
    std::vector<Pizza> getPizzas() const;
    int getRoomChoice() const; // Getter for roomChoice

    // Other methods
    double calculateTotal() const;
    void displayOrder(std::ostream& os) const; // Updated to take ostream&
};

#endif // ORDER_H