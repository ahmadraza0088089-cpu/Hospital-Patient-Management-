#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Patient.h"
#include "Doctor.h"
#include "Staff.h"
#include "Appointment.h"
#include "Bill.h"
#include "Exceptions.h"
#include <vector>
#include <string>
using namespace std;

// ============================================================
//  CLASS: Hospital  (Master / Controller class)
//  Manages all patients, doctors, appointments
//  Handles CSV file I/O for data persistence
// ============================================================
class Hospital {
private:
    string hospitalName;

    // "patients[], doctors[], appointments[]" from project spec
    vector<Patient>     patients;
    vector<Doctor>      doctors;
    vector<Appointment> appointments;
    vector<Bill>        bills;
    vector<Staff>       staff;

    // ID counters for auto-generating IDs
    int patientCounter;
    int appointmentCounter;
    int billCounter;
    int staffCounter;

    // Helper: generate next ID string
    string nextPatientId();
    string nextApptId();
    string nextBillId();
    string nextStaffId();

public:
    Hospital(string name);

    // ------- Core Methods (as specified in project) -------
    void register_patient();
    void book_appointment();
    void discharge(string patient_id);
    void daily_report() const;

    // ------- Search Methods -------
    Patient* findPatientById(const string& id);
    Patient* findPatientByName(const string& name);
    void     searchByBloodGroup(const string& bg) const;

    // ------- Doctor Management -------
    void addDoctor();
    void viewDoctors()   const;
    Doctor* findDoctorById(const string& id);

    // ------- Medical Records -------
    void addMedicalRecord();

    // ------- Billing -------
    void createBill();
    void viewBill(const string& bill_id);

    // ------- Staff -------
    void addStaff();
    void viewStaff() const;

    // ------- CSV File I/O (persistence) -------
    void saveToCSV()    const;   // called on exit
    void loadFromCSV();          // called on startup

    // ------- Display helpers -------
    void viewAllPatients()     const;
    void viewAllAppointments() const;
};

#endif
