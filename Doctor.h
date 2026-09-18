#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include "Interfaces.h"
#include "Exceptions.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

// ============================================================
//  CLASS: Doctor  (inherits Person, implements Schedulable)
//  Manages doctor profile and weekly schedule
// ============================================================
class Doctor : public Person, public Schedulable {
private:
    string speciality;
    float  fee;
    // Private schedule: date -> list of booked times
    // "__schedule" mirrors Python double-underscore (private)
    map<string, vector<string>> __schedule;

    // Helper: validate time is within 09:00-17:00
    bool isValidHour(const string& time) const;

public:
    string doctor_id;  // e.g., "D001"

    Doctor(string doctor_id, string name, string DOB,
           string CNIC, string contact, string address,
           string speciality, float fee);

    // Getters
    string getSpeciality() const;
    float  getFee()        const;
    string getDoctorId()   const;

    // Methods (as specified in project)
    void book_slot(string date, string time) override;
    bool is_available(string date, string time) const;
    void get_appointments() const;   // prints all booked slots
    void display_info()     const;   // overrides Person::display_info
};

#endif
