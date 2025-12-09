// Arttu Pietarinen
// 5 point assignment (I hope so)
// I could have used toupper to make the search not case-sensitive but ran out of time.

// Including necessary libraries
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <climits>
#include <string>
#include <vector>
using namespace std;

// Defining the structure for room information
struct roominfo {
    int roomnumber;
    int beds;
    bool isavailable;
    string guestname;
    int nights;
    int resnumber;
    int price;
};

// Defining constants for room prices
const int price1bed = 100;
const int price2bed = 150;

// Function prototypes
void mainmenu(vector<roominfo> &roomlist);
void printres(const roominfo &room);
void searchres(vector<roominfo> &roomlist);
void newsearch(vector<roominfo> &roomlist);
void newres(vector<roominfo> &roomlist);
void resagain(vector<roominfo> &roomlist);
void cancelres(vector<roominfo> &roomlist);
void cancelagain(vector<roominfo> &roomlist);
void resetsystem(vector<roominfo> &roomlist);
void roominit(vector<roominfo> &roomlist);
void loadroominfo(vector<roominfo> &roomlist);
bool file_exists(const string &name);
void saverooms(const vector<roominfo> &roomlist);
void clearConsole();
bool isResNumberUsed(const vector<roominfo> &roomlist, int resnumber);
int getNumberInRange(int min, int max, string instruction, string error);

// Minimal main function
int main() {
    srand(time(0));
    vector<roominfo> roomlist;

    if (!file_exists("roominfo.txt")) {
        roominit(roomlist);
    }

    else {
        loadroominfo(roomlist);
    }

    clearConsole();
    mainmenu(roomlist);

    return 0;
}

// Main menu function
void mainmenu(vector<roominfo> &roomlist) {
    do {

        cout << "Welcome to the Hotel Management System!" << endl;
        cout << "***************************************" << endl;
        cout << "Input 1 to search for a reservation" << endl;
        cout << "Input 2 to create a new reservation" << endl;
        cout << "Input 3 to cancel a reservation" << endl;
        cout << "Input 4 to reset system" << endl;
        cout << "Input 0 to exit" << endl;
        cout << "***************************************" << endl;
        int choice = getNumberInRange(0, 4, "Please input your choice: ", "Invalid choice. Please enter a number between 0 and 4: ");

        cout << endl;

        if (choice == 1) {
            searchres(roomlist);
        } else if (choice == 2) {
            newres(roomlist);
        } else if (choice == 3) {
            cancelres(roomlist);
        } else if (choice == 4) {
            resetsystem(roomlist);
        } else if (choice == 0) {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid choice" << endl;
        }

    } while (true);
}

// Function to print reservation details
void printres(const roominfo &room) {
    cout << endl;
    cout << "Guest Name: " << room.guestname << endl;
    cout << "Room Number: " << room.roomnumber << endl;
    cout << "Number of Beds: " << room.beds << endl;
    cout << "Number of Nights: " << room.nights << endl;
    cout << "Reservation Number: " << room.resnumber << endl;
    cout << "Total Price: " << room.price << " euros" << endl;
    cout << endl;
}

// Function to search for a reservation
void searchres(vector<roominfo> &roomlist) {
    clearConsole();

    // Making sure there are reservations to search for
    bool anyreserved = false;
    for (const auto &room : roomlist) {
        if (!room.isavailable) {
            anyreserved = true;
            break;
        }
    }

    // If no reservations exist, prompt to make one or cancel
    if (!anyreserved) {
        cout << "No reservations found." << endl;
        cout << "To make one, input 1. To cancel, input 0: ";
        int choice = getNumberInRange(0, 1, "", "Invalid input. Please enter 0 or 1: ");
        if (choice == 1) {
            clearConsole();
            newres(roomlist);
        } else {
            clearConsole();
        }
        return;
    }

    // Asking user how they want to search
    int choice = getNumberInRange(0, 2, "Search by: 1. Reservation Number  2. Guest Name\nInput choice (Or 0 to cancel): ", "Invalid choice. Please enter 0, 1, or 2: ");

    if (choice == 0) {
        clearConsole();
        return;
    }

    // Searching by reservation number
    if (choice == 1) {
        int resnumber;
        cout << "Input reservation number (Or 0 to cancel): ";
        cin >> resnumber;
        if (resnumber == 0) {
            clearConsole();
            return;
        }

        bool found = false;
        for (const auto &room : roomlist) {
            if (room.resnumber == resnumber) {
                clearConsole();
                found = true;
                cout << "Reservation found:" << endl;
                printres(room);
                newsearch(roomlist);

                break;
            }
        }

        if (!found) {
            cout << endl
                 << "Reservation not found." << endl;
            newsearch(roomlist);
        }

        // Searching by guest name
    } else if (choice == 2) {
        string name;
        cin.ignore();
        cout << "Input guest name (Or 0 to cancel): ";
        getline(cin, name);
        if (name == "0") {
            clearConsole();
            return;
        }

        clearConsole();
        bool found = false;
        for (const auto &room : roomlist) {
            if (room.guestname == name) {
                found = true;
                cout << "Reservation found:" << endl;
                printres(room);
                newsearch(roomlist);
            }
        }

        if (!found) {
            cout << "Reservation not found." << endl;
            newsearch(roomlist);
        }
    }
}

// Function if user wants to search for another reservation
void newsearch(vector<roominfo> &roomlist) {
    {

        int continuechoice;
        cout << "Input 1 to search for another reservation, or 0 to return to main menu: ";
        cin >> continuechoice;
        if (continuechoice == 1) {
            clearConsole();
            searchres(roomlist);
        }

        if (continuechoice == 0) {
            clearConsole();
            return;
        }
    }
}

// Function to create a new reservation
void newres(vector<roominfo> &roomlist) {
    clearConsole();
    int count1 = 0;
    int count2 = 0;
    int beds;
    string name;
    int nights;
    int totalprice = 0;

    for (const auto &room : roomlist) {
        if (room.isavailable) {
            if (room.beds == 1)
                count1++;
            else if (room.beds == 2)
                count2++;
        }
    }

    cout << "Total number of rooms: " << roomlist.size() << endl;
    cout << "Available 1-bed rooms: " << count1 << endl;
    cout << "Available 2-bed rooms: " << count2 << endl
         << endl;

    cin.ignore();

    cout << "Insert customer name (Or 0 to cancel): ";
    getline(cin, name);
    if (name == "0") {
        clearConsole();
        return;
    }

    do {

        beds = getNumberInRange(0, 2, "Insert number of beds (1 or 2) (Or 0 to cancel): ", "Invalid input. Please enter 1 or 2 (Or 0 to cancel): ");

        if (beds == 0) {
            clearConsole();
            return;
        }

        if (beds != 1 && beds != 2) {
            cout << "Invalid number of beds. Please enter 1 or 2 (Or 0 to cancel)." << endl;
        }

        // Checking availability of selected bed type
        if (beds == 1 && count1 == 0) {
            cout << endl
                 << "No available 1-bed rooms. Please choose 2 beds or cancel." << endl;
            beds = -1;
        }

        if (beds == 2 && count2 == 0) {
            cout << endl
                 << "No available 2-bed rooms. Please choose 1 bed or cancel." << endl;
            beds = -1;
        }

    } while (beds != 1 && beds != 2);

    nights = getNumberInRange(0, INT_MAX, "Insert number of nights (Or 0 to cancel): ", "Invalid input. Please enter a number (Or 0 to cancel): ");
    if (nights == 0) {
        clearConsole();
        return;
    }

    // Generating a unique reservation number
    int resnumber = 1000 + rand() % 9000;
    while (isResNumberUsed(roomlist, resnumber)) {
        resnumber = 1000 + rand() % 9000;
    }

    int discountoptions[3] = {0, 10, 20};
    int discount = discountoptions[rand() % 3];

    if (beds == 1) {
        totalprice = (price1bed * nights) * (100 - discount) / 100;
    } else {
        totalprice = (price2bed * nights) * (100 - discount) / 100;
    }

    clearConsole();
    cout << "Reservation details:" << endl
         << endl;
    cout << "Guest name: " << name << endl;
    cout << "Number of beds: " << beds << endl;
    cout << "Number of nights: " << nights << endl;
    cout << "Reservation number: " << resnumber << endl;
    cout << "Total price: " << totalprice << " euros" << endl;

    int confirm;
    cout << endl
         << "Input 1 to confirm reservation, or 0 to cancel: ";
    cin >> confirm;
    if (confirm == 1) {
        for (auto &room : roomlist) {
            if (room.isavailable && room.beds == beds) {
                room.isavailable = false;
                room.guestname = name;
                room.nights = nights;
                room.resnumber = resnumber;
                room.price = totalprice;

                saverooms(roomlist);

                clearConsole();

                break;
            }
        }

        cout << "Reservation " << resnumber << " confirmed!" << endl
             << endl;
        resagain(roomlist);

    } else {
        clearConsole();
        return;
    }
}

// Function if user wants to make another reservation
void resagain(vector<roominfo> &roomlist) {
    {

        int continuechoice = getNumberInRange(0, 1, "Input 1 to make another reservation, or 0 to return to main menu: ", "Invalid input. Please enter 0 or 1: ");
        if (continuechoice == 1) {
            clearConsole();
            newres(roomlist);
        }

        if (continuechoice == 0) {
            clearConsole();
            return;
        }
    }
}

// Function to cancel a reservation
void cancelres(vector<roominfo> &roomlist) {
    clearConsole();
    int resnumber = getNumberInRange(0, 9999, "Input reservation number to cancel (Or 0 to cancel): ", "Invalid input. Please enter a valid reservation number (Or 0 to cancel): ");
    cout << endl;
    if (resnumber == 0) {
        clearConsole();
        return;
    }

    bool found = false;
    for (auto &room : roomlist) {
        if (room.resnumber == resnumber) {
            found = true;
            clearConsole();
            cout << "Reservation found:" << endl;
            printres(room);

            int confirm;
            cout << "Input 1 to confirm cancellation, or 0 to abort: ";
            cin >> confirm;
            if (confirm == 1) {
                room.isavailable = true;
                room.guestname = "empty";
                room.nights = 0;
                room.resnumber = 0;
                room.price = 0;

                saverooms(roomlist);

                clearConsole();
                cout << "Reservation cancelled." << endl
                     << endl;
                cancelagain(roomlist);
            }

            break;
        }
    }

    if (!found) {
        cout << "Reservation not found." << endl;
        cancelagain(roomlist);
    }
}

// Function if user wants to cancel another reservation
void cancelagain(vector<roominfo> &roomlist) {
    int continuechoice = getNumberInRange(0, 1, "Input 1 to cancel another reservation, or 0 to return to main menu: ", "Invalid input. Please enter 0 or 1: ");
    if (continuechoice == 1) {
        clearConsole();
        cancelres(roomlist);
    }
    if (continuechoice == 0) {
        clearConsole();
        return;
    }
}

// Function to reset the system
void resetsystem(vector<roominfo> &roomlist) {
    clearConsole();
    cout << "Are you sure you want to reset the system? This will delete all reservations." << endl;
    cout << "Input 1 to confirm, or 0 to cancel: ";
    int confirm;
    cin >> confirm;
    if (confirm == 1) {
        roominit(roomlist);
        clearConsole();
        return;
    } else {
        clearConsole();
        return;
    }
}

// Function to initialize room information
void roominit(vector<roominfo> &roomlist) {

    // Generating a random even number of rooms between 40 and 300
    int roomrand = 40 + rand() % 261;

    if (roomrand % 2 != 0) {
        roomrand++;
    }

    int totalrooms = roomrand;

    roomlist.clear();
    roomlist.resize(totalrooms);

    // Initializing room details
    for (int i = 0; i < totalrooms; i++) {
        roomlist[i].roomnumber = i + 1;

        if (i < totalrooms / 2) {
            roomlist[i].beds = 1;
        } else {
            roomlist[i].beds = 2;
        }

        roomlist[i].isavailable = true;
        roomlist[i].guestname = "empty";
        roomlist[i].nights = 0;
        roomlist[i].resnumber = 0;
        roomlist[i].price = 0;
    }

    // Saving room information to file
    ofstream file("roominfo.txt");

    file << roomlist.size() << endl;

    // Text file format: roomnumber, beds, isavailable, guestname, nights, resnumber, price
    for (const auto &room : roomlist) {
        file << endl
             << room.roomnumber << endl
             << room.beds << endl
             << room.isavailable << endl
             << room.guestname << endl
             << room.nights << endl
             << room.resnumber << endl
             << room.price << endl;
    }
}

// Function to load room information from file
void loadroominfo(vector<roominfo> &roomlist) {
    ifstream file("roominfo.txt");
    if (!file)
        return;

    int totalrooms;

    file >> totalrooms;
    string dummy;
    getline(file, dummy);
    getline(file, dummy);

    roomlist.clear();
    roomlist.resize(totalrooms);

    for (int i = 0; i < totalrooms; i++) {
        file >> roomlist[i].roomnumber;
        getline(file, dummy);

        file >> roomlist[i].beds;
        getline(file, dummy);

        file >> roomlist[i].isavailable;
        getline(file, dummy);

        getline(file, roomlist[i].guestname);

        file >> roomlist[i].nights;
        getline(file, dummy);

        file >> roomlist[i].resnumber;
        getline(file, dummy);

        file >> roomlist[i].price;
        getline(file, dummy);

        getline(file, dummy);
    }
}

// Function to check if a file exists
bool file_exists(const string &name) {
    ifstream f(name);
    return f.good();
}

// Function to save room information to file
void saverooms(const vector<roominfo> &roomlist) {
    ofstream file("roominfo.txt");
    if (!file)
        return;

    file << roomlist.size() << endl;

    for (const auto &room : roomlist) {
        file << endl
             << room.roomnumber << endl
             << room.beds << endl
             << room.isavailable << endl
             << room.guestname << endl
             << room.nights << endl
             << room.resnumber << endl
             << room.price << endl;
    }
}

// Function to clear the console
void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to check if reservation number is not used
bool isResNumberUsed(const vector<roominfo> &roomlist, int resnumber) {
    for (const auto &room : roomlist) {
        if (room.resnumber == resnumber) {
            return true;
        }
    }
    return false;
}

// Function to get a number within a specified range with input validation
int getNumberInRange(int min, int max, string instruction, string error) {
    int number;

    cout << instruction;
    cin >> number;

    while (cin.fail() || (number < min || number > max)) {
        cout << error;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> number;
    }

    return number;
}
