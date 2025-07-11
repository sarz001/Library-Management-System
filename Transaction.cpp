#include "Transaction.h"

Transaction::Transaction(int bId, int borId, std::time_t cDate, std::time_t dDate)
    : bookId(bId), borrowerId(borId), checkoutDate(cDate), dueDate(dDate), returnDate(0), fine(0.0) {}