#ifndef BORROWER_H
#define BORROWER_H

#include <string>

class Borrower {
public:
    static int nextId;
    int id;
    std::string name;
    std::string contact;

    Borrower(std::string n, std::string c);
    Borrower(int id, std::string n, std::string c);
    void display() const;
};

#endif // BORROWER_H