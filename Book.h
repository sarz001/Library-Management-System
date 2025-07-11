#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
public:
    static int nextId;
    int id;
    std::string title;
    std::string author;
    std::string ISBN;
    bool isAvailable;

    Book(std::string t, std::string a, std::string i);
    Book(int id, std::string t, std::string a, std::string i, bool avail);
    void display() const;
};

#endif // BOOK_H