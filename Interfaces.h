#ifndef INTERFACES_H
#define INTERFACES_H

#include <string>
using namespace std;

// ============================================================
//  ABSTRACT CLASS: Billable  (acts as an Interface)
//  Any class that can generate a fee must implement this.
//  Applied to: Appointment, Procedure
// ============================================================
class Billable {
public:
    virtual float calculate_fee() = 0;   // pure virtual (abstract)
    virtual ~Billable() {}
};


// ============================================================
//  ABSTRACT CLASS: Schedulable  (acts as an Interface)
//  Any class that owns bookable slots must implement this.
//  Applied to: Doctor, Room (Doctor used here)
// ============================================================
class Schedulable {
public:
    virtual void book_slot(string date, string time) = 0;  // pure virtual
    virtual ~Schedulable() {}
};

#endif
