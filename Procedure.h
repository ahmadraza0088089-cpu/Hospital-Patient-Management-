#ifndef PROCEDURE_H
#define PROCEDURE_H

#include "Interfaces.h"
#include <string>
#include <iostream>
using namespace std;

// ============================================================
//  CLASS: Procedure  (implements Billable)
//  Represents a medical procedure with base + extra costs
// ============================================================
class Procedure : public Billable {
private:
    string proc_id;
    string name;
    float  base_cost;
    float  consumables_cost;  // extra cost (e.g. gloves, syringes)

public:
    Procedure(string proc_id, string name,
              float base_cost, float consumables_cost = 0.0f);

    // Getters
    string getProcId()  const;
    string getName()    const;

    // Billable interface method (as specified in project)
    // calculate_fee() adds consumables to base_cost
    float calculate_fee() override;

    void display() const;
};

// ---- inline implementation (small class) ----

inline Procedure::Procedure(string proc_id, string name,
                             float base_cost, float consumables_cost)
    : proc_id(proc_id), name(name),
      base_cost(base_cost), consumables_cost(consumables_cost) {}

inline string Procedure::getProcId() const { return proc_id; }
inline string Procedure::getName()   const { return name; }

inline float Procedure::calculate_fee() {
    return base_cost + consumables_cost;
}

inline void Procedure::display() const {
    cout << "  Procedure   : " << name           << endl;
    cout << "  Base Cost   : PKR " << base_cost  << endl;
    cout << "  Consumables : PKR " << consumables_cost << endl;
    cout << "  Total Fee   : PKR " << (base_cost + consumables_cost) << endl;
}

#endif
