#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Donor class to store donor information
class Donor {
public:
    string name;
    int age;
    string gender;
    string bloodGroup;
    string contactNo;
    string location;  // Added location attribute

    // Constructor to initialize donor details
    Donor(string name, int age, string gender, string bloodGroup, string contactNo, string location) {
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->bloodGroup = bloodGroup;
        this->contactNo = contactNo;
        this->location = location;
    }

    // Function to display donor details
    void displayDonorDetails() const {
        cout << "\nName: " << name
             << "\nAge: " << age
             << "\nGender: " << gender
             << "\nBlood Group: " << bloodGroup
             << "\nContact No: " << contactNo
             << "\nLocation: " << location << endl;
    }

    // Function to save donor to file
    // Now the function is `const`-correct and will not modify the object
    void saveToFile(ofstream &outFile) const {
        outFile << name << "\n"
                << age << "\n"
                << gender << "\n"
                << bloodGroup << "\n"
                << contactNo << "\n"
                << location << "\n";
    }

    // Static function to load donor from file
    static Donor loadFromFile(ifstream &inFile) {
        string name, gender, bloodGroup, contactNo, location;
        int age;

        getline(inFile, name); // Get the name
        inFile >> age;         // Get age
        inFile.ignore();       // Ignore the newline after reading age
        getline(inFile, gender);
        getline(inFile, bloodGroup);
        getline(inFile, contactNo);
        getline(inFile, location);

        // Move the file pointer back to the next donor's name
        inFile.ignore();  // This is to skip the newline between donors' records

        return Donor(name, age, gender, bloodGroup, contactNo, location);
    }
};

// BloodBank class to manage donors
class BloodBank {
private:
    vector<Donor> donors; // List to store donors
    const string filename ="Reportfile1.txt"; // File name

public:
    // Constructor to initialize the Blood Bank by loading data from the file
    BloodBank() {
        loadFromFile();
    }

    // Function to add a new donor
    void addDonor() {
        string name, gender, bloodGroup, contactNo, location;
        int age;

        cout << "Enter Donor Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Gender (M/F): ";
        cin >> gender;
        cout << "Enter Blood Group (A+/A-/B+/B-/O+/O-/AB+/AB-): ";
        cin >> bloodGroup;
        cout << "Enter Contact Number: ";
        cin >> contactNo;
        cout << "Enter Location: ";  // Prompt for location
        cin.ignore();  // Ignore the newline character after reading contact number
        getline(cin, location);

        Donor newDonor(name, age, gender, bloodGroup, contactNo, location);
        donors.push_back(newDonor); // Adding donor to the list

        // Save the donor to file immediately after adding
        saveToFile();

        cout << "\nDonor added successfully!\n";
    }

    // Function to display all donors
    void viewAllDonors() const {
        if (donors.empty()) {
            cout << "\nNo donors available!\n";
            return;
        }

        cout << "\nList of Donors:\n";
        for (size_t i = 0; i < donors.size(); i++) {
            cout << "\nDonor " << i + 1 << ":";
            donors[i].displayDonorDetails();
        }
    }

    // Function to search donors by blood group
    void searchDonorByBloodGroup() const {
        if (donors.empty()) {
            cout << "\nNo donors available!\n";
            return;
        }

        string bloodGroup;
        cout << "Enter Blood Group to Search (A+/A-/B+/B-/O+/O-/AB+/AB-): ";
        cin >> bloodGroup;

        bool found = false;
        for (size_t i = 0; i < donors.size(); i++) {
            if (donors[i].bloodGroup == bloodGroup) {
                donors[i].displayDonorDetails();
                found = true;
            }
        }

        if (!found) {
            cout << "\nNo donors found with blood group " << bloodGroup << "!\n";
        }
    }

    // Function to search donors by location
    void searchDonorByLocation() const {
        if (donors.empty()) {
            cout << "\nNo donors available!\n";
            return;
        }

        string location;
        cout << "Enter Location to Search: ";
        cin.ignore();  // Ignore any leftover newline character
        getline(cin, location);

        bool found = false;
        for (size_t i = 0; i < donors.size(); i++) {
            if (donors[i].location == location) {
                donors[i].displayDonorDetails();
                found = true;
            }
        }

        if (!found) {
            cout << "\nNo donors found in location " << location << "!\n";
        }
    }

    // Function to save all donors to file
    void saveToFile() {
        ofstream outFile(filename, ios::out | ios::trunc);  // Open file in write mode and truncate it
        if (outFile.is_open()) {
            for (const Donor &donor : donors) {
                donor.saveToFile(outFile);  // Write each donor's details to file
            }
            outFile.close();
            cout << "\nDonor data saved to " << filename << ".\n";
        } else {
            cout << "\nError opening file for writing!\n";
        }
    }

    // Function to load donors from file
    void loadFromFile() {
        ifstream inFile(filename, ios::in);
        if (inFile.is_open()) {
            while (inFile.peek() != EOF) {
                donors.push_back(Donor::loadFromFile(inFile));  // Load each donor from file
            }
            inFile.close();
            cout << "\nDonor data loaded from " << filename << ".\n";
        } else {
            cout << "\nNo previous donor data found.\n";
        }
    }
};

// Main function to drive the program
int main() {
    BloodBank bloodBank;
    int choice;

    while (true) {
        // Displaying the menu
        cout << "\n*";
        cout << "\n * Blood Bank Management System *";
        cout << "\n*";
        cout << "\n            SERVICES             ";
        cout << "\n_";
        cout << "\n_";
        cout << "\n          1. Add Donor           ";
        cout << "\n         --------------          ";
        cout << "\n_";
        cout << "\n       2. View All Donors        ";
        cout << "\n       ------------------        ";
        cout << "\n ________________________________";
        cout << "\n3. Search Donor by Blood Group   ";
        cout << "\n  -----------------------------  ";
        cout << "\n_";
        cout << "\n4. Search Donor by Location      ";  
        cout << "\n   ------------------------      ";
        cout << "\n_";
        cout << "\n             5.Exit              ";
        cout << "\n            --------             ";
        cout << "\n_";
        cout << "\n         6. Enter your choice--> ";
        cin>>choice;


        switch (choice) {
            case 1:
                bloodBank.addDonor();
                break;
            case 2:
                bloodBank.viewAllDonors();
                break;
            case 3:
                bloodBank.searchDonorByBloodGroup();
                break;
            case 4:
                bloodBank.searchDonorByLocation();
                break;
            case 5:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}
