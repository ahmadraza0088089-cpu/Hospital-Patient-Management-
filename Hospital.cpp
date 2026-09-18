#include "Hospital.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// ============================================================
Hospital::Hospital(string name)
    : hospitalName(name),
      patientCounter(1), appointmentCounter(1),
      billCounter(1), staffCounter(1) {}

// ---- ID generators ----
string Hospital::nextPatientId()  { return "P" + to_string(patientCounter++); }
string Hospital::nextApptId()     { return "A" + to_string(appointmentCounter++); }
string Hospital::nextBillId()     { return "B" + to_string(billCounter++); }
string Hospital::nextStaffId()    { return "S" + to_string(staffCounter++); }

// ============================================================
//  REGISTER PATIENT  (as specified in project)
// ============================================================
void Hospital::register_patient() {
    string name, dob, cnic, contact, address, blood;

    cout << "\n  --- Register New Patient ---\n";
    cout << "  Name       : "; cin.ignore(); getline(cin, name);
    cout << "  DOB (DD/MM/YYYY): "; getline(cin, dob);
    cout << "  CNIC       : "; getline(cin, cnic);
    cout << "  Contact    : "; getline(cin, contact);
    cout << "  Address    : "; getline(cin, address);
    cout << "  Blood Group: "; getline(cin, blood);

    string pid = nextPatientId();
    patients.push_back(Patient(pid, name, dob, cnic,
                                contact, address, blood));
    cout << "  [OK] Patient registered. ID = " << pid << "\n";
}

// ============================================================
//  ADD DOCTOR
// ============================================================
void Hospital::addDoctor() {
    string name, dob, cnic, contact, address, spec;
    float fee;

    cout << "\n  --- Add New Doctor ---\n";
    cout << "  Name        : "; cin.ignore(); getline(cin, name);
    cout << "  DOB (DD/MM/YYYY): "; getline(cin, dob);
    cout << "  CNIC        : "; getline(cin, cnic);
    cout << "  Contact     : "; getline(cin, contact);
    cout << "  Address     : "; getline(cin, address);
    cout << "  Speciality  : "; getline(cin, spec);
    cout << "  Fee (PKR)   : "; cin >> fee;

    // Generate doctor ID
    string did = "D" + to_string(doctors.size() + 1);
    doctors.push_back(Doctor(did, name, dob, cnic,
                              contact, address, spec, fee));
    cout << "  [OK] Doctor added. ID = " << did << "\n";
}

// ============================================================
//  BOOK APPOINTMENT  (with conflict detection, as specified)
// ============================================================
void Hospital::book_appointment() {
    string pid, did, date, time;

    cout << "\n  --- Book Appointment ---\n";
    viewAllPatients();
    cout << "  Patient ID  : "; cin >> pid;
    viewDoctors();
    cout << "  Doctor ID   : "; cin >> did;
    cout << "  Date (DD/MM/YYYY): "; cin >> date;
    cout << "  Time (HH:MM): "; cin >> time;

    Patient* pat = findPatientById(pid);
    Doctor*  doc = findDoctorById(did);

    if (!pat) {
        throw PatientNotFoundError("Patient ID '" + pid + "' not found.");
    }
    if (!doc) {
        cout << "  [ERROR] Doctor ID '" << did << "' not found.\n";
        return;
    }

    // book_slot throws AppointmentConflictError or InvalidSlotError
    doc->book_slot(date, time);

    string aid = nextApptId();
    appointments.push_back(Appointment(aid, pat, doc, date, time));
    appointments.back().confirm();
    cout << "  [OK] Appointment booked. ID = " << aid << "\n";
}

// ============================================================
//  DISCHARGE PATIENT
// ============================================================
void Hospital::discharge(string patient_id) {
    Patient* p = findPatientById(patient_id);
    if (!p) throw PatientNotFoundError(
        "Cannot discharge: Patient '" + patient_id + "' not found.");
    cout << "  [OK] Patient " << p->getName()
         << " (" << patient_id << ") has been discharged.\n";
}

// ============================================================
//  DAILY REPORT  (as specified in project)
// ============================================================
void Hospital::daily_report() const {
    float totalRevenue = 0;
    int   confirmedCount = 0;

    for (const Appointment& a : appointments) {
        if (a.getStatus() == "Confirmed") {
            confirmedCount++;
            totalRevenue += a.getDoctor()->getFee();
        }
    }

    cout << "\n  ============================================\n";
    cout << "       DAILY REPORT — " << hospitalName        << "\n";
    cout << "  ============================================\n";
    cout << "  Total Patients     : " << patients.size()     << "\n";
    cout << "  Total Doctors      : " << doctors.size()      << "\n";
    cout << "  Appointments Today : " << confirmedCount       << "\n";
    cout << "  Revenue Collected  : PKR "
         << fixed << setprecision(2) << totalRevenue         << "\n";
    cout << "  ============================================\n";
}

// ============================================================
//  ADD MEDICAL RECORD
// ============================================================
void Hospital::addMedicalRecord() {
    string pid, did, diagnosis, prescription, date;

    cout << "\n  --- Add Medical Record ---\n";
    viewAllPatients();
    cout << "  Patient ID   : "; cin >> pid;
    viewDoctors();
    cout << "  Doctor ID    : "; cin >> did;
    cout << "  Date (DD/MM/YYYY): "; cin >> date;
    cin.ignore();
    cout << "  Diagnosis    : "; getline(cin, diagnosis);
    cout << "  Prescription : "; getline(cin, prescription);

    Patient* pat = findPatientById(pid);
    Doctor*  doc = findDoctorById(did);

    if (!pat) throw PatientNotFoundError("Patient not found: " + pid);
    if (!doc) { cout << "  [ERROR] Doctor not found.\n"; return; }

    string rid = "R" + to_string(pat->getPatientId().back())
                     + to_string(rand() % 1000);
    MedicalRecord rec(rid, pat->getName(), doc->getName(),
                      diagnosis, prescription, date);
    pat->add_record(rec);
    rec.export_to_file();
}

// ============================================================
//  CREATE BILL
// ============================================================
void Hospital::createBill() {
    string pid;
    cout << "\n  --- Create Bill ---\n";
    viewAllPatients();
    cout << "  Patient ID: "; cin >> pid;

    Patient* pat = findPatientById(pid);
    if (!pat) throw PatientNotFoundError("Patient not found: " + pid);

    string bid = nextBillId();
    bills.push_back(Bill(bid, pat));
    Bill& bill = bills.back();

    // Add consultation fee from appointments
    for (Appointment& a : appointments) {
        if (a.getPatient()->getPatientId() == pid
            && a.getStatus() == "Confirmed") {
            bill.add_item("Consultation - Dr. " + a.getDoctor()->getName(),
                          a.calculate_fee());
        }
    }

    // Allow adding extra procedures
    char more;
    do {
        string desc; float cost;
        cout << "  Add procedure? (desc + cost): ";
        cin.ignore(); getline(cin, desc);
        cout << "  Cost (PKR): "; cin >> cost;
        bill.add_item(desc, cost);
        cout << "  Add another item? (y/n): "; cin >> more;
    } while (more == 'y' || more == 'Y');

    bill.generate_invoice();

    char pay;
    cout << "\n  Mark as paid now? (y/n): "; cin >> pay;
    if (pay == 'y' || pay == 'Y') bill.mark_paid();
}

// ============================================================
//  ADD STAFF
// ============================================================
void Hospital::addStaff() {
    string name, dob, cnic, contact, address, dept, role, shift;

    cout << "\n  --- Add Staff Member ---\n";
    cout << "  Name       : "; cin.ignore(); getline(cin, name);
    cout << "  DOB        : "; getline(cin, dob);
    cout << "  CNIC       : "; getline(cin, cnic);
    cout << "  Contact    : "; getline(cin, contact);
    cout << "  Address    : "; getline(cin, address);
    cout << "  Department : "; getline(cin, dept);
    cout << "  Role       : "; getline(cin, role);
    cout << "  Shift      : "; getline(cin, shift);

    string sid = nextStaffId();
    staff.push_back(Staff(sid, name, dob, cnic,
                           contact, address, dept, role, shift));
    cout << "  [OK] Staff member added. ID = " << sid << "\n";
}

// ============================================================
//  SEARCH METHODS
// ============================================================
Patient* Hospital::findPatientById(const string& id) {
    for (Patient& p : patients)
        if (p.getPatientId() == id) return &p;
    return nullptr;
}

Patient* Hospital::findPatientByName(const string& name) {
    for (Patient& p : patients)
        if (p.getName() == name) return &p;
    return nullptr;
}

void Hospital::searchByBloodGroup(const string& bg) const {
    cout << "\n  --- Patients with Blood Group: " << bg << " ---\n";
    bool found = false;
    for (const Patient& p : patients) {
        if (p.getBloodGroup() == bg) {
            p.display_info();
            cout << "  ----\n";
            found = true;
        }
    }
    if (!found) cout << "  (No patients found)\n";
}

Doctor* Hospital::findDoctorById(const string& id) {
    for (Doctor& d : doctors)
        if (d.getDoctorId() == id) return &d;
    return nullptr;
}

// ============================================================
//  VIEW HELPERS
// ============================================================
void Hospital::viewAllPatients() const {
    cout << "\n  --- Registered Patients ---\n";
    if (patients.empty()) { cout << "  (None)\n"; return; }
    for (const Patient& p : patients)
        cout << "  [" << p.getPatientId() << "] "
             << p.getName() << " | " << p.getBloodGroup() << "\n";
}

void Hospital::viewDoctors() const {
    cout << "\n  --- Available Doctors ---\n";
    if (doctors.empty()) { cout << "  (None)\n"; return; }
    for (const Doctor& d : doctors)
        cout << "  [" << d.getDoctorId() << "] Dr. "
             << d.getName() << " | " << d.getSpeciality()
             << " | PKR " << d.getFee() << "\n";
}

void Hospital::viewAllAppointments() const {
    cout << "\n  --- All Appointments ---\n";
    if (appointments.empty()) { cout << "  (None)\n"; return; }
    for (const Appointment& a : appointments) {
        a.display();
        cout << "  ----\n";
    }
}

void Hospital::viewStaff() const {
    cout << "\n  --- Staff Members ---\n";
    if (staff.empty()) { cout << "  (None)\n"; return; }
    for (const Staff& s : staff)
        s.display_info();
}

// ============================================================
//  CSV FILE I/O  — saveToCSV() called on exit
// ============================================================
void Hospital::saveToCSV() const {
    // --- patients.csv ---
    ofstream pf("patients.csv");
    pf << "patient_id,name,dob,cnic,contact,address,blood_group\n";
    for (const Patient& p : patients) {
        pf << p.getPatientId() << ","
           << p.getName()      << ","
           << p.getBloodGroup() << "\n";
    }
    pf.close();

    // --- appointments.csv ---
    ofstream af("appointments.csv");
    af << "appt_id,patient_id,patient_name,doctor_id,doctor_name,"
          "date,time,status,fee\n";
    for (const Appointment& a : appointments) {
        af << a.getApptId()                    << ","
           << a.getPatient()->getPatientId()   << ","
           << a.getPatient()->getName()        << ","
           << a.getDoctor()->getDoctorId()     << ","
           << a.getDoctor()->getName()         << ","
           << a.getDate()                      << ","
           << a.getTime()                      << ","
           << a.getStatus()                    << ","
           << a.getDoctor()->getFee()          << "\n";
    }
    af.close();

    cout << "\n  [OK] Data saved to patients.csv and appointments.csv\n";
}

// ============================================================
//  loadFromCSV() — called on startup
// ============================================================
void Hospital::loadFromCSV() {
    // --- Load patients.csv ---
    ifstream pf("patients.csv");
    if (pf.is_open()) {
        string line;
        getline(pf, line); // skip header
        while (getline(pf, line)) {
            stringstream ss(line);
            string pid, name, blood;
            getline(ss, pid,   ',');
            getline(ss, name,  ',');
            getline(ss, blood, ',');
            if (!pid.empty() && !name.empty()) {
                patients.push_back(Patient(pid, name,
                    "01/01/2000", "00000-0000000-0",
                    "N/A", "N/A", blood));
                patientCounter++;
            }
        }
        pf.close();
        cout << "  [OK] Loaded " << patients.size()
             << " patient(s) from patients.csv\n";
    }
}
