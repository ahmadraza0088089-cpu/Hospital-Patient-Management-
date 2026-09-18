#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "Interfaces.h"
#include "Patient.h"
#include "Doctor.h"
#include <string>
using namespace std;

// ============================================================
//  CLASS: Appointment  (implements Billable)
//  Links one patient to one doctor at a specific date/time
// ============================================================
class Appointment : public Billable {
private:
    string   appt_id;
    Patient* patient;   // pointer — patient registered in Hospital
    Doctor*  doctor;    // pointer — doctor registered in Hospital
    string   date;
    string   time;
    string   status;    // "Pending" / "Confirmed" / "Cancelled"

public:
    Appointment(string appt_id, Patient* patient,
                Doctor* doctor, string date, string time);

    // Getters
    string getApptId()  const;
    string getDate()    const;
    string getTime()    const;
    string getStatus()  const;
    Doctor*  getDoctor()  const;
    Patient* getPatient() const;

    // Methods (as specified in project)
    void  confirm();
    void  cancel();
    float calculate_fee() override;  // polymorphic: returns doctor->fee

    void  display() const;
};

#endif
