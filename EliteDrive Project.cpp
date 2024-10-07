#include <iostream>
#include <string>
#include <vector>
#include "reader.h"
using namespace std;

class Customer {
public:
    string name;
    string contact;
    string rentalDate;
    Customer* next;
    Customer(string n, string c, string d) : name(n), contact(c), rentalDate(d), next(nullptr) {}
};


class Car {
private:
    Node* head;
    Customer* customersHead;
public:
    Car() : head(nullptr), customersHead(nullptr) {}
    void reader() {
        string line;
        ifstream file("cars.txt");
        if (file.is_open()) {
            while (getline(file, line)) {
                string t, b, m, y;
                istringstream al(line);
                getline(al, t, ',');
                getline(al, b, ',');
                getline(al, m, ',');
                getline(al, y);
                Node* p = new Node(t, b, m, y);
                p->next = head;
                head = p;
            }
            file.close();
        }
        else {
            cout << "File is not open! ";
        }
    }

    void printData() {

        Node* temp = head;
        while (temp != nullptr) {
            cout << "Type: " << temp->type << ", Brand: " << temp->brand << ", Model: " << temp->model << ", Year: " << temp->year;
            if (temp->rented == true)
                cout << ", Rented: Yes" << endl;
            else
                cout << ", Rented: No" << endl;
            temp = temp->next;
        }
    }


    void rent() {
        string type_;
        cout << "Select the car type you want to rent: (Economy, Compact, Midsize, Full - Size, SUV, Crossover, Luxury, Convertible, Van, Minivan, Truck, Electric, Hybrid): ";
        cin >> type_;
        if (isValidCarType(type_)) {
            Node* walk = head;
            bool found = false;
            while (walk != nullptr) {
                if (walk->type == type_ && !walk->rented) {
                    found = true;
                    cout << "Brand: " << walk->brand << ", Model: " << walk->model << ", Year: " << walk->year << endl;
                }
                walk = walk->next;
            }
            if (!found) {
                cout << "No available cars of selected type." << endl;
            }
            else {
                string selectedBrand, selectedModel, selectedYear;
                cout << "Enter the brand, model, and year of the car you want to rent: ";
                cin >> selectedBrand >> selectedModel >> selectedYear;
                walk = head;
                while (walk != nullptr) {
                    if (walk->type == type_ && walk->brand == selectedBrand && walk->model == selectedModel && walk->year == selectedYear && !walk->rented) {
                        walk->rented = true;
                        addCustomer();
                        cout << "Car rented successfully." << endl;
                        return;
                    }
                    walk = walk->next;
                }
                cout << "Selected car is not available." << endl;
            }
        }
        else {
            cout << "Invalid car type." << endl;
        }
    }


    void addCustomer() {
        string name, contact, date;
        string brand, model, year;

        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your contact number: ";
        cin >> contact;
        cout << "Enter rental date (dd/mm/yyyy): ";
        cin >> date;

        Customer* newCustomer = new Customer(name, contact, date);
        newCustomer->next = customersHead;
        customersHead = newCustomer;
    }


    void printCustomers() {
        Customer* temp = customersHead;
        cout << "\nList of Customers:\n";
        while (temp != nullptr) {
            cout << "Name: " << temp->name << ", Contact: " << temp->contact << ", Rental Date: " << temp->rentalDate <<endl;
            temp = temp->next;
        }
    }

    bool isValidCarType(string type) {
        vector<string> validTypes = { "Economy", "Compact", "Midsize", "Full-Size", "SUV", "Crossover", "Luxury", "Convertible", "Van", "Minivan", "Truck", "Electric", "Hybrid" };
        for (const auto& validType : validTypes) {
            if (type == validType) {
                return true;
            }
        }
        return false;
    }

    void returnRentedCar(string brand, string model) {
        Node* temp = head;
        bool found = false;
        while (temp != nullptr) {
            if (temp->brand == brand && temp->model == model && temp->rented==true) {
                temp->rented = false;
                cout << "Car " << brand << " " << model << " returned successfully." << endl;
                found = true;
                break;
            }
            temp = temp->next;
        }

        if (!found) {
            cout << "No rented car found with brand: " << brand << " and model: " << model << endl;
            return;
        }

        string customerName;
        cout << "Enter the customer name who returned the car: ";
        cin >> customerName;
        Customer* customerTemp = customersHead;
        while (customerTemp != nullptr) {
            if (customerTemp->name == customerName) {
                customerTemp->rentalDate = "Returned: " + customerTemp->rentalDate;
                return;
            }
            customerTemp = customerTemp->next;
        }
        cout << "Customer not found: " << customerName << endl;
    }

    void registerNewCustomer() {
        string name, contact;
        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your contact number: ";
        cin >> contact;

        Customer* newCustomer = new Customer(name, contact, "No renting");
        newCustomer->next = customersHead;
        customersHead = newCustomer;

        cout << "Customer registered successfully." << endl;
    }

    void viewCustomerAccounts() {
        cout << "\nCustomer Accounts and Booking History:\n";
        Customer* temp = customersHead;
        while (temp != nullptr) {
            cout << "Name: " << temp->name << ", Contact: " << temp->contact << ", Rental History: " << temp->rentalDate << endl;
            temp = temp->next;
        }

        string response;
        cout << "\nWould you like to make a new reservation? (yes/no): ";
        cin >> response;
        if (response == "yes" || response == "Yes" || response == "YES") {
            rent();
        }
    }



};





void displayMenu() {
    cout << "===== EliteDrive Car Rental System =====" << endl;
    cout << "1. Display current inventory of available cars" << endl;
    cout << "2. Rent a car" << endl;
    cout << "3. Return a rented car" << endl;
    cout << "4. Display customer information" << endl;
    cout << "5. Register new customer" << endl;
    cout << "6. View customer accounts and booking history" << endl;
    cout << "7. Exit" << endl;
    cout << endl;
}


int main() {
    Car car;
    car.reader(); 
    int choice;
    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            car.printData();
            break;
        case 2:
            car.rent();
            cout << "You selected option 2" << endl;
            break;
        case 3:
        {
            string brand, model;
            cout << "Enter the brand and model of the car to return: ";
            cin >> brand >> model;
            car.returnRentedCar(brand, model);
            break;
        }
        case 4:
            car.printCustomers();
            cout << "You selected option 4" << endl;
            break;
        case 5:
            car.registerNewCustomer();
            cout << "You selected option 5" << endl;
            break;

        case 6:
            car.viewCustomerAccounts();
            cout << "You selected option 6" << endl;
            break;

        case 7:
            cout << "Exiting the program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 7." << endl;
            break;
        }
        cout << endl;
    }

    return 0;
}
