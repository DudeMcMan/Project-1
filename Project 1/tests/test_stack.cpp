
#include "CancellationHistory.h"
#include "Reservation.h"
#include <cassert>
#include <iostream>

Reservation makeRes(int id, int sid, std::string name, std::string resId, std::string date) {
    return Reservation(id, sid, name, resId, date);
}

int main() {
    CancellationHistory history;
    Reservation out(0, 0, "", "", "");

    assert(history.isEmpty() == true);
    assert(history.size() == 0);
    assert(history.pop(out) == false);
    assert(history.peek(out) == false);

    history.push(makeRes(301, 1001, "Alice Smith", "R101", "09/15/2026"));
    history.push(makeRes(302, 1002, "Bob Jones", "R102", "09/16/2026"));
    history.push(makeRes(303, 1003, "Carla Diaz", "R103", "09/17/2026"));

    assert(history.isEmpty() == false);
    assert(history.size() == 3);

    bool ok = history.peek(out);
    assert(ok == true);
    assert(out.getReservationID() == 303);
    assert(history.size() == 3);

    ok = history.pop(out);
    assert(ok == true);
    assert(out.getReservationID() == 303);
    assert(history.size() == 2);

    history.pop(out);
    assert(out.getReservationID() == 302);

    history.pop(out);
    assert(out.getReservationID() == 301);

    assert(history.isEmpty() == true);
    assert(history.size() == 0);

    std::cout << "All CancellationHistory tests passed." << std::endl;
    return 0;
}
