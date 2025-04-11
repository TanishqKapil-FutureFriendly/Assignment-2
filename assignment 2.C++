#include <iostream>
#include <vector>
using namespace std;

class Learner {
private:
    string fullName;
    int idNumber;
    float gradePoint;
    vector<string> enrolledSubjects;

public:
    Learner() : fullName(""), idNumber(0), gradePoint(0.0f) {}

    Learner(string name, int id, float gpa)
        : fullName(name), idNumber(id), gradePoint(gpa) {}

    Learner(const Learner &l) {
        fullName = l.fullName;
        idNumber = l.idNumber;
        gradePoint = l.gradePoint;
        enrolledSubjects = l.enrolledSubjects;
    }

    void enrollSubject(const string &subject) {
        enrolledSubjects.push_back(subject);
    }

    void modifyGPA(float updatedGPA) {
        if (updatedGPA >= 0.0 && updatedGPA <= 10.0)
            gradePoint = updatedGPA;
        else
            cout << "GPA entered is out of range." << endl;
    }

    void showDetails() const {
        cout << "\n--- Learner Profile ---\n";
        cout << "Name: " << fullName << "\n";
        cout << "ID: " << idNumber << "\n";
        cout << "GPA: " << gradePoint << "\n";
        cout << "Enrolled Subjects: ";
        for (const string &sub : enrolledSubjects)
            cout << sub << " ";
        cout << "\n";
    }

    int getID() const {
        return idNumber;
    }
};

class RecordSystem {
private:
    vector<Learner> records;

public:
    void registerLearner(const Learner &l) {
        records.push_back(l);
    }

    void lookupLearner(int id) const {
        for (const auto &l : records) {
            if (l.getID() == id) {
                l.showDetails();
                return;
            }
        }
        cout << "No learner found with that ID.\n";
    }

    void listAllLearners() const {
        if (records.empty()) {
            cout << "No learners have been added yet.\n";
            return;
        }
        for (const auto &l : records) {
            l.showDetails();
            cout << "----------------------\n";
        }
    }
};

int main() {
    RecordSystem database;
    int option;

    do {
        cout << "\n=== Learner Record System ===\n";
        cout << "1. Register Learner\n";
        cout << "2. View All Learners\n";
        cout << "3. Search by ID\n";
        cout << "4. Quit\n";
        cout << "Select an option: ";
        cin >> option;

        if (option == 1) {
            string name;
            int id;
            float gpa;
            int subjectCount;
            string subject;

            cout << "Enter learner's full name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter ID number: ";
            cin >> id;

            cout << "Enter GPA: ";
            cin >> gpa;

            Learner learner(name, id, gpa);

            cout << "Number of subjects to enroll: ";
            cin >> subjectCount;
            cin.ignore();

            for (int i = 0; i < subjectCount; ++i) {
                cout << "Enter subject name: ";
                getline(cin, subject);
                learner.enrollSubject(subject);
            }

            database.registerLearner(learner);
        } else if (option == 2) {
            database.listAllLearners();
        } else if (option == 3) {
            int searchID;
            cout << "Enter ID to search: ";
            cin >> searchID;
            database.lookupLearner(searchID);
        } else if (option == 4) {
            cout << "Closing system. Goodbye!\n";
        } else {
            cout << "Invalid input. Try again.\n";
        }
    } while (option != 4);

    return 0;
}

