#include "Library.h"
#include <iostream>
#include <limits>

int main() {
    Library lib;

    // Load initial data
    lib.loadBooks("books.txt");
    lib.loadBorrowers("borrowers.txt");

    int choice;
    do {
        std::cout << "\nLibrary System Menu:\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Add Borrower\n";
        std::cout << "3. Search Books\n";
        std::cout << "4. Check Out Book\n";
        std::cout << "5. Return Book\n";
        std::cout << "6. Show Borrower Info\n";
        std::cout << "7. Reserve Book\n";
        std::cout << "8. Display Books by Title\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                std::string title, author, ISBN;
                std::cout << "Enter title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, ISBN);
                lib.addBook(title, author, ISBN);
                break;
            }
            case 2: {
                std::string name, contact;
                std::cout << "Enter name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter contact: ";
                std::getline(std::cin, contact);
                lib.addBorrower(name, contact);
                break;
            }
            case 3: {
                std::string searchTerm;
                std::cout << "Enter search term: ";
                std::cin.ignore();
                std::getline(std::cin, searchTerm);
                lib.searchBooks(searchTerm);
                break;
            }
            case 4: {
                int bookId, borrowerId;
                std::cout << "Enter book ID: ";
                std::cin >> bookId;
                std::cout << "Enter borrower ID: ";
                std::cin >> borrowerId;
                lib.checkoutBook(bookId, borrowerId);
                break;
            }
            case 5: {
                int bookId;
                std::cout << "Enter book ID: ";
                std::cin >> bookId;
                lib.returnBook(bookId);
                break;
            }
            case 6: {
                int borrowerId;
                std::cout << "Enter borrower ID: ";
                std::cin >> borrowerId;
                lib.showBorrowerInfo(borrowerId);
                break;
            }
            case 7: {
                int bookId, borrowerId;
                std::cout << "Enter book ID: ";
                std::cin >> bookId;
                std::cout << "Enter borrower ID: ";
                std::cin >> borrowerId;
                lib.reserveBook(bookId, borrowerId);
                break;
            }
            case 8: {
                lib.displayBooksByTitle();
                break;
            }
            case 9:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 9);

    return 0;
}