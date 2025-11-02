# 🏥 Hospital Management System (C++)

This is a **console-based Hospital Management System** written in **C++**, designed to simulate core hospital operations such as patient registration, diagnosis recording, appointment scheduling, and billing.  
It demonstrates **object-oriented programming concepts**, **file handling**, and **modular system design**.

---

## 📋 Features

### 👨‍⚕️ Admin
- Register or delete **Doctors** and **Receptionists**
- View and manage hospital staff credentials
- Persistent data storage using text files

### 👩‍💼 Receptionist
- Register new patients (auto-generates a patient ID)
- Search patients by **ID** or **phone number**
- Assign patients automatically to available doctors
- Manage billing (add or deduct payments)

### 🧑‍⚕️ Doctor
- View assigned patients
- Write and view **diagnoses**
- Schedule, reschedule, or cancel **appointments**

---

## 🗂️ Data Storage

All records are stored in plain text files for persistence:
| File | Description |
|------|--------------|
| `patients.txt` | Stores patient details (name, age, phone, billing info) |
| `doctors.txt` | Contains doctor credentials |
| `receptionists.txt` | Contains receptionist credentials |
| `diagnosises.txt` | Stores written diagnoses for patients |
| `appointments.txt` | Stores scheduled appointments |

---

## 🧠 Concepts Used

- **Classes and Objects** (`Doctor`, `Receptionist`, `Admin`, `Patient`)
- **Encapsulation** and **friend functions**
- **File I/O** for data persistence (`ifstream`, `ofstream`)
- **Vectors** for dynamic data storage
- **Conditional and iterative logic** for menu-driven navigation

---

## ⚙️ How to Run

### 1️⃣ Compile
Make sure you have `g++` installed, then compile using:

```bash
g++ hospital_management.cpp -o hospital_management
