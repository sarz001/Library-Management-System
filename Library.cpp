#include "Library.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iostream>

std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

Library::Library() {}

void Library::loadBooks(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open books file: " << filename << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line); // Skip header
    int maxId = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, title, author, ISBN, availStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, title, ',');
        std::getline(ss, author, ',');
        std::getline(ss, ISBN, ',');
        std::getline(ss, availStr, ',');
        int id = std::stoi(idStr);
        bool avail = (availStr == "Yes");
        Book book(id, title, author, ISBN, avail);
        books.emplace_back(book);
        isbnMap.emplace(ISBN, book); // Use emplace instead of operator[]
        std::string lowerTitle = toLower(title);
        std::string lowerAuthor = toLower(author);
        keywordMap[lowerTitle].push_back(book);
        keywordMap[lowerAuthor].push_back(book);
        titleBST.insert(book);
        if (id > maxId) maxId = id;
    }
    file.close();
    Book::nextId = maxId + 1;
    std::cout << "Loaded " << books.size() << " books.\n";
}

void Library::loadBorrowers(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open borrowers file: " << filename << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line); // Skip header
    int maxId = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, contact;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, contact, ',');
        int id = std::stoi(idStr);
        borrowers.emplace_back(id, name, contact);
        if (id > maxId) maxId = id;
    }
    file.close();
    Borrower::nextId = maxId + 1;
    std::cout << "Loaded " << borrowers.size() << " borrowers.\n";
}

void Library::addBook(std::string title, std::string author, std::string ISBN) {
    Book book(title, author, ISBN);
    books.emplace_back(book);
    isbnMap.emplace(ISBN, book); // Use emplace instead of operator[]
    std::string lowerTitle = toLower(title);
    std::string lowerAuthor = toLower(author);
    keywordMap[lowerTitle].push_back(book);
    keywordMap[lowerAuthor].push_back(book);
    titleBST.insert(book);
    std::cout << "Book added successfully.\n";
}

void Library::addBorrower(std::string name, std::string contact) {
    borrowers.emplace_back(name, contact);
    std::cout << "Borrower registered successfully.\n";
}

void Library::searchBooks(std::string searchTerm) {
    std::string lowerTerm = toLower(searchTerm);
    bool found = false;

    // Check ISBN map for exact match
    auto isbnIt = isbnMap.find(lowerTerm);
    if (isbnIt != isbnMap.end()) {
        isbnIt->second.display();
        found = true;
    }

    // Check keyword map for title/author matches
    for (const auto& pair : keywordMap) {
        if (pair.first.find(lowerTerm) != std::string::npos) {
            for (const auto& book : pair.second) {
                book.display();
                found = true;
            }
        }
    }

    if (!found) std::cout << "No books found.\n";
}

void Library::checkoutBook(int bookId, int borrowerId) {
    auto bookIt = std::find_if(books.begin(), books.end(),
        [bookId](const Book& b) { return b.id == bookId && b.isAvailable; });
    if (bookIt == books.end()) {
        std::cout << "Book not available or doesn't exist.\n";
        reserveBook(bookId, borrowerId);
        return;
    }

    auto borIt = std::find_if(borrowers.begin(), borrowers.end(),
        [borrowerId](const Borrower& b) { return b.id == borrowerId; });
    if (borIt == borrowers.end()) {
        std::cout << "Borrower not found.\n";
        return;
    }

    std::time_t now = std::time(nullptr);
    std::time_t due = now + 14 * 24 * 60 * 60; // 14 days
    transactions.emplace_back(bookId, borrowerId, now, due);
    bookIt->isAvailable = false;
    auto isbnIt = isbnMap.find(bookIt->ISBN);
    if (isbnIt != isbnMap.end()) {
        isbnIt->second.isAvailable = false; // Update existing entry
    }
    auto titleIt = titleBST.find(*bookIt);
    if (titleIt != titleBST.end()) {
        Book updatedBook = *titleIt;
        updatedBook.isAvailable = false;
        titleBST.erase(titleIt);
        titleBST.insert(updatedBook);
    }
    std::cout << "Book checked out successfully.\n";
}

void Library::returnBook(int bookId) {
    auto transIt = std::find_if(transactions.begin(), transactions.end(),
        [bookId](const Transaction& t) { return t.bookId == bookId && t.returnDate == 0; });
    if (transIt == transactions.end()) {
        std::cout << "No active transaction for this book.\n";
        return;
    }

    std::time_t now = std::time(nullptr);
    transIt->returnDate = now;
    double fine = 0.0;
    if (now > transIt->dueDate) {
        double daysLate = std::difftime(now, transIt->dueDate) / (60 * 60 * 24);
        transIt->fine = daysLate * 0.50;
        fine = transIt->fine;
        std::cout << "Book returned late. Fine: $" << fine << std::endl;
    } else {
        std::cout << "Book returned on time.\n";
    }

    auto bookIt = std::find_if(books.begin(), books.end(),
        [bookId](const Book& b) { return b.id == bookId; });
    if (bookIt != books.end()) {
        bookIt->isAvailable = true;
        auto isbnIt = isbnMap.find(bookIt->ISBN);
        if (isbnIt != isbnMap.end()) {
            isbnIt->second.isAvailable = true; // Update existing entry
        }
        auto titleIt = titleBST.find(*bookIt);
        if (titleIt != titleBST.end()) {
            Book updatedBook = *titleIt;
            updatedBook.isAvailable = true;
            titleBST.erase(titleIt);
            titleBST.insert(updatedBook);
        }
    }

    auto resIt = reservations.find(bookId);
    if (resIt != reservations.end() && !resIt->second.empty()) {
        auto nextRes = resIt->second.top();
        resIt->second.pop();
        if (resIt->second.empty()) reservations.erase(bookId);
        std::cout << "Book reserved by borrower ID " << nextRes.borrowerId
                  << ". Notifying them of availability.\n";
    }
}

void Library::reserveBook(int bookId, int borrowerId) {
    auto bookIt = std::find_if(books.begin(), books.end(),
        [bookId](const Book& b) { return b.id == bookId; });
    if (bookIt == books.end()) {
        std::cout << "Book does not exist.\n";
        return;
    }

    auto borIt = std::find_if(borrowers.begin(), borrowers.end(),
        [borrowerId](const Borrower& b) { return b.id == borrowerId; });
    if (borIt == borrowers.end()) {
        std::cout << "Borrower not found.\n";
        return;
    }

    reservations[bookId].emplace(borrowerId, std::time(nullptr));
    std::cout << "Book reserved successfully for borrower ID " << borrowerId << ".\n";
}

void Library::displayBooksByTitle() {
    if (titleBST.empty()) {
        std::cout << "No books in the library.\n";
        return;
    }
    std::cout << "Books in alphabetical order by title:\n";
    for (const auto& book : titleBST) {
        book.display();
    }
}

int Library::getCurrentBorrowedCount(int borrowerId) {
    int count = 0;
    for (const auto& trans : transactions) {
        if (trans.borrowerId == borrowerId && trans.returnDate == 0) {
            count++;
        }
    }
    return count;
}

std::vector<std::string> Library::getBorrowingHistory(int borrowerId) {
    std::vector<std::string> history;
    for (const auto& trans : transactions) {
        if (trans.borrowerId == borrowerId) {
            auto bookIt = std::find_if(books.begin(), books.end(),
                [&trans](const Book& b) { return b.id == trans.bookId; });
            if (bookIt != books.end()) {
                history.push_back(bookIt->title);
            }
        }
    }
    return history;
}

double Library::getTotalFine(int borrowerId) {
    double total = 0.0;
    for (const auto& trans : transactions) {
        if (trans.borrowerId == borrowerId) {
            total += trans.fine;
        }
    }
    return total;
}

void Library::showBorrowerInfo(int borrowerId) {
    auto borIt = std::find_if(borrowers.begin(), borrowers.end(),
        [borrowerId](const Borrower& b) { return b.id == borrowerId; });
    if (borIt == borrowers.end()) {
        std::cout << "Borrower not found.\n";
        return;
    }
    std::cout << "Borrower: " << borIt->name << std::endl;
    std::cout << "Currently borrowed books: " << getCurrentBorrowedCount(borrowerId) << std::endl;
    std::cout << "Borrowing history: ";
    auto history = getBorrowingHistory(borrowerId);
    if (history.empty()) {
        std::cout << "No borrowing history.\n";
    } else {
        for (size_t i = 0; i < history.size(); ++i) {
            std::cout << history[i];
            if (i < history.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "Total fine: $" << getTotalFine(borrowerId) << std::endl;
}