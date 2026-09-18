#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
using namespace std;

// ============================================================
//  CUSTOM EXCEPTIONS  (as specified in project document)
// ============================================================

// Thrown when a doctor slot is already booked
class AppointmentConflictError : public exception {
    string msg;
public:
    AppointmentConflictError(string m) : msg(m) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

// Thrown when a patient ID is not found in the system
class PatientNotFoundError : public exception {
    string msg;
public:
    PatientNotFoundError(string m) : msg(m) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

// Thrown when a time slot is outside working hours (09:00-17:00)
class InvalidSlotError : public exception {
    string msg;
public:
    InvalidSlotError(string m) : msg(m) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

#endif
