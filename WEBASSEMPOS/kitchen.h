#ifndef KITCHEN_H
#define KITCHEN_H

#include <string>
#include <vector>
#include <map>
#include <ostream> // For std::ostream

class Pizza {
protected:
    double price;
    int size; // 12 or 16 inches
    std::string type;
    std::vector<std::string> toppings;
    std::map<int, std::string> toppingsID;

public:
    Pizza() noexcept; // Default constructor
    Pizza(double price, int size, std::string type); // Parameterized constructor

    // Setters
    void setPrice(double price);
    void setSize(int size);
    void setType(std::string type);
    void addTopping(int choice);
    void setToppings(const std::vector<std::string>& newToppings); // New setter for toppings vector

    // Getters
    double virtual getPrice() const; // **CHANGED: Added 'virtual' here**
    int getSize() const;
    std::string getType() const;
    std::vector<std::string> getToppings() const;
    std::map<int, std::string> getToppingsMap() const; // Getter for the toppingsID map

    // Display functions
    void displayToppings(std::ostream& os) const; // Takes ostream&
    static void displayPizzaMenu(std::ostream& os); // Static, takes ostream&
    static void displayPizzaToppingsOptions(std::ostream& os); // Static, takes ostream&

    // Factory method
    static Pizza createPizza(int choice); // Static factory method
};

// Derived Pizza classes
class Focaccia : public Pizza {
public:
    Focaccia();
    double getPrice() const override;
};

class Bianca : public Pizza {
public:
    Bianca();
    double getPrice() const override;
};

class Marinara : public Pizza {
public:
    Marinara();
    double getPrice() const override;
};

class Napoletana : public Pizza {
public:
    Napoletana();
    double getPrice() const override;
};

class Margherita : public Pizza {
public:
    Margherita();
    double getPrice() const override;
};

class Funghi : public Pizza {
public:
    Funghi();
    double getPrice() const override;
};

class Angelina : public Pizza {
public:
    Angelina();
    double getPrice() const override;
};

class Ortolana : public Pizza {
public:
    Ortolana();
    double getPrice() const override;
};

class SalamePiccante : public Pizza {
public:
    SalamePiccante();
    double getPrice() const override;
};

class Salsiccia : public Pizza {
public:
    Salsiccia();
    double getPrice() const override;
};

#endif // KITCHEN_H