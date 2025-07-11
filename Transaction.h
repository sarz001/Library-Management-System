#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <ctime>

class Transaction {
public:
    int bookId;
    int borrowerId;
    std::time_t checkoutDate;
    std::time_t dueDate;
    std::time_t returnDate;
    double fine;

    Transaction(int bId, int borId, std::time_t cDate, std::time_t dDate);
};

#endif // TRANSACTION_H