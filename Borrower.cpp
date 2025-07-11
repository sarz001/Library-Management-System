#include "Borrower.h"
#include <iostream>

int Borrower::nextId = 1;

Borrower::Borrower(std::string n, std::string c)
    : id(nextId++), name(n), contact(c) {}

Borrower::Borrower(int id, std::string n, std::string c)
    : id(id), name(n), contact(c) {}

void Borrower::display() const {
    std::cout << "ID: " << id << ", Name: " << name << ", Contact: " << contact << std::endl;
}