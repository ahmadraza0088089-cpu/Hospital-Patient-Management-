#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include "MedicalRecord.h"
#include <vector>
using namespace std;

// ============================================================
//  CLASS: Patient  (inherits Person)
//  Stores patient records and generates bill summary
// ============================================================
class Patient : public Person {
private:
    string blood_group;
    vector<MedicalRecord> records;  // "records[]" from project spec

public:
    string patient_id;   // e.g., "P001"

    Patient(string patient_id, string name, string DOB,
            string CNIC, string contact, string address,
            string blood_group);

    // Getters
    string getPatientId()   const;
    string getBloodGroup()  const;

    // Methods (as specified in project)
    void add_record(const MedicalRecord& rec);
    void get_history()  const;   // prints all medical records
    void get_bill()     const;   // prints all bill items (placeholder)
    void display_info() const;   // overrides Person::display_info
};

#endif
