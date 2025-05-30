#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip> // Required for std::fixed and std::setprecision
#include "kitchen.h"
#include "userInterface.h" // For display functions

// Base Pizza class implementation
Pizza::Pizza() noexcept {
    price = 0.0;
    size = 12;
    type = "Unknown";
    toppings.clear();
    toppingsID = {
        {1, "Rosemary"}, {2, "E.V. olive oil"}, {3, "Coarse sea salt"},
        {4, "Sea salt"}, {5, "Mozzarella"}, {6, "Truffle oil"},
        {7, "Vine ripe tomatoes"}, {8, "Sliced garlic"}, {9, "Oregano"},
        {10, "Peperoncino"}, {11, "Garlic"}, {12, "Capers"},
        {13, "Olives"}, {14, "Sicilian salted anchovies"}, {15, "Fresh basil"},
        {16, "Fresh mushrooms"}, {17, "Parsley"}, {18, "Cherry tomatoes"},
        {19, "Arugula"}, {20, "Zucchini"}, {21, "Eggplant"},
        {22, "Mushrooms"}, {23, "Radicchio"}, {24, "Spicy salame"},
        {25, "Homemade sausage"}, {26, "Baby meatballs"}, {27, "Fresh sage"},
        {28, "Goat cheese"}, {29, "Roasted peppers"}, {30, "Roasted onions"}
    };
}

Pizza::Pizza(double price, int size, std::string type) {
    this->price = price;
    this->size = size;
    this->type = type;
    toppings.clear();
    toppingsID = {
        {1, "Rosemary"}, {2, "E.V. olive oil"}, {3, "Coarse sea salt"},
        {4, "Sea salt"}, {5, "Mozzarella"}, {6, "Truffle oil"},
        {7, "Vine ripe tomatoes"}, {8, "Sliced garlic"}, {9, "Oregano"},
        {10, "Peperoncino"}, {11, "Garlic"}, {12, "Capers"},
        {13, "Olives"}, {14, "Sicilian salted anchovies"}, {15, "Fresh basil"},
        {16, "Fresh mushrooms"}, {17, "Parsley"}, {18, "Cherry tomatoes"},
        {19, "Arugula"}, {20, "Zucchini"}, {21, "Eggplant"},
        {22, "Mushrooms"}, {23, "Radicchio"}, {24, "Spicy salame"},
        {25, "Homemade sausage"}, {26, "Baby meatballs"}, {27, "Fresh sage"},
        {28, "Goat cheese"}, {29, "Roasted peppers"}, {30, "Roasted onions"}
    };
}

void Pizza::setPrice(double price) {
    this->price = price;
}

void Pizza::setSize(int size) {
    this->size = size;
}

void Pizza::setType(std::string type) {
    this->type = type;
}

void Pizza::addTopping(int choice) {
    if (toppingsID.count(choice)) {
        toppings.push_back(toppingsID[choice]);
    } else {
        // Handle invalid topping choice if necessary (e.g., throw exception or print error)
    }
}

void Pizza::setToppings(const std::vector<std::string>& newToppings) {
    this->toppings = newToppings;
}


double Pizza::getPrice() const {
    return price;
}

int Pizza::getSize() const {
    return size;
}

std::string Pizza::getType() const {
    return type;
}

std::vector<std::string> Pizza::getToppings() const {
    return toppings;
}

std::map<int, std::string> Pizza::getToppingsMap() const {
    return toppingsID;
}

void Pizza::displayToppings(std::ostream& os) const {
    for (const auto& topping : toppings) {
        os << "- " << topping << std::endl;
    }
}

// Static method to display the pizza menu
void Pizza::displayPizzaMenu(std::ostream& os) {
    os << "1. Focaccia      ($10.00)" << std::endl;
    os << "2. Bianca        ($12.00)" << std::endl;
    os << "3. Marinara      ($11.00)" << std::endl;
    os << "4. Napoletana    ($13.00)" << std::endl;
    os << "5. Margherita    ($14.00)" << std::endl;
    os << "6. Funghi        ($15.00)" << std::endl;
    os << "7. Angelina      ($16.00)" << std::endl;
    os << "8. Ortolana      ($17.00)" << std::endl;
    os << "9. Salame Piccante ($18.00)" << std::endl;
    os << "10. Salsiccia    ($19.00)" << std::endl;
}

// Static method to display topping options
void Pizza::displayPizzaToppingsOptions(std::ostream& os) {
    // A single instance of Pizza to access toppingsID for display
    Pizza temp_pizza;
    for (const auto& pair : temp_pizza.getToppingsMap()) {
        os << std::setw(2) << pair.first << ". " << pair.second << std::endl;
    }
}

// Static factory method implementation
Pizza Pizza::createPizza(int choice) {
    switch (choice) {
        case 1: return Focaccia();
        case 2: return Bianca();
        case 3: return Marinara();
        case 4: return Napoletana();
        case 5: return Margherita();
        case 6: return Funghi();
        case 7: return Angelina();
        case 8: return Ortolana();
        case 9: return SalamePiccante();
        case 10: return Salsiccia();
        default: return Pizza(); // Returns an "Unknown" pizza
    }
}

// Derived classes implementations
Focaccia::Focaccia() : Pizza(10.00, 12, "Focaccia") {}
double Focaccia::getPrice() const {
    double base_price = price;
    if (size == 16) base_price += 4.00; // 16-inch upcharge
    return base_price + (toppings.size() * 1.50); // Topping price
}

Bianca::Bianca() : Pizza(12.00, 12, "Bianca") {}
double Bianca::getPrice() const {
    double base_price = price;
    if (size == 16) base_price += 4.00;
    return base_price + (toppings.size() * 1.50);
}

Marinara::Marinara() : Pizza(11.00, 12, "Marinara") {}
double Marinara::getPrice() const {
    double base_price = price;
    if (size == 16) base_price += 4.00;
    return base_price + (toppings.size() * 1.50);
}

Napoletana::Napoletana() : Pizza(13.00, 12, "Napoletana") {}
double Napoletana::getPrice() const {
    double base_price = price;
    if (size == 16) base_price += 4.00;
    return base_price + (toppings.size() * 1.50);
}

Margherita::Margherita() : Pizza(14.00, 12, "Margherita") {}
double Margherita::getPrice() const {
    double base_price = price;
    if (size == 16) base_price += 4.00;
    return base_price + (toppings.size() * 1.50);
}

Funghi::Funghi() : Pizza(15.00, 12, "Funghi") {}
double Funghi::getPrice() const {
    double base_price = price;
    if (size == 16) base_price += 4.00;
    return base_price + (toppings.size() * 1.50);
}

Angelina::Angelina() : Pizza(16.00, 12, "Angelina") {}
double Angelina::getPrice() const {
    double base_price = price;
    if (size == 16) base_price += 4.00;
    return base_price + (toppings.size() * 1.50);
}

Ortolana::Ortolana() : Pizza(17.00, 12, "Ortolana") {}
double Ortolana::getPrice() const {
    double base_price = price;
    if (size == 16) base_price += 4.00;
    return base_price + (toppings.size() * 1.50);
}

SalamePiccante::SalamePiccante() : Pizza(18.00, 12, "Salame Piccante") {}
double SalamePiccante::getPrice() const {
    double base_price = price;
    if (size == 16) base_price += 4.00;
    return base_price + (toppings.size() * 1.50);
}

Salsiccia::Salsiccia() : Pizza(19.00, 12, "Salsiccia") {}
double Salsiccia::getPrice() const {
    double base_price = price;
    if (size == 16) base_price += 4.00;
    return base_price + (toppings.size() * 1.50);
}