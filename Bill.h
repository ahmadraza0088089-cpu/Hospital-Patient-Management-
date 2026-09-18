#ifndef BILL_H
#define BILL_H

#include "Patient.h"
#include <vector>
#include <string>
using namespace std;

// ============================================================
//  CLASS: Bill
//  Itemised invoice for a patient (consultation + procedures)
// ============================================================

// One line item on a bill
struct BillItem {
    string description;
    float  cost;
};

class Bill {
private:
    string         bill_id;
    Patient*       patient;
    vector<BillItem> items;   // "items[]" from project spec
    float          total;
    bool           paid;

public:
    Bill(string bill_id, Patient* patient);

    // Methods (as specified in project)
    void  add_item(string desc, float cost);
    void  generate_invoice() const;
    void  mark_paid();

    float getTotal()  const;
    bool  isPaid()    const;
};

#endif
