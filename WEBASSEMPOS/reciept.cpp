#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip> // Required for std::fixed and std::setprecision
#include "reciept.h"

Reciept::Reciept() noexcept {
    total = 0;
    tax = 0;
    tip = 0;
    grandTotal = 0;
    table = "";
}

Reciept::Reciept(double total, double tax, double tip, double grandTotal, std::string table) noexcept {
    this->total = total;
    this->tax = tax;
    this->tip = tip;
    this->grandTotal = grandTotal;
    this->table = table;
}

void Reciept::setTotal(double total) {
    this->total = total;
}

void Reciept::setTax(double tax) {
    this->tax = tax;
}

void Reciept::setTip(double tip) {
    this->tip = tip;
}

void Reciept::setGrandTotal(double grandTotal) {
    this->grandTotal = grandTotal;
}

void Reciept::setTable(std::string table) {
    this->table = table;
}

double Reciept::getTotal() {
    return total;
}

double Reciept::getTax() {
    return tax;
}

double Reciept::getTip() {
    return tip;
}

double Reciept::getGrandTotal() {
    return grandTotal;
}

std::string Reciept::getTable() {
    return table;
}

void Reciept::displayReciept(std::ostream& os) {
    os << "Table: " << table << std::endl;
    os << "Subtotal: $" << std::fixed << std::setprecision(2) << total << std::endl;
    os << "Tax:      $" << std::fixed << std::setprecision(2) << tax << std::endl;
    os << "Tip:      $" << std::fixed << std::setprecision(2) << tip << std::endl;
    os << "--------------------" << std::endl;
    os << "Grand Total: $" << std::fixed << std::setprecision(2) << grandTotal << std::endl;
}