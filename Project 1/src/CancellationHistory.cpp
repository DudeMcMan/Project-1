#include "../include/CancellationHistory.h"
#include <iostream>

CancellationHistory::CancellationHistory() : top(nullptr), count(0) {}

// free every node so the stack leaks no memory.
CancellationHistory::~CancellationHistory() {
  while (top != nullptr) {
    Node *temp = top;
    top = top->next;
    delete temp;
  }
}

// new node points at the old top, then becomes the top.
void CancellationHistory::push(const Reservation &r) {
  top = new Node(r, top);
  count++;
}

// copy out the top, unlink it, delete it. False if the stack is empty.
bool CancellationHistory::pop(Reservation &out) {
  if (top == nullptr)
    return false;
  Node *temp = top;
  out = top->data;
  top = top->next;
  delete temp;
  count--;
  return true;
}

// same as pop but leaves the stack unchanged.
bool CancellationHistory::peek(Reservation &out) const {
  if (top == nullptr)
    return false;
  out = top->data;
  return true;
}

bool CancellationHistory::isEmpty() const { return top == nullptr; }
int CancellationHistory::size() const { return count; }

// walk from the top down so the most recent cancellation prints first.
void CancellationHistory::display() const {
  if (top == nullptr) {
    std::cout << "No cancelled reservations.\n";
    return;
  }
  std::cout << "===== Cancellation History (most recent first) =====\n";
  int position = 1;
  for (Node *cur = top; cur != nullptr; cur = cur->next) {
    std::cout << position++ << ". Reservation ID: " << cur->data.id
              << " | Student: " << cur->data.studentName << " ("
              << cur->data.studentId << ")"
              << " | Resource: " << cur->data.resourceId
              << " | Date: " << cur->data.date << "\n";
  }
}