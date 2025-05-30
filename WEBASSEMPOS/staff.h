#ifndef STAFF_H
#define STAFF_H

#include <string>

class Staff {
protected:
    std::string name;
    std::string position;
    int pin;

public:
    bool isAdmin;

    Staff() noexcept;
    Staff(std::string name, std::string position, int pin) noexcept;

    // Setters
    void setName(std::string name);
    void setPosition(std::string position);
    void setPin(int pin);

    // Getters
    std::string getName() const;
    std::string getPosition();
    int getPin();
};

class Manager : public Staff {
public:
    Manager(std::string name, std::string position, int pin) noexcept;
};

class Server : public Staff {
public:
    Server(std::string name, std::string position, int pin) noexcept;
};

// Function declaration for pin check
bool pinCheck(int pin);

#endif // STAFF_H