#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;
class Shoe {
public:
    string name;
    string brand;
    int stock;
    int size;

    Shoe(const string& n, const string& b, int s, int sz) : name(n), brand(b), stock(s), size(sz) {}
};

class Store {
public:
    string location;
    vector<Shoe> inventory;

    Store(const string& loc) : location(loc) {}

    void displayInventory() const {
        cout << "--------------------------------------------------------\n";
        cout << "\t\t      " << location << ":\n";
        cout << "--------------------------------------------------------\n";
        for (const Shoe& shoe : inventory) {
            cout << "Name: " << shoe.name << ", Brand: " << shoe.brand << ", Size: " << shoe.size
                << ", Stock: " << shoe.stock << "\n";
        }
        std::cout << "\n";
    }
};

class Customer {
public:
    string name;
    string email;
    int customerNumber;
    int shoeSize;
    string selectedShoe;
    string selectedStore;
    bool buyDecision;

    Customer(const string& n, const string& e, int num, int size)
        : name(n), email(e), customerNumber(num), shoeSize(size), buyDecision(false) {}
};

class ShoeStore {
private:
    vector<Store> stores;
    vector<Customer> customers;
    int customerCounter;

public:
    ShoeStore() : customerCounter(1) {}

    void addStore(const string& location, const vector<Shoe>& inventory) {
        stores.emplace_back(location);
        stores.back().inventory = inventory;
    }

    void viewAndSelectShoes() {
        int choice;
        cout << "----------------------------------------\n";
        cout << "WELCOME TO THE VIP SHOE TELLER SYSTEM\n";
        cout << "----------------------------------------\n";

        cout << "1. Check In for Viewing and Input User Data\n";
        cout << "2. Exit\n";
        cout << "Enter your choice (1-2): ";
        cin >> choice;

        switch (choice) {
        case 1:
            checkInForViewing();
            break;
        case 2:

            cout << "Exiting the program\n";
            exit(0);
        default:
            cout << "Invalid choice\n";
        }
    }

    bool checkInForViewing() {
        string name, email;
        int size;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Please input your name: ";
        getline(cin, name);
        cout << "Please input your email address: ";
        getline(cin, email);

        customers.emplace_back(name, email, customerCounter++, 0);


        cout << "\nAvailable Shoes for Viewing:\n";
        cout << "1.) Dunk\n";
        cout << "2.) Rosherun\n";
        cout << "3.) Fuelcell\n";
        cout << "4.) Hovr\n";
        cout << "5.) Classic\n\n";
        for (const Store& store : stores) {
            store.displayInventory();
        }


        cout << "Please select a shoe (by name): ";
        cin >> customers.back().selectedShoe;


        while (true) {
            cout << "Select a shoe size: ";
            cin >> size;

            if (cin.fail()) {

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid shoe size (numeric).\n";
            }
            else {

                customers.back().shoeSize = size;
                break;
            }
        }


        if (!checkStoreAvailability(customers.back())) {
            cout << "Thank you for using our service.\n\n";
            return false;
        }


        scheduleViewing(customers.back());


        cout << "\nDo you confirm the viewing for the selected shoe? (1 for yes, 0 for no): ";
        cin >> customers.back().buyDecision;
        if (customers.back().buyDecision == 1) {
            cout << "\nCongratulations! We have reserved a viewing schedule for you\n";
            cout << "Please screenshot this confirmation and show it to the manager when you arrive\n";
            cout << "Thank you for using our service.\n\n";
            return true;
        }
        else {
            cout << "Thank you for using our service.\n\n";
        }

    }



    bool checkStoreAvailability(Customer& customer) {
        cout << "\nChecking store availability for " << customer.selectedShoe << " in size " << customer.shoeSize
            << "..\n";

        for (Store& store : stores) {
            for (Shoe& shoe : store.inventory) {
                if (shoe.name == customer.selectedShoe && shoe.size == customer.shoeSize && shoe.stock > 0) {
                    cout << customer.selectedShoe << " is available at " << store.location << "\n";
                    customer.selectedStore = store.location;
                    return true;
                }
            }
        }

        cout << "Sorry but " << customers.back().selectedShoe << " in size: " << customers.back().shoeSize << " is not available in any store\n";
        return false;
    }

    void scheduleViewing(const Customer& customer) {

        cout << "Queuing a view schedule for Customer: " << customer.customerNumber << " ("
            << customer.name << ") at " << customer.selectedStore << "\n";
    }
};

int main() {
    ShoeStore shoeStore;

    shoeStore.addStore("Cubao Branch", { {"Dunk", "Nike", 10, 8}, {"Classic", "Onitsuka Tiger", 7, 9}, {"Hovr", "Underarmour", 2, 9} });
    shoeStore.addStore("Gilmore Branch", { {"Hovr", "Underarmour", 8, 7}, {"Fuelcell", "New Balance", 2, 11} ,{"Rosherun", "Adidas", 3, 7} });
    shoeStore.addStore("Morayta Branch", { {"Rosherun", "Adidas", 10, 7}, {"Classic", "Onitsuka", 12, 10},{"Dunk", "Nike", 4, 10} });
    shoeStore.addStore("Quezon Branch", { {"Hovr", "Underarmour", 5, 9}, {"Fuelcell", "New Balance", 12, 9},{"Classic", "Onitsuka", 2, 8} });

    while (true) {
        shoeStore.viewAndSelectShoes();
    }

    return 0;
}