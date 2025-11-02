#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Patient{
    string firstName, middleName, lastName;
    int age, patientId, phoneNum;
    double billingAmount;
};

struct Diagnosis{
    int patientId;
    string diagnosis;
};

struct Schedule {
    int patientId;
    string docId;
    string date, time;
};

vector<Patient> listOfPatients;
vector<Diagnosis> diagnosises;
vector<Schedule> appointments;

void loadDiagnosis() {
    ifstream file("diagnosises.txt");
    Diagnosis d;
    while (file >> d.patientId >> d.diagnosis){
        diagnosises.push_back(d);
    }
    file.close();
}

void loadAppointments() {
    ifstream file("appointments.txt");
    Schedule s;
    while (file >> s.patientId >> s.docId >> s.date >> s.time) {
        appointments.push_back(s);
    }
    file.close();
}

void saveAppointments() {
    ofstream file("appointments.txt");
    for (Schedule s : appointments) {
        file << s.patientId << " " << s.docId << " " << s.date << " " << s.time << endl;
    }
    file.close();
}

void loadPatients() {
    ifstream file("patients.txt");
    Patient P;
    while (file >> P.firstName >> P.middleName >> P.lastName >> P.age >> P.patientId >> P.phoneNum >> P.billingAmount) {
        listOfPatients.push_back(P);
    }
    file.close();
}

void savePatient() {
    ofstream file("patients.txt");
    for (Patient p : listOfPatients) {
        file << p.firstName << " " << p.middleName << " " << p.lastName << " " <<  p.age << " " << p.patientId << " " << p.phoneNum << " " << p.billingAmount << endl;
    }
    file.close();
}

int counter;

class Doctor {
public:
    string name, id, password;
    vector<Patient> assignedPatients;

    Doctor() {}
    Doctor(string n, string i, string p) {
        name = n;
        id = i;
        password = p;
    }

    Patient searchAssignedPatient(int id){
        for (Patient p : assignedPatients){
            if (id == p.patientId){
                return p;
            }
        }
        cout << "Patient ID " << id << " not found\n";
        return {};
    }

    void viewAppointedPatients(){
        if (assignedPatients.empty()){
            cout << "you have no patients assigned to you yet\n";
            return;
        }
        bool diagnosisFound = false;
        counter = 1;
        for (Patient p : assignedPatients){
            cout << counter << endl;
            counter++;
            cout << "Full name: " << p.firstName << " " << p.middleName << " " << p.lastName << endl;
            cout << "Age: " << p.age << endl;
            cout << "ID: " << p.patientId << endl;
            cout << "Previous diagnoses: ";
            for (Diagnosis d: diagnosises){
                if (p.patientId == d.patientId){
                    diagnosisFound = true;
                    cout << ", " << d.diagnosis;
                }
            }
            if (!diagnosisFound){
                cout << "No previous diagnosis!\n";
            }
        }

    }

    void writeDiagnosis(){
        int id;
        cout << "Enter patient ID: ";
        cin >> id;
        for (Patient p : assignedPatients){
            if (id == p.patientId){
                string diagnosis;
                cout << "Write diagnosis: ";
                cin >> diagnosis;

                ofstream file ("diagnosises.txt", ios::app);
                file << p.patientId << " " << diagnosis << endl;
                file.close();
                return;
            }
        }
        cout << "Patient ID " << id << " not found\n";
    }

    void readDiagnosis(int id){
        for (Diagnosis d : diagnosises){
            if (id == d.patientId){
                cout << d.diagnosis << endl;
                return;
            }
        }
        cout << "No diagnosis found for patient " << id << endl;
    }

    void scheduleAppointment(Doctor d) {
        Schedule s;
        cout << "Enter patient ID: ";
        cin >> s.patientId;
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> s.date;
        cout << "Enter time (HH:MM): ";
        cin >> s.time;

        appointments.push_back(s);
        saveAppointments();
        cout << "Appointment scheduled for patient " << s.patientId  << " to doctor " << d.name << endl;
    }

    void rescheduleAppointment() {
        int id;
        cout << "Enter patient ID to reschedule: ";
        cin >> id;
        for (Schedule &s : appointments) {
            if (s.patientId == id) {
                cout << "Enter new date (YYYY-MM-DD): ";
                cin >> s.date;
                cout << "Enter new time (HH:MM): ";
                cin >> s.time;
                saveAppointments();
                cout << "Appointment rescheduled!\n";
                return;
            }
        }
        cout << "No appointment found for patient " << id << endl;
    }

    void cancelAppointment() {
        int id;
        cout << "Enter patient id to cancel: ";
        cin >> id;
        for (auto it = appointments.begin(); it != appointments.end(); ++it) {
            if (it->patientId == id) {
                appointments.erase(it);
                saveAppointments();
                cout << "Appointment canceled for patient " << id << endl;
                return;
            }
        }
        cout << "No appointment found for patient " << id << endl;
    }

    void viewAppointments(Doctor d){
        bool found = false;
        counter = 1;
        for (Schedule& s: appointments) {
            if (s.docId == d.id){
                found = true;
                cout << counter << endl;
                counter++;
                cout << "Patient id: " << s.patientId << endl;
                cout << "Date and time: " << s.date << " " << s.time << endl;
            }
        }
        if (!found){
            cout << "you have 0 appointments\n";
        }
    }
};

class Receptionist {
public:
    string name, id, password;

    Receptionist() {}
    Receptionist(string n, string i, string p) : name(n), id(i), password(p) {}

    void registerPatients(Patient& pat) {
        Patient p;
        srand(time(0));
        p.patientId = rand() % 900000 + 100000;

        cout << "Enter first name: ";
        cin >> p.firstName;
        cout << "Enter middle name: ";
        cin >> p.middleName;
        cout << "Enter last name: ";
        cin >> p.lastName;
        cout << "Enter age: ";
        cin >> p.age;
        cout << "Enter phone number: ";
        cin >> p.phoneNum;

        p.billingAmount = 0.0;
        listOfPatients.push_back(p);
        savePatient();
        pat = p;

        cout << "Patient " << p.firstName << " " << p.lastName << " registered with ID " << p.patientId << endl;
    }

    void addBilling() {
        int id;
        double amount;
        cout << "Enter patient ID: ";
        cin >> id;
        cout << "Enter billing amount: ";
        cin >> amount;

        for (Patient &p : listOfPatients) {
            if (p.patientId == id) {
                p.billingAmount += amount;
                savePatient();
                cout << "Billing updated. Total: $" << p.billingAmount << endl;
                return;
            }
        }
        cout << "Patient not found!\n";
    }

    void paidBilling() {
        int id;
        double amount;
        cout << "Enter patient ID: ";
        cin >> id;
        cout << "Enter paid amount: ";
        cin >> amount;

        for (Patient &p : listOfPatients) {
            if (p.patientId == id) {
                p.billingAmount -= amount;
                savePatient();
                cout << "Billing updated. Total left to pay: $" << p.billingAmount << endl;
                return;
            }
        }
        cout << "Patient not found!\n";
    }

    void searchByID(int id, Patient& pat){
        for (Patient &p : listOfPatients){
            if (id == p.patientId){
                cout << "Patient id " << id << " details: " << endl << "----------------------------------------" << endl;
                cout << "First name: " << p.firstName << "\nMiddle name: " 
                << p.middleName << "\nLast name: " << p.lastName << "\nPatient id: " << p.patientId << "\nAge: " 
                << p.age << "\nPhone number: " << p.phoneNum << endl;
                pat = p;
                return;
            }
        }
        cout << "Patient id: " << id << " not found!\n";

    }

    void searchByPhoneNumber(int phoneNumber, Patient& pat){
        for (Patient &p : listOfPatients){
            if (phoneNumber == p.phoneNum){
                cout << "Patient id " << id << " details: " << endl <<
                 "----------------------------------------" << endl;
                cout << "First name: " << p.firstName 
                << "\nMiddle name: " << p.middleName <<
                "\nLast name: " << p.lastName << 
                "\nPatient id: " << p.patientId << 
                "\nAge: " << p.age << 
                "\nPhone number: " << p.phoneNum <<
                "\nBilling amount: "<< p.billingAmount <<  endl;
                pat = p;
                return;
            }
        }
        cout << "Patient phone number: " << phoneNumber << " not found!\n";
    }
};

class Admin {
private:
    string name = "yero", id = "admin1", password = "yero123";
    vector<Doctor> doctors;
    vector<Receptionist> receptionists;

public:
    Admin() {
        loadDoctors();
        loadReceptionists();
    }

    friend string loginUser(Admin& a, string& username);
    friend void assignPatientToDoctor(Admin& a, Doctor& doc, Patient p);
    friend void adminMenu(Admin& a);
    friend void mainMenu(Admin& a);

    void registerDoctor(string name, string id, string password) {
        for (Doctor& d : doctors) {
            if (d.id == id) {
                cout << "Doctor ID already exists!\n";
                return;
            }
        }
        doctors.push_back(Doctor(name, id, password));
        saveDoctors();
        cout << "Doctor " << name << " registered successfully\n";
    }

    void registerReceptionist(string name, string id, string password) {
        for (Receptionist& r : receptionists) {
            if (r.id == id) {
                cout << "Receptionist ID already exists!\n";
                return;
            }
        }
        receptionists.push_back(Receptionist(name, id, password));
        saveReceptionists();
        cout << "Receptionist " << name << " registered successfully\n";
    }

    void deleteDoctor(string id) {
        for (auto it = doctors.begin(); it != doctors.end(); ++it) {
            if (it->id == id) {
                cout << "Doctor " << it->name << " deleted successfully!" << endl;
                doctors.erase(it);
                saveDoctors();
                return;
            }
        }
        cout << "Doctor ID " << id << " not found!" << endl;
    }

    void deleteReceptionist(string id) {
        for (auto it = receptionists.begin(); it != receptionists.end(); ++it) {
            if (it->id == id) {
                cout << "Receptionist " << it->name << " deleted successfully!" << endl;
                receptionists.erase(it);
                saveReceptionists();
                return;
            }
        }
        cout << "Receptionist ID " << id << " not found!" << endl;
    }

    void saveDoctors() {
        ofstream file("doctors.txt");
        for (Doctor d : doctors) {
            file << d.name << " " << d.id << " " << d.password << endl;
        }
        file.close();
    }

    void loadDoctors() {
        ifstream file("doctors.txt");
        Doctor d;
        while (file >> d.name >> d.id >> d.password) {
            doctors.push_back(d);
        }
        file.close();
    }

    void saveReceptionists() {
        ofstream file("receptionists.txt");
        for (Receptionist r : receptionists) {
            file << r.name << " " << r.id << " " << r.password << endl;
        }
        file.close();
    }

    void loadReceptionists() {
        ifstream file("receptionists.txt");
        Receptionist r;
        while (file >> r.name >> r.id >> r.password) {
            receptionists.push_back(r);
        }
        file.close();
    }
};

string loginUser(Admin& a, string& username){
    string id, password;
    cout << "Enter ID: ";
    cin >> id;

    username = id;

    if (id == a.id){
        cout << "Enter password: ";
        cin >> password;
        if (password == a.password){
            cout << "Welcome Admin!\n";
            return "Admin";
        }
        cout << "Incorrect password!\n";
        return "invalid";
    }

    for (Doctor& d : a.doctors){
        if (id == d.id){
            cout << "Enter password: ";
            cin >> password;
            if (password == d.password){
                cout << "Welcome Dr. " << d.name << "!\n";
                return "Doctor";
            }
            cout << "Incorrect password!\n";
            return "invalid";
        }
    }

    for (Receptionist& r : a.receptionists){
        if (id == r.id){
            cout << "Enter password: ";
            cin >> password;
            if (password == r.password){
                cout << "Welcome " << r.name << "!\n";
                return "Receptionist";
            }
            cout << "Incorrect password!\n";
            return "invalid";
        }
    }

    cout << "ID not found!\n";
    return "invalid";
}

void assignPatientToDoctor(Admin& a, Doctor &doc, Patient p) {
    bool docFound = false;
    for (Doctor d: a.doctors){
        if (d.assignedPatients.size() <= 5){
            docFound = true;
            doc = d;
        }
    }
    if (docFound){
        doc.assignedPatients.push_back(p);
        cout << "patient id " << p.patientId << " assigned to doctor id " << doc.id << endl;
    }
    else
        cout << "there are no available doctors at this moment!\n";
}

void adminMenu(Admin& a);
void mainMenu(Admin& a);
void receptionistMenu();
void doctorMenu();



void adminMenu(Admin& a){
    int choice;
    cout << "0: Go back\n";
    cout << "1: Register a doctor\n";
    cout << "2: Register a receptionist\n";
    cout << "3: Delete a doctor\n";
    cout << "4: Delete a receptionist\n";
    cout << "Enter choice: ";
    cin >> choice;

    string name;
    string id;
    string password;

    switch(choice){
        case 0: 
            mainMenu(a);
            break;
        case 1:
            cout << "Enter doctor name to be registered: ";
            cin >> name;
            cout << "Enter ID to be registered: ";
            cin >> id;
            cout << "Enter doctor's password: ";
            cin >> password;
            
            a.registerDoctor(name, id, password);
            adminMenu(a);
            break;
        case 2:
            cout << "Enter receptionist name to be registered: ";
            cin >> name;
            cout << "Enter ID to be registered: ";
            cin >> id;
            cout << "Enter receptionist's password: ";
            cin >> password;

            a.registerReceptionist(name, id, password);
            adminMenu(a);
            break;
        case 3:
            cout << "Enter doctor id to be deleted: ";
            cin >> id;

            a.deleteDoctor(id);
            adminMenu(a);
            break;
        case 4:
            cout << "Enter receptionist id to be deleted: ";
            cin >> id;

            a.deleteReceptionist(id);
            adminMenu(a);
            break;
        default:
            cout << "Invalid input, try again\n";
            adminMenu(a);
            break;
    }
}

void receptionistMenu(Admin a, Receptionist& r){
    cout << "logged in as receptionist " << r.name << endl;

    int choice;
    cout << "0: Go back\n";
    cout << "1: Register a patient\n";
    cout << "2: Search for patient and assign to doctor\n";
    cout << "3: Billing for patient\n";
    cout << "Enter choice: ";
    cin >> choice;

    Doctor doc;
    Patient pat;
    int ch;
    int id;
    int phoneNumber;

    switch(choice){
        case 0:
            mainMenu(a);
            break;
        case 1:
            r.registerPatients(pat);
            assignPatientToDoctor(a, doc, pat);
            receptionistMenu(a, r);
            break;
        case 2:
            cout << "0: Go back\n";
            cout << "1: search by id\n";
            cout << "2: search by phone number\n";
            cout << "Enter choice: ";
            cin >> ch;

            switch(ch){
                case 0:
                    receptionistMenu(a, r);
                    break;
                case 1:
                    cout << "Enter ID: ";
                    cin >> id;
                    r.searchByID(id, pat);
                    assignPatientToDoctor(a, doc, pat);
                    receptionistMenu(a, r);
                    break;
                case 2:
                    cout << "Enter phone number: ";
                    cin >> phoneNumber;
                    r.searchByPhoneNumber(phoneNumber, pat);
                    assignPatientToDoctor(a, doc, pat);
                    receptionistMenu(a, r);
                    break;
                default:
                    cout << "Invalid input!\n";
                    receptionistMenu(a, r);
                    break;       
            }
            break;
        case 3:
            cout << "0: Go back\n";
            cout << "1: Add bill\n";
            cout << "2: Paid bill\n";
            cout << "Enter choice: ";
            cin >> ch;

            switch(ch){
                case 0:
                    receptionistMenu(a, r);
                    break;
                case 1:
                    r.addBilling();
                    receptionistMenu(a, r);
                    break;
                case 2:
                    r.paidBilling();
                    receptionistMenu(a, r);
                    break;
                default:
                    cout << "Invalid input!\n";
                    receptionistMenu(a, r);
                    break; 
            }
            break;
        default:
            cout << "Invalid input, try again!\n";
            receptionistMenu(a, r);
            break;
              
    }

}

void doctorMenu(Admin a, Doctor& d){
    cout << "logged in as Doctor " << d.name << endl;

    int choice;
    cout << "0: Go back\n";
    cout << "1: Patient details\n";
    cout << "2: Appointments\n";
    cout << "Enter choice: ";
    cin >> choice;

    int ch;

    switch(choice){
        case 0:
            mainMenu(a);
            break;
        case 1:
            cout << "0: Go back\n";
            cout << "1: view appointed patients' information\n";
            cout << "2: write diagnosis for patient\n";
            cout << "Enter choice: ";
            cin >> ch;

            switch(ch){
                case 0:
                    doctorMenu(a, d);
                    break;
                case 1:
                    d.viewAppointedPatients();
                    doctorMenu(a, d);
                    break;
                case 2:
                    d.writeDiagnosis();
                    doctorMenu(a, d);
                    break;
                default:
                    cout << "invalid input!\n";
                    doctorMenu(a, d);
                    break;
            }
            break;
        case 2:
            cout << "0: Go back\n";
            cout << "1: Schedule appointment\n";
            cout << "2: Reschedule appointment\n";
            cout << "3: Cancel appointment\n";
            cout << "4: view your appointmens\n";
            cout << "Enter choice: ";
            cin >> ch;
    
            switch(ch){
                case 0:
                    doctorMenu(a, d);
                    break;
                case 1:
                    d.scheduleAppointment(d);
                    doctorMenu(a, d);
                    break;
                case 2:
                    d.rescheduleAppointment();
                    doctorMenu(a, d);
                    break;
                case 3:
                    d.cancelAppointment();
                    doctorMenu(a, d);
                    break;
                case 4:
                    d.viewAppointments(d);
                    doctorMenu(a, d);
                    break;
                default:
                    cout << "invalid input!\n";
                    doctorMenu(a, d);
                    break;
            }
            break;
        
    }

}

void mainMenu(Admin& a){
    //bool terminate = false;
    int choice;
    cout << "Hello there, press the number of choice\n";
    cout << "0: Terminate program\n";
    cout << "1: Login\n";
    cout << "Enter choice: ";
    cin >> choice;

    string loginType;
    string id;
    Receptionist r;
    Doctor d;
    
    switch(choice){
        case 0:
            return;
            break;
        case 1:
            loginType = loginUser(a, id);
            if (loginType == "Admin"){
                adminMenu(a);
            }

            else if (loginType == "Receptionist"){
                for (Receptionist& rec: a.receptionists){
                    if (id == rec.id){
                        r = rec;
                    }
                }
                receptionistMenu(a, r);
            }

            else if (loginType == "Doctor"){
                for (Doctor& doc: a.doctors){
                    if (id == doc.id){
                        d = doc;
                    }
                }
                doctorMenu(a, d);
            }

            else if (loginType == "invalid"){
                mainMenu(a);
            }

            break;
        default:
            cout << "Invalid input, try again\n";
            mainMenu(a);
            break;
    }
    
}


int main() {
    loadPatients();
    loadDiagnosis();
    loadAppointments();
    Admin admin;

    mainMenu(admin);
    return 0;
}
