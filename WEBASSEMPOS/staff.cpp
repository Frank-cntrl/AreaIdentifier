#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "staff.h"
#include "userInterface.h"

Staff::Staff() noexcept {
    name = "";
    position = "";
    pin = 0;
    isAdmin = false; // Initialize isAdmin
}

Staff::Staff(std::string name, std::string position, int pin) noexcept {
    this->name = name;
    this->position = position;
    this->pin = pin;
    this->isAdmin = false; // Default to false, set true in Manager constructor
}

void Staff::setName(std::string name) {
    this->name = name;
}

void Staff::setPosition(std::string position) {
    this->position = position;
}

void Staff::setPin(int pin) {
    this->pin = pin;
}

std::string Staff::getName() const {
    return name;
}

std::string Staff::getPosition() {
    return position;
}

int Staff::getPin() {
    return pin;
}

Manager::Manager(std::string name, std::string position, int pin) noexcept : Staff(name, position, pin) {
    this->isAdmin = true;
}

Server::Server(std::string name, std::string position, int pin) noexcept : Staff(name, position, pin) {
    this->isAdmin = false;
}

bool pinCheck(int pin) {
    // Hardcoded pins for simplicity, in a real app these would be stored securely
    if (pin == 4493 || pin == 1739) {
        return true;
    } else {
        return false;
    }
}