#include "Staff.h"
#include <iostream>

Staff::Staff(string staff_id, string name, string DOB,
             string CNIC, string contact, string address,
             string department, string role, string shift)
    : Person(name, DOB, CNIC, contact, address),
      staff_id(staff_id), department(department),
      role(role), shift(shift), attendance(0) {}

// ----------------------------------------------------------
string Staff::get_shift() const { return shift; }

// ----------------------------------------------------------
void Staff::log_attendance() {
    attendance++;
    cout << "  [OK] Attendance logged for " << name
         << " (Total: " << attendance << " days)\n";
}

// ----------------------------------------------------------
void Staff::display_info() const {
    cout << "  Staff ID    : " << staff_id   << endl;
    cout << "  Department  : " << department << endl;
    cout << "  Role        : " << role       << endl;
    cout << "  Shift       : " << shift      << endl;
    cout << "  Attendance  : " << attendance << " days" << endl;
    Person::display_info();
}
