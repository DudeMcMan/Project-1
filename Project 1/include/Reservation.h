#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

struct Reservation {
  int id;
  int studentId;
  std::string studentName;
  std::string resourceId;
  std::string date;
};

#endif