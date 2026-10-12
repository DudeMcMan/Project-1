# Campus Resource Reservation System - User Documentation

## Getting Started

1. Open a terminal and navigate into the `Project 1` folder.
2. Build the program:
g++ -std=c++17 -Wall -Iinclude src/main.cpp src/ReservationManager.cpp src/ResourceManager.cpp src/ReservationList.cpp src/WaitingList.cpp src/Resource.cpp src/Reservation.cpp src/CancellationHistory.cpp -o campus_system
3. Run it:
./campus_system
4. The program loads existing resources and reservations from the `data/` folder automatically on startup.

## Using the Menu

When the program starts, you'll see a numbered menu. Type the number of the option you want and press Enter.

**1. View Resources** - Shows every resource in the system (study rooms, laptops, calculators, lab equipment, tutoring appointments) along with which dates, if any, each one is currently booked on.

**2. Create Reservation** - Walks you through booking a resource. You'll be asked for your student ID, your name, the resource ID you want (for example `R101`), and the date you want it. If that resource is already booked on that date, you'll automatically be placed on the waiting list for it instead.

**3. Cancel Reservation** - Enter a reservation ID to cancel it. The resource becomes free on that date again, and if anyone was waiting for that exact resource and date, they are automatically given the reservation.

**4. View Waiting Lists** - Shows everyone currently waiting for a resource to open up, in the order they joined the waiting list.

**5. Undo Cancellation** - Restores your most recently cancelled reservation, as long as the resource is still free on that date and the reservation ID hasn't been reused.

**6. Search Reservations** - Lets you search either by reservation ID (to look up one specific reservation) or by student name (to see everything a particular student has booked).

**7. Sort Resources** - Sorts and displays all resources alphabetically by name.

**8. Generate Report** - Choose from four reports:
   - Active Reservations - every reservation currently in the system
   - Resource Utilization - how many reservations each resource has had
   - Most Requested Resources - resources ranked from most to least reserved
   - Waiting-List Statistics - how many students are waiting, broken down by resource

**9. Exit** - Closes the program.
