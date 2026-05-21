#include <iostream>
#include <string>
using namespace std;

// Struct that holds patient information
struct Patient { 
    int order;
    string fullname;
    int age;
    char gender;
    string medical_flag;
    string complaint;
    string triage;
    Patient* next; 
};

// Function declaring
string assignTriage(string complaint);
bool comparePatients(Patient* p1, Patient* p2);

Patient* head = nullptr;
int counter = 0;

// Function that adds new patient to the list
void addPatient() {
    Patient* newPatient = new Patient;
    newPatient->order = counter++;

    cout << "Full name: ";
    cin >> newPatient->fullname;

    cout << "Age: ";
    cin >> newPatient->age;

    cout << "Sex (M/F): ";
    cin >> newPatient->gender;

    cout << "Medical flag (cancer/disabled/pregnant/none): ";
    cin >> newPatient->medical_flag;

    cout << "Complaint (headache, fever, fracture, abdominal pain, injury, vomiting, chest pain, burn, severe trauma, dizziness): ";
    cin >> newPatient->complaint;

    newPatient->triage = assignTriage(newPatient->complaint);
    newPatient->next = nullptr;

    // Inserting to linked list
    if (!head || comparePatients(newPatient, head)) {
        newPatient->next = head;
        head = newPatient;
    }
    else {
        Patient* current = head;
        while (current->next && !comparePatients(newPatient, current->next)) {
            current = current->next;
        }
        newPatient->next = current->next;
        current->next = newPatient;
    }
    cout << "Patient added with triage: " << newPatient->triage << endl;
}

// Assigning triage levels compared to situation
string assignTriage(string complaint) {
    if (complaint == "chest pain" || complaint == "severe trauma")
        return "RED";
    else if (complaint == "fever" || complaint == "fracture" || complaint == "abdominal pain")
        return "YELLOW";
    else
        return "GREEN";
}

// Assigning triage levels to nnumber format that we can use
int triagePriority(string triage) {
    if (triage == "RED") 
        return 3;
    else if (triage == "YELLOW") 
        return 2;
    else
    return 1; // GREEN
}

// Compare the priorities between patients according to their triage levels, ages, genders and orders
bool comparePatients(Patient* p1, Patient* p2) {
    int t1 = triagePriority(p1->triage);
    int t2 = triagePriority(p2->triage);
    if (t1 != t2) return t1 > t2;

    if (p1->age != p2->age) return p1->age > p2->age;

    if (p1->gender != p2->gender) return p1->gender == 'F';

    return p1->order < p2->order;
}

// Lists the requested patient information
void servePatient() {
    if (head == nullptr) {
        cout << "No patients to display!" <<endl;
        return;
    }

    Patient* sıradaki = head;
    head = head->next;

    cout << "Next Patient:";
    cout << "Full Name: " << sıradaki->fullname << endl;
    cout << "Age: " << sıradaki->age << endl;
    cout << "Gender: " << sıradaki->gender << endl;
    cout << "Medical Flag: " << sıradaki->medical_flag << endl;
    cout << "Complaint: " << sıradaki->complaint << endl;
    cout << "Triage: " << sıradaki->triage << endl;

    delete sıradaki;
}

// Lists the each patient in the list
void printQueue() {
    if (head == nullptr) {
        cout << "No patients to display!" << endl;
        return;
    }

    cout << "\n- Patients -\n";
    Patient* temp = head;
    int i = 0;
    while (temp != nullptr) {
        cout << i++ << ". Patient:\n" << temp->fullname<< ", " << temp->triage << ", " << temp->age << ", " << temp->gender << endl;
        temp = temp->next;
    }
}

int main()
{
    int choice;
    while (true) {
        cout << "-------  OPERATIONS  -------" << endl;
        cout << "1- Adding new patient" << endl;
        cout << "2- Serving patients" << endl;
        cout << "3- Show all the patients" << endl;
        cout << "4- Exit\n" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addPatient();
            break;
        case 2:
            servePatient();
            break;
        case 3: 
            printQueue();
            break;
        case 4:
            cout << "Exiting...";
            return 0;
        default: 
            cout << "Please enter a valid chice!";
            break;
        }
    }
}

