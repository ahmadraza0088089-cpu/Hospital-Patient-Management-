# 🏥 Hospital Patient Management System

A **C++-based Hospital Patient Management System** developed as a **First-Year University Project** to apply Object-Oriented Programming concepts to a real-world healthcare management scenario.

The project focuses on organizing hospital-related entities such as patients, doctors, appointments, medical records, procedures, and billing into a structured C++ application.

---

## 📌 Project Overview

The **Hospital Patient Management System** is designed to demonstrate how a real-world hospital workflow can be represented using **Object-Oriented Programming (OOP)**.

Instead of keeping the complete application in a single source file, the project is organized into multiple classes and modules representing different hospital entities.

This project was developed during my **first year of university** as part of my programming/OOP learning journey.

---

## ✨ Main Features

### 👤 Patient Management

* Patient-related information management
* Patient identification and record handling
* Structured patient objects

### 👨‍⚕️ Doctor Management

* Doctor information management
* Doctor specialization/details
* Doctor availability and scheduling logic

### 📅 Appointment Management

* Create appointments
* Assign patients to doctors
* Store appointment date and time
* Appointment status management
* Confirm appointments
* Cancel appointments
* Check doctor availability
* Prevent invalid/conflicting bookings

### 🏥 Hospital Management

* Centralized hospital-related management
* Organized relationships between different hospital entities

### 📋 Medical Records

* Structured medical record representation
* Patient-related medical information management

### 💳 Billing & Procedures

* Procedure-related information
* Billing-related class structure
* Cost handling for hospital procedures

### ⚠️ Exception Handling

* Error handling for invalid operations
* Exception-based handling for situations such as invalid appointment operations and scheduling conflicts

---

## 🧠 Object-Oriented Programming Concepts

This project was primarily created to practice and demonstrate **C++ OOP concepts**, including:

* Classes & Objects
* Encapsulation
* Inheritance
* Polymorphism
* Constructors
* Class relationships
* Header (`.h`) and source (`.cpp`) separation
* Function overriding
* Exception handling
* Modular code organization

---

## 🗂️ Project Structure

The project is organized into separate classes/modules for better code structure.

```text
Hospital-Patient-Management/
│
├── Appointment.cpp
├── Appointment.h
│
├── Bill.cpp
├── Bill.h
│
├── Doctor.cpp
├── Doctor.h
│
├── Exception.cpp
├── Exception.h
│
├── Hospital.cpp
├── Hospital.h
│
├── Interface.h
│
├── MedicalRecord.cpp
├── MedicalRecord.h
│
├── Patient.cpp
├── Patient.h
│
├── Person.cpp
├── Person.h
│
├── Procedure.cpp
├── Procedure.h
│
├── main.cpp
│
└── Makefile
```

> File names may vary slightly depending on the current version of the repository.

---

## 🔄 Appointment Workflow

A major part of the system is the appointment module.

```text
Patient
   │
   ▼
Select Doctor
   │
   ▼
Select Date & Time
   │
   ▼
Check Doctor Availability
   │
   ├── Available ──► Book Appointment
   │
   └── Not Available ──► Reject Booking
                             
Booked Appointment
   │
   ├── Confirm
   │
   └── Cancel
```

This helps demonstrate how programming logic can be used to model real-world scheduling problems.

---

## 🛠️ Technologies Used

| Technology             | Purpose                           |
| ---------------------- | --------------------------------- |
| **C++**                | Core programming language         |
| **OOP**                | Application architecture          |
| **Visual Studio Code** | Development environment           |
| **Makefile**           | Build/project management          |
| **GitHub**             | Version control & project hosting |

---

## 🎯 Learning Objectives

This project was created with the following goals:

1. Practice C++ programming beyond basic syntax.
2. Understand Object-Oriented Programming.
3. Learn how multiple classes interact with each other.
4. Practice separating declarations and implementations.
5. Implement real-world business logic.
6. Handle errors and invalid operations.
7. Develop a structured university-level software project.

---

## 📚 What I Learned

Building this project helped me understand that software development is not only about writing code—it is also about **designing relationships between different parts of a system**.

Through this project, I gained practical experience with:

* Designing classes for real-world entities
* Connecting multiple classes
* Implementing scheduling logic
* Handling invalid operations
* Structuring C++ projects
* Debugging and testing
* Writing more organized code

---

## 🚀 Future Improvements

Possible future improvements include:

* Graphical User Interface (GUI)
* Database integration
* Secure user authentication
* Admin dashboard
* Advanced patient search
* Prescription management
* Pharmacy management
* Automated reports
* Persistent database storage
* Improved validation
* Web-based version
* REST API integration

---

## 🎓 Project Context

**Project Level:** First-Year University Project
**Language:** C++
**Focus:** Object-Oriented Programming
**Developer:** **Ahmad Khan**

This project represents one of my early steps toward building larger and more advanced software systems.

---

## 👨‍💻 Author

### Ahmad Khan

Data Science Student | C++ Developer | Software & Technology Enthusiast

GitHub:
https://github.com/ahmadraza0088089-cpu

---

## ⭐ Acknowledgment

This project was developed as part of my **first-year university programming journey** and reflects my practical learning and application of C++ Object-Oriented Programming concepts.

More advanced projects and improvements are coming. 🚀

---

## 📄 License

This project is intended primarily for **educational and learning purposes**.
