#include "Bill.h"
#include <iostream>
#include <iomanip>

Bill::Bill(string bill_id, Patient* patient)
    : bill_id(bill_id), patient(patient), total(0.0f), paid(false) {}

// ----------------------------------------------------------
void Bill::add_item(string desc, float cost) {
    items.push_back({desc, cost});
    total += cost;
}

// ----------------------------------------------------------
void Bill::generate_invoice() const {
    cout << "\n";
    cout << "  ============================================\n";
    cout << "       CITY GENERAL HOSPITAL — INVOICE        \n";
    cout << "  ============================================\n";
    cout << "  Bill ID  : " << bill_id               << "\n";
    cout << "  Patient  : " << patient->getName()    << "\n";
    cout << "  ID       : " << patient->getPatientId() << "\n";
    cout << "  --------------------------------------------\n";
    cout << left << setw(28) << "  Description"
         << right << setw(10) << "Amount (PKR)" << "\n";
    cout << "  --------------------------------------------\n";
    for (const BillItem& item : items) {
        cout << left << setw(28) << ("  " + item.description)
             << right << setw(10) << fixed << setprecision(2)
             << item.cost << "\n";
    }
    cout << "  --------------------------------------------\n";
    cout << left << setw(28) << "  TOTAL"
         << right << setw(10) << fixed << setprecision(2)
         << total << "\n";
    cout << "  Status   : " << (paid ? "PAID" : "UNPAID") << "\n";
    cout << "  ============================================\n";
}

// ----------------------------------------------------------
void Bill::mark_paid() {
    paid = true;
    cout << "  [OK] Bill " << bill_id << " marked as PAID. "
         << "Total: PKR " << fixed << setprecision(2) << total << "\n";
}

float Bill::getTotal() const { return total; }
bool  Bill::isPaid()   const { return paid; }
