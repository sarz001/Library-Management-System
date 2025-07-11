#ifndef RESERVATION_H
#define RESERVATION_H

#include <ctime>

class Reservation {
public:
    int borrowerId;
    std::time_t requestTime;

    Reservation(int bId, std::time_t rTime);
    bool operator<(const Reservation& other) const; // For priority_queue (earlier time = higher priority)
};

#endif // RESERVATION_H