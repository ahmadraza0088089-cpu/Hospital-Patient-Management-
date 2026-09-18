#include "Doctor.h"
#include <iostream>

Doctor::Doctor(string doctor_id, string name, string DOB,
               string CNIC, string contact, string address,
               string speciality, float fee)
    : Person(name, DOB, CNIC, contact, address),
      doctor_id(doctor_id), speciality(speciality), fee(fee) {}

string Doctor::getSpeciality() const { return speciality; }
float  Doctor::getFee()        const { return fee; }
string Doctor::getDoctorId()   const { return doctor_id; }

// ----------------------------------------------------------
// Validates hour is between 9 and 17
bool Doctor::isValidHour(const string& time) const {
    // time format: "HH:MM"
    int hour = stoi(time.substr(0, 2));
    return (hour >= 9 && hour < 17);
}

// ----------------------------------------------------------
// Book a slot — throws if conflict or invalid hour
void Doctor::book_slot(string date, string time) {
    if (!isValidHour(time)) {
        throw InvalidSlotError(
            "Slot " + time + " is outside working hours (09:00-17:00).");
    }
    vector<string>& booked = __schedule[date];
    for (const string& t : booked) {
        if (t == time) {
            throw AppointmentConflictError(
                "Dr. " + name + " is already booked at "
                + time + " on " + date + ".");
        }
    }
    booked.push_back(time);
}

// ----------------------------------------------------------
bool Doctor::is_available(string date, string time) const {
    auto it = __schedule.find(date);
    if (it == __schedule.end()) return true;   // no bookings that day
    for (const string& t : it->second) {
        if (t == time) return false;
    }
    return true;
}

// ----------------------------------------------------------
void Doctor::get_appointments() const {
    cout << "\n  Appointments for Dr. " << name << ":\n";
    if (__schedule.empty()) {
        cout << "  (No appointments booked)\n";
        return;
    }
    for (const auto& entry : __schedule) {
        cout << "  Date: " << entry.first << "  ->  ";
        for (const string& t : entry.second)
            cout << t << "  ";
        cout << endl;
    }
}

// ----------------------------------------------------------
void Doctor::display_info() const {
    cout << "  Doctor ID   : " << doctor_id  << endl;
    cout << "  Speciality  : " << speciality << endl;
    cout << "  Fee (PKR)   : " << fee        << endl;
    Person::display_info();
}
