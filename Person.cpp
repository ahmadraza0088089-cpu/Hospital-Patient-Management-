#include "Person.h"
#include <sstream>

// ----------------------------------------------------------
Person::Person(string name, string DOB, string CNIC,
               string contact, string address)
    : name(name), DOB(DOB), CNIC(CNIC),
      contact(contact), address(address) {}

// ----------------------------------------------------------
string Person::getName()    const { return name; }
string Person::getCNIC()    const { return CNIC; }
string Person::getContact() const { return contact; }

// ----------------------------------------------------------
// Calculates age from DOB string "DD/MM/YYYY"
int Person::get_age() const {
    // Simple year-only calculation (beginner-friendly)
    int birthYear = stoi(DOB.substr(6, 4));
    // Using fixed current year 2025
    return 2025 - birthYear;
}

// ----------------------------------------------------------
void Person::display_info() const {
    cout << "  Name    : " << name    << endl;
    cout << "  DOB     : " << DOB     << endl;
    cout << "  CNIC    : " << CNIC    << endl;
    cout << "  Contact : " << contact << endl;
    cout << "  Address : " << address << endl;
    cout << "  Age     : " << get_age() << " years" << endl;
}
