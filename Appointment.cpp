#include "Appointment.h"
#include <iostream>

Appointment::Appointment(string appt_id, Patient* patient,
                         Doctor* doctor, string date, string time)
    : appt_id(appt_id), patient(patient), doctor(doctor),
      date(date), time(time), status("Pending") {}

string   Appointment::getApptId()  const { return appt_id; }
string   Appointment::getDate()    const { return date; }
string   Appointment::getTime()    const { return time; }
string   Appointment::getStatus()  const { return status; }
Doctor*  Appointment::getDoctor()  const { return doctor; }
Patient* Appointment::getPatient() const { return patient; }

// ----------------------------------------------------------
void Appointment::confirm() {
    status = "Confirmed";
    cout << "  [OK] Appointment " << appt_id << " CONFIRMED.\n";
}

// ----------------------------------------------------------
void Appointment::cancel() {
    status = "Cancelled";
    cout << "  [OK] Appointment " << appt_id << " CANCELLED.\n";
}

// ----------------------------------------------------------
// POLYMORPHISM: fee depends on which doctor handles the appointment
float Appointment::calculate_fee() {
    return doctor->getFee();
}

// ----------------------------------------------------------
void Appointment::display() const {
    cout << "  Appt ID   : " << appt_id               << endl;
    cout << "  Patient   : " << patient->getName()     << endl;
    cout << "  Doctor    : Dr. " << doctor->getName()  << endl;
    cout << "  Date      : " << date                   << endl;
    cout << "  Time      : " << time                   << endl;
    cout << "  Status    : " << status                 << endl;
    cout << "  Fee (PKR) : " << doctor->getFee()       << endl;
}
