// ============================================================
//  main.cpp — Hospital Patient Management System
//  Entry point: loads CSV data, shows menu, saves on exit
//
//  OOP Concepts Used:
//    - Inheritance     : Person -> Patient / Doctor / Staff
//    - Polymorphism    : calculate_fee() varies by service
//    - Abstraction     : Billable & Schedulable interfaces
//    - Encapsulation   : private schedule in Doctor
//    - Exception Handling: 3 custom exception classes
//    - File I/O (CSV)  : loadFromCSV() / saveToCSV()
// ============================================================

#include <iostream>
#include <string>
#include "Hospital.h"
#include "Exceptions.h"
using namespace std;

// ----------------------------------------------------------
void printBanner() {
    cout << "\n";
    cout << "  ============================================\n";
    cout << "     CITY GENERAL HOSPITAL — PAKISTAN        \n";
    cout << "        Patient Management System            \n";
    cout << "  ============================================\n";
}

// ----------------------------------------------------------
void printMenu() {
    cout << "\n  ========== MAIN MENU ===========\n";
    cout << "  [1]  Register New Patient\n";
    cout << "  [2]  Add Doctor\n";
    cout << "  [3]  Book Appointment\n";
    cout << "  [4]  View All Patients\n";
    cout << "  [5]  View All Doctors\n";
    cout << "  [6]  View All Appointments\n";
    cout << "  [7]  Add Medical Record\n";
    cout << "  [8]  View Patient History\n";
    cout << "  [9]  Create & View Bill\n";
    cout << "  [10] Search by Blood Group\n";
    cout << "  [11] Search Patient by Name\n";
    cout << "  [12] Discharge Patient\n";
    cout << "  [13] Doctor's Schedule\n";
    cout << "  [14] Add Staff Member\n";
    cout << "  [15] View All Staff\n";
    cout << "  [16] Daily Report\n";
    cout << "  [0]  Exit (saves data)\n";
    cout << "  =================================\n";
    cout << "  Choice: ";
}

// ----------------------------------------------------------
int main() {
    printBanner();

    Hospital hospital("City General Hospital");

    // Load previous session data on startup
    cout << "\n  Loading saved data...\n";
    hospital.loadFromCSV();

    int choice;
    do {
        printMenu();
        cin >> choice;

        try {
            switch (choice) {

            case 1:
                hospital.register_patient();
                break;

            case 2:
                hospital.addDoctor();
                break;

            case 3:
                hospital.book_appointment();
                break;

            case 4:
                hospital.viewAllPatients();
                break;

            case 5:
                hospital.viewDoctors();
                break;

            case 6:
                hospital.viewAllAppointments();
                break;

            case 7:
                hospital.addMedicalRecord();
                break;

            case 8: {
                string pid;
                hospital.viewAllPatients();
                cout << "  Patient ID: "; cin >> pid;
                Patient* p = hospital.findPatientById(pid);
                if (p) p->get_history();
                else   throw PatientNotFoundError("Patient not found: " + pid);
                break;
            }

            case 9:
                hospital.createBill();
                break;

            case 10: {
                string bg;
                cout << "  Blood Group (e.g. A+): "; cin >> bg;
                hospital.searchByBloodGroup(bg);
                break;
            }

            case 11: {
                string name;
                cin.ignore();
                cout << "  Patient Name: "; getline(cin, name);
                Patient* p = hospital.findPatientByName(name);
                if (p) p->display_info();
                else   cout << "  [!] Patient not found.\n";
                break;
            }

            case 12: {
                string pid;
                hospital.viewAllPatients();
                cout << "  Patient ID to discharge: "; cin >> pid;
                hospital.discharge(pid);
                break;
            }

            case 13: {
                string did;
                hospital.viewDoctors();
                cout << "  Doctor ID: "; cin >> did;
                Doctor* d = hospital.findDoctorById(did);
                if (d) d->get_appointments();
                else   cout << "  [!] Doctor not found.\n";
                break;
            }

            case 14:
                hospital.addStaff();
                break;

            case 15:
                hospital.viewStaff();
                break;

            case 16:
                hospital.daily_report();
                break;

            case 0:
                cout << "\n  Saving data before exit...\n";
                hospital.saveToCSV();
                cout << "  Goodbye! Stay healthy.\n\n";
                break;

            default:
                cout << "  [!] Invalid choice. Please try again.\n";
            }
        }
        // Catch all custom exceptions and print friendly messages
        catch (AppointmentConflictError& e) {
            cout << "\n  [CONFLICT ERROR] " << e.what() << "\n";
        }
        catch (PatientNotFoundError& e) {
            cout << "\n  [NOT FOUND ERROR] " << e.what() << "\n";
        }
        catch (InvalidSlotError& e) {
            cout << "\n  [INVALID SLOT] " << e.what() << "\n";
        }
        catch (exception& e) {
            cout << "\n  [ERROR] " << e.what() << "\n";
        }

    } while (choice != 0);

    return 0;
}
