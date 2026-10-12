Campus Resource Reservation System
Final Submission
UNT Foundations of Data Structures

Team Members: Ryker, Mason, Owen


Project Description

The Campus Resource Reservation System lets students reserve campus
resources (study rooms, laptops, calculators, lab equipment, and
tutoring appointments) by date, manage waiting lists when a resource
is already booked on a requested date, search and sort resources and
reservations, generate usage reports, and track a history of
cancelled reservations that can be undone. The system runs as a
menu-driven command-line program.


Features

  1. View Resources - lists all loaded resources and their current
     booked dates.
  2. Create Reservation - books a resource for a student on a given
     date, after validating the student ID, the date, and resource
     availability on that specific date. If the resource is already
     booked on that date, the student is placed on the waiting list.
  3. Cancel Reservation - cancels a reservation, frees the resource
     on that date, pushes the cancellation onto the cancellation
     history stack, and automatically promotes the next matching
     waiting-list student into the freed slot, if one is waiting.
  4. View Waiting Lists - displays all students currently waiting for
     a resource/date to open up.
  5. Undo Cancellation - restores the most recently cancelled
     reservation, if the resource/date is still free.
  6. Search Reservations - search by reservation ID or by student
     name (hand-written linear search, no library search functions).
  7. Sort Resources - sorts all resources alphabetically by name using
     a hand-written merge sort (no std::sort).
  8. Generate Report - active reservations, resource utilization
     (reservation count per resource), most requested resources
     (ranked without any library sort), and waiting-list statistics.
  9. Exit


Data Structures

  - Reservation linked list (ReservationList) - insert, remove,
    find by ID, find by student name, count by resource, display.
  - Waiting list queue (WaitingList) - add student, remove student,
    display, statistics by resource.
  - Cancellation history stack (CancellationHistory) - push, pop,
    peek, isEmpty, size, display; backs the undo-cancellation feature.
  - Resource per-date availability (Resource) - tracks a list of
    booked dates per resource instead of a single available/
    unavailable flag, so the same resource can be reserved on
    different dates independently.


Folder Structure

Project 1/
  include/            Header files (.h)
  src/                Source files (.cpp)
  data/               Input data files (resources.txt, reservations.txt)
  docs/               Complexity analysis and contribution report
  tests/              Unit tests


How to Build and Run

  cd "Project 1"
  g++ -std=c++17 -Wall -Iinclude src/main.cpp src/ReservationManager.cpp src/ResourceManager.cpp src/ReservationList.cpp src/WaitingList.cpp src/Resource.cpp src/Reservation.cpp src/CancellationHistory.cpp -o campus_system
  ./campus_system

This project was verified to compile successfully on the UNT CSE
CELL machines using the same command above.

To build and run the unit tests:

  g++ -std=c++17 -Wall -Iinclude tests/test_stack.cpp src/CancellationHistory.cpp src/Reservation.cpp -o test_stack
  ./test_stack

  g++ -std=c++17 -Wall -Iinclude tests/test_sort_and_reports.cpp src/ResourceManager.cpp src/Resource.cpp src/ReservationList.cpp src/Reservation.cpp -o test_sort_and_reports
  ./test_sort_and_reports

  g++ -std=c++17 -Wall -Iinclude tests/test_availability_and_search.cpp src/Resource.cpp src/ReservationList.cpp src/Reservation.cpp src/ResourceManager.cpp src/ReservationManager.cpp src/WaitingList.cpp src/CancellationHistory.cpp -o test_availability_and_search
  ./test_availability_and_search

--------------------------------------------------------------------
GitHub Repository
--------------------------------------------------------------------
https://github.com/DudeMcMan/Project-1
