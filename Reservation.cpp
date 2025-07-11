#include "Reservation.h"

Reservation::Reservation(int bId, std::time_t rTime)
    : borrowerId(bId), requestTime(rTime) {}

bool Reservation::operator<(const Reservation& other) const {
    return requestTime > other.requestTime; // Earlier time = higher priority
}