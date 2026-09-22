Campus Resource Reservation System
Milestone 1 - Core System Development
UNT Foundations of Data Structures

Team Members:Ryker, Mason, Owen


Project Description

The Campus Resource Reservation System lets students reserve campus
resources (study rooms, laptops, calculators, lab equipment, and
tutoring appointments), manage waiting lists when a resource is
unavailable, and track a history of cancelled reservations that can
be undone. The system runs as a menu-driven command-line program.


Milestone 1 Features

  - Resource management (load resources from file, view all
    resources, view available resources, search by ID).
  - Reservation management (create, cancel, search/display active
    reservations).
  - Cancellation history stack (push, pop, peek, isEmpty, size,
    display) - stores cancelled reservations and undoes the most
    recently cancelled reservation through the menu.
  - Active reservation linked list (insert, remove, find, display,
    isEmpty).
  - Waiting list queue (add student, remove student, display,
    isEmpty).
  - Shared Reservation data structure (id, studentId, studentName,
    resourceId, date) used across the project.
  - Complexity analysis of reservation insertion, removal,
    waiting-list processing, and undo cancellation
    (docs/complexity_analysis.docx).


Folder Structure

Project 1/
  include/            Header files (.h)
  src/                Source files (.cpp)
  data/               Input data files (resources.txt, reservations.txt)
  docs/               Complexity analysis document
  tests/              Unit tests


How to Build and Run


  cd "Project 1"
  g++ -std=c++17 -Wall -Iinclude src/*.cpp -o reservation_system
  ./reservation_system

To build and run the cancellation history stack's unit test on its
own:

  g++ -std=c++17 -Wall -Iinclude tests/test_stack.cpp \
      src/CancellationHistory.cpp src/Reservation.cpp -o test_stack
  ./test_stack

--------------------------------------------------------------------
GitHub Repository
--------------------------------------------------------------------
https://github.com/DudeMcMan/Project-1
