#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;

const char fname[] = "hospital_record.txt";

struct record {
    char id[5], name[15], age[5], sex[5], contact[15], time[10], description[100];
};

class hospital {
public:
    void pack(record r);
    record unpack(char a[]);
    void writedata();
    int owner_authen();
    void display();
    void search();
    void modify();
};

int hospital::owner_authen() {
    char o_username[20], o_password[20];
    const char o_user[20] = "moiz07", o_pass[20] = "tom123";
    cout << endl << endl;
    cout.width(25);
    cout << "Enter Doctor's User id and Password\n" << "------------------------------------------------------------------------------------\n";
    cout << endl << "username: ";
    cin >> o_username;
    cout << "password: ";
    cin >> o_password;
    cout << "------------------------------------------------------------------------------------\n";
    if (strcmp(o_username, o_user) == 0 && strcmp(o_password, o_pass) == 0)
        return 1;
    else
        return 0;
}

void hospital::pack(record r) {
    fstream fp;
    fp.open(fname, ios::out | ios::app);
    if (!fp) {
        cout << "\nCannot open file";
        exit(0);
    }
    fp << r.id << "|" << r.name << "|" << r.age << "|" << r.sex << "|" << r.contact << "|" << r.time << "|" << r.description << "|*\n";
    fp.close();
}

record hospital::unpack(char buff[]) {
    record r;
    int i = 0, j = 0;
    while (buff[j] != '|') r.id[i++] = buff[j++];
    r.id[i] = '\0';
    i = 0; j++;
    while (buff[j] != '|') r.name[i++] = buff[j++];
    r.name[i] = '\0';
    i = 0; j++;
    while (buff[j] != '|') r.age[i++] = buff[j++];
    r.age[i] = '\0';
    i = 0; j++;
    while (buff[j] != '|') r.sex[i++] = buff[j++];
    r.sex[i] = '\0';
    i = 0; j++;
    while (buff[j] != '|') r.contact[i++] = buff[j++];
    r.contact[i] = '\0';
    i = 0; j++;
    while (buff[j] != '|') r.time[i++] = buff[j++];
    r.time[i] = '\0';
    i = 0; j++;
    while (buff[j] != '|') r.description[i++] = buff[j++];
    r.description[i] = '\0';
    return r;
}

void hospital::writedata() {
    record r;
    cout << "\nEnter ID:";
    cin >> r.id;
    cout << "\nEnter Name:";
    cin >> r.name;
    cout << "\nEnter age:";
    cin >> r.age;
    cout << "\nEnter Sex (M/F):";
    cin >> r.sex;
    cout << "\nEnter Contact Number:";
    cin >> r.contact;
    cout << "\nEnter Time Slot:";
    cin >> r.time;
    cout << "\nEnter Description:";
    cin >> r.description;
    pack(r);
}

void hospital::display() {
    fstream fp;
    char buff[500];
    record r;
    fp.open(fname, ios::in);
    if (!fp) {
        cout << "\nCannot open file";
        exit(0);
    }
    cout << "#\tID\tName\tAge\tSex\tContact Number\tTime Slot\tDescription\n";
    int c = 1;
    while (true) {
        fp.getline(buff, 500, '*');
        if (fp.eof()) break;
        r = unpack(buff);
        cout << c << "\t" << r.id << "\t" << r.name << "\t" << r.age << "\t" << r.sex << "\t" << r.contact << "\t" << r.time << "\t" << r.description << endl;
        c++;
    }
    fp.close();
}

void hospital::modify() {
    fstream fp;
    char id[15], buff[500];
    int i, j;
    record s[100];
    fp.open(fname, ios::in);
    if (!fp) {
        cout << "\nCannot open file";
        exit(0);
    }
    cout << "\nEnter the ID to be modified:";
    cin >> id;
    i = 0;
    while (true) {
        fp.getline(buff, 500, '*');
        if (fp.eof()) break;
        s[i] = unpack(buff);
        i++;
    }
    fp.close();

    for (j = 0; j < i; j++) {
        if (strcmp(s[j].id, id) == 0) {
            cout << "\nValues of the record are:\n";
            cout << "\nID:" << s[j].id;
            cout << "\nName:" << s[j].name;
            cout << "\nAge:" << s[j].age;
            cout << "\nSex (M/F):" << s[j].sex;
            cout << "\nContact:" << s[j].contact;
            cout << "\nTime Slot:" << s[j].time;
            cout << "\nDescription:" << s[j].description;
            cout << "\nEnter the new values:\n";
            cout << "\nID:";
            cin >> s[j].id;
            cout << "\nName:";
            cin >> s[j].name;
            cout << "\nAge:";
            cin >> s[j].age;
            cout << "\nSex (M/F):";
            cin >> s[j].sex;
            cout << "\nContact:";
            cin >> s[j].contact;
            cout << "\nTime Slot:";
            cin >> s[j].time;
            cout << "\nDescription:";
            cin >> s[j].description;
            break;
        }
    }
    if (j == i) {
        cout << "\nRecord not found";
        return;
    }
    fstream fd;
    fd.open(fname, ios::out | ios::trunc);
    if (!fd) {
        cout << "\nCannot open file";
        exit(0);
    }
    for (j = 0; j < i; j++)
        pack(s[j]);
    fd.close();
}

void hospital::search() {
    fstream fp;
    char id[15], buff[500];
    record s;
    fp.open(fname, ios::in);
    if (!fp) {
        cout << "\nCannot open file";
        exit(0);
    }
    cout << "\nEnter the ID to be searched:";
    cin >> id;
    while (true) {
        fp.getline(buff, 500, '*');
        if (fp.eof()) break;
        s = unpack(buff);
        if (strcmp(s.id, id) == 0) {
            cout << "\nRecord found\n";
            cout << "\nID:" << s.id;
            cout << "\nName:" << s.name;
            cout << "\nAge:" << s.age;
            cout << "\nSex (M/F):" << s.sex;
            cout << "\nContact:" << s.contact;
            cout << "\nTime Slot:" << s.time;
            cout << "\nDescription:" << s.description;
            return;
        }
    }
    cout << "\nRecord not found";
}

int main() {
    int ch, user;
    hospital obj;
    cout << "------------------------------------------------------------------------------------\n" << "1.Doctor\n2.Patient\n" << "------------------------------------------------------------------------------------\n";
    cout << "Select User: ";
    cin >> user;
    switch (user) {
    case 1: {
        int check;
        check = obj.owner_authen();
        if (check == 1) {
            cout << "Welcome Doctor\n" << "------------------------------------------------------------------------------------\n";
            cout << "1.Write Data\n2.Display\n3.Search\n4.Modify\n5.Exit:";
            while (true) {
                cout << "\nEnter your choice:";
                cin >> ch;
                switch (ch) {
                case 1: obj.writedata();
                    break;
                case 2: obj.display();
                    break;
                case 3: obj.search();
                    break;
                case 4: obj.modify();
                    break;
                default: exit(0);
                }
            }
        }
        else {
            cout << endl << "Invalid Username or Password!! Please try again...";
        }
        break;
    }
    case 2: {
        cout << "Patient Record\n" << "------------------------------------------------------------------------------------\n";
        while (true) {
            obj.search();
        }
        break;
    }
    default: exit(0);
    }
    return 0;
}
