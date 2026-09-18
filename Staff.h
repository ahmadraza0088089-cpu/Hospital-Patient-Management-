#ifndef STAFF_H
#define STAFF_H

#include "Person.h"
using namespace std;

// ============================================================
//  CLASS: Staff  (inherits Person)
//  Represents non-doctor hospital employees
// ============================================================
class Staff : public Person {
private:
    string department;
    string role;
    string shift;       // "Morning" / "Evening" / "Night"
    int    attendance;  // count of logged days

public:
    string staff_id;    // e.g., "S001"

    Staff(string staff_id, string name, string DOB,
          string CNIC, string contact, string address,
          string department, string role, string shift);

    // Methods (as specified in project)
    string get_shift()       const;
    void   log_attendance();          // increments attendance counter
    void   display_info()    const;   // overrides Person::display_info
};

#endif
