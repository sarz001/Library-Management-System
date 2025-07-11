# Library Management System

This project implements a custom Library Management System in C++ that manages books, borrowers, transactions, and reservations. The system is built entirely without using STL containers like `std::map`, `std::set`, or `std::priority_queue`. Instead, all data structures (such as hash tables, binary search trees, and priority queues) are implemented from scratch.

---

## Project Overview

The system simulates a library’s core functions:

- Adding and searching books
- Managing borrowers
- Checking out and returning books (with fine calculations)
- Handling book reservations
- Viewing books sorted alphabetically
- Viewing borrower details, history, and fines

Data is persisted via `books.txt` and `borrowers.txt` files. The console interface is menu-driven and interactive.

---

## Key Features and Custom Data Structures

### 1. Efficient Book Search

- **ISBN Lookup:**  
  Uses a custom `HashTable<std::string, Book>` for O(1) average-case lookup by ISBN.

- **Keyword Search:**  
  Implements another `HashTable<std::string, DynamicArray<Book>>`, mapping lowercase titles/authors to lists of books. Case-insensitive search is done using a `toLower` utility.

### 2. Alphabetical Book Listing

- Utilizes a custom `BST<Book>` with a comparator for sorting by title.
- Provides O(log n) insertion and efficient in-order traversal for displaying books alphabetically.

### 3. Borrowing and Fine System

- Tracks checkouts via a `Transaction` class storing:
  - Book ID, borrower ID
  - Checkout date, due date (14 days), return date
- Fine of ₹0.50 per day for late returns.
- Data consistency is maintained across  `HashTable`, and `BST`.

### 4. Reservation System

- Each book ID maps to a `PriorityQueue<Reservation>` stored in a `HashTable<int, PriorityQueue<Reservation>>`.
- Ensures priority-based reservation using request timestamps.

### 5. Borrower Management

- Borrowers are stored in a `DynamicArray<Borrower>`.
- Provides functions like:
  - `getCurrentBorrowedCount()`
  - `getBorrowingHistory()`
  - `getTotalFine()`

---

## Technical Highlights

- **Custom STL Replacements:**
  - `HashTable<K, V>` instead of `std::unordered_map`
  - `BST<T>` instead of `std::set`
  - `PriorityQueue<T>` instead of `std::priority_queue`

- **Data Structure Synchronization:**  
  Carefully updates internal states across all structures in O(1) to O(log n) time.

- **Case-Insensitive Search:**  
  Converts all user input to lowercase for robust searching.

- **Time-Based Logic:**  
  Uses `std::time` to calculate due dates, return times, and fines with precision.

- **Modular OOP Design:**  
  Classes include `Book`, `Borrower`, `Transaction`, `Reservation`, and `Library`. All code is cleanly modularized with headers and source files.

- **Error Handling:**  
  Invalid inputs are handled gracefully, and user-friendly error messages are displayed.

---

## Implementation Details

### Core Classes

- **Book:**  
  Stores ID, title, author, ISBN, availability, and auto-increments IDs.

- **Borrower:**  
  Stores ID, name, and contact, along with borrowing history and total fine.

- **Transaction:**  
  Tracks when a book was checked out, returned, and the fine if applicable.

- **Reservation:**  
  Stores borrower ID and timestamp. Supports comparison for priority handling.

- **Library:**  
  Main controller class managing all operations and linking other components.

### File I/O

- Books and borrowers are loaded from and saved to `.txt` files.
- Robust parsing using file streams and error detection.

### Menu Interface

- The main loop is in `main.cpp`.
- Presents a clean CLI for performing operations interactively.

---

## Compilation and Execution

### Prerequisites
- A C++17-compatible compiler (e.g., `g++`, `clang++`)

### Compilation

```bash
g++ -std=c++17 main.cpp Library.cpp Book.cpp Borrower.cpp Transaction.cpp Reservation.cpp -o libraryApp
