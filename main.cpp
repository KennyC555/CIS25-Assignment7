
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Record {
    int id;
    string name;
};

class User {
protected:
    string username;

public:
    User(string name) : username(name) {}

    virtual void showRole() {
        cout << "User: " << username << endl;
    }
};

class RegularUser : public User {
public:
    RegularUser(string name) : User(name) {}

    void showRole() override {
        cout << "Regular User: " << username << endl;
    }
};

class Admin : public User {
public:
    Admin(string name) : User(name) {}

    void showRole() override {
        cout << "Admin: " << username << endl;
    }

    static int binarySearch(const vector<Record>& records, int id) {
        int left = 0;
        int right = static_cast<int>(records.size()) - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (records[mid].id == id) return mid;
            if (records[mid].id < id) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    void addRecord(vector<Record>& records, int id, string name) {
        if (binarySearch(records, id) != -1) {
            cout << "Record ID already exists.\n";
            return;
        }

        records.push_back({id, name});
        sort(records.begin(), records.end(),
             [](const Record& a, const Record& b) {
                 return a.id < b.id;
             });

        cout << "Record added successfully.\n";
    }

    void deleteRecord(vector<Record>& records, int id) {
        int index = binarySearch(records, id);

        if (index == -1) {
            cout << "Record not found.\n";
            return;
        }

        records.erase(records.begin() + index);
        cout << "Record deleted successfully.\n";
    }
};

void viewRecords(const vector<Record>& records) {
    if (records.empty()) {
        cout << "No records available.\n";
        return;
    }

    for (const Record& r : records) {
        cout << "ID: " << r.id << ", Name: " << r.name << endl;
    }
}

void searchRecord(const vector<Record>& records, int id) {
    int index = Admin::binarySearch(records, id);

    if (index == -1)
        cout << "Record not found.\n";
    else
        cout << "Record found: " << records[index].id
             << ", " << records[index].name << endl;
}

int main() {
    vector<Record> records = {
        {101, "Alice"},
        {103, "Charlie"},
        {105, "David"}
    };

    Admin admin("Kenny");
    RegularUser regular("Student");

    int role;
    cout << "Choose a role:\n1. Admin\n2. Regular User\nChoice: ";
    if (!(cin >> role)) return 0;

    if (role == 1) {
        admin.showRole();

        int choice;
        do {
            cout << "\n1. View records\n2. Add record\n"
                 << "3. Delete record\n4. Search record\n0. Exit\nChoice: ";
            cin >> choice;

            if (choice == 1) viewRecords(records);
            else if (choice == 2) {
                int id;
                string name;
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter name (one word): ";
                cin >> name;
                admin.addRecord(records, id, name);
            } else if (choice == 3) {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                admin.deleteRecord(records, id);
            } else if (choice == 4) {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;
                searchRecord(records, id);
            }
        } while (choice != 0);

    } else if (role == 2) {
        regular.showRole();

        int choice;
        do {
            cout << "\n1. View records\n2. Search record\n0. Exit\nChoice: ";
            cin >> choice;

            if (choice == 1) viewRecords(records);
            else if (choice == 2) {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;
                searchRecord(records, id);
            }
        } while (choice != 0);

    } else {
        cout << "Invalid role.\n";
    }

    return 0;
}
