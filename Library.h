#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <queue>
#include <functional>
#include "Book.h"
#include "Borrower.h"
#include "Transaction.h"
#include "Reservation.h"

class Library {
private:
    struct BookTitleComparator {
        bool operator()(const Book& a, const Book& b) const {
            return a.title < b.title;
        }
    };

    std::vector<Book> books;
    std::vector<Borrower> borrowers;
    std::vector<Transaction> transactions;
    std::unordered_map<std::string, Book> isbnMap;
    std::unordered_map<std::string, std::vector<Book>> keywordMap;
    std::set<Book, BookTitleComparator> titleBST;
    std::unordered_map<int, std::priority_queue<Reservation>> reservations;

public:
    Library();
    void loadBooks(const std::string& filename);
    void loadBorrowers(const std::string& filename);
    void addBook(std::string title, std::string author, std::string ISBN);
    void addBorrower(std::string name, std::string contact);
    void searchBooks(std::string searchTerm);
    void checkoutBook(int bookId, int borrowerId);
    void returnBook(int bookId);
    void reserveBook(int bookId, int borrowerId);
    void displayBooksByTitle();
    int getCurrentBorrowedCount(int borrowerId);
    std::vector<std::string> getBorrowingHistory(int borrowerId);
    double getTotalFine(int borrowerId);
    void showBorrowerInfo(int borrowerId);
};

#endif // LIBRARY_H