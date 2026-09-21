#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include "Reservation.h"

// Stack (last in, first out) of cancelled reservations,
// built as a singly linked list where only the top is touched.
class CancellationHistory {
public:
  CancellationHistory();
  ~CancellationHistory();
  CancellationHistory(const CancellationHistory &) = delete;
  CancellationHistory &operator=(const CancellationHistory &) = delete;

  void push(const Reservation &r);   // store a cancelled reservation
  bool pop(Reservation &out);        // remove most recent; false if empty
  bool peek(Reservation &out) const; // read most recent without removing
  bool isEmpty() const;
  int size() const;
  void display() const; // most recent first

private:
  struct Node {
    Reservation data;
    Node *next;
    Node(const Reservation &r, Node *n) : data(r), next(n) {}
  };
  Node *top; // newest cancellation, or nullptr when empty
  int count;
};

#endif