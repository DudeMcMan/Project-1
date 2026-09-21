#include "CancellationHistory.h"
#include <cassert>
#include <iostream>


// helper: build a Reservation from the five fields.
static Reservation makeRes(int id, int studentId, const std::string &name,
                           const std::string &resourceId,
                           const std::string &date) {
  Reservation r;
  r.id = id;
  r.studentId = studentId;
  r.studentName = name;
  r.resourceId = resourceId;
  r.date = date;
  return r;
}

int main() {
  CancellationHistory history;
  Reservation out;

  // empty stack: pop and peek must fail safely, not crash.
  assert(history.isEmpty());
  assert(!history.pop(out));
  assert(!history.peek(out));
  history.display();

  // push three cancellations (data taken from reservations.txt).
  history.push(makeRes(301, 1001, "Alice Smith", "R101", "09/15/2026"));
  history.push(makeRes(302, 1002, "Bob Johnson", "R103", "09/16/2026"));
  history.push(makeRes(303, 1003, "Sara Lee", "R105", "09/17/2026"));
  assert(history.size() == 3);
  history.display();

  // peek shows the newest without removing it.
  assert(history.peek(out) && out.id == 303);
  assert(history.size() == 3);

  // pop returns them newest first (last in, first out).
  assert(history.pop(out) && out.id == 303);
  assert(history.pop(out) && out.id == 302);
  assert(history.pop(out) && out.id == 301);
  assert(history.isEmpty());
  assert(!history.pop(out)); // empty again

  std::cout << "All CancellationHistory tests passed.\n";
  return 0;
}