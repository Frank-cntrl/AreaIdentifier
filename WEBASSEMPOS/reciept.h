#ifndef RECIEPT_H
#define RECIEPT_H

#include <string>
#include <ostream> // For std::ostream

class Reciept {
private:
    double total;
    double tax;
    double tip;
    double grandTotal;
    std::string table;

public:
    Reciept() noexcept;
    Reciept(double total, double tax, double tip, double grandTotal, std::string table) noexcept;

    // Setters
    void setTotal(double total);
    void setTax(double tax);
    void setTip(double tip);
    void setGrandTotal(double grandTotal);
    void setTable(std::string table);

    // Getters
    double getTotal();
    double getTax();
    double getTip();
    double getGrandTotal();
    std::string getTable();

    void displayReciept(std::ostream& os); // Takes ostream&
};

#endif // RECIEPT_H