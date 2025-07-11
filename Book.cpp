#include "Book.h"
#include <iostream>

int Book::nextId = 1;

Book::Book(std::string t, std::string a, std::string i)
    : id(nextId++), title(t), author(a), ISBN(i), isAvailable(true) {}

Book::Book(int id, std::string t, std::string a, std::string i, bool avail)
    : id(id), title(t), author(a), ISBN(i), isAvailable(avail) {}

void Book::display() const {
    std::cout << "ID: " << id << ", Title: " << title << ", Author: " << author
              << ", ISBN: " << ISBN << ", Available: " << (isAvailable ? "Yes" : "No") << std::endl;
}
