# Hotel Management System

A C++ command-line hotel reservation management system built as a final project for *C++ programming* course. The program handles room initialization, reservations, cancellations, and persistent storage using a text file.

---

## Features

- Create new reservations with automatic room assignment
- Search for reservations by reservation number or guest name
- Cancel existing reservations
- Randomly generated reservation numbers and discounts
- Persistent storage — reservations are saved and loaded between sessions
- Automatic room initialization on first run

---

## How to build

```
g++ hotelproject.cpp -o hotelproject
```

---

## How to use

Run the program

On mac/linux:
```
./hotelproject
```

Or on windows:
```
./hotelproject
```

You will be greeted with the main menu:

```
Welcome to the Hotel Management System!
***************************************
Input 1 to search for a reservation
Input 2 to create a new reservation
Input 3 to cancel a reservation
Input 4 to reset system
Input 0 to exit
***************************************
```

---

## Rooms

On first run the system randomly generates between 40 and 300 rooms, split evenly between 1-bed and 2-bed rooms. Room data is saved to `roominfo.txt` and loaded on subsequent runs.

| Room type | Price per night |
|-----------|----------------|
| 1-bed     | 100€           |
| 2-bed     | 150€           |

A random discount of 0%, 10%, or 20% is applied to each reservation.

---

## Storage

Room and reservation data is stored in `roominfo.txt` in the working directory. The file is automatically created on first run and updated after every reservation or cancellation.

---

## Project structure

| File | Description |
|------|-------------|
| `hotelproject.cpp` | All source code |
| `roominfo.txt` | Generated at runtime, stores room data |

---

## AI usage

AI was used in this project for understand how different concepts work in C++, and to make sure my code meets the standards. All the code is written by the author.
