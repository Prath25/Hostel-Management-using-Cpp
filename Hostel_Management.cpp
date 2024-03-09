#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <map>
using namespace std;

map<int, int> m;
int room_no = 1;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void print_star()
{
    cout << endl;
    SetConsoleTextAttribute(h, 13);
    for (int i = 1; i <= 70; i++)
        cout << "*";
    cout << endl;
}

class Student_login;
class Student_Info
{
public:
    char name[100], address[100], parent_cont[100], student_cont[100];
    int year;
    long long int id;
};

class complaint
{
public:
    long long int id2;
    complaint(long long int a)
    {
        id2 = a;
    }
    complaint() {}

    char comp[250];

    void set_complaint();
    void complete_complaint(long long int);
    void store_complaint();
};

class New_Admission : Student_Info
{
public:
    float hostel_fees = 10000, mess_fees = 15000;
    int student_room;
    char update_code;
    friend class Student_login;
    void set_info()
    {
        SetConsoleTextAttribute(h, 11);

        cout << "\t\tEnter Student Name : ";
        fflush(stdin);
        cin.getline(name, 100);
        cout << "\t\tEnter your registration number : ";
        cin >> id;
        cout << "\t\tEnter Student Address : ";
        fflush(stdin);
        cin.getline(address, 100);
        cout << "\t\tEnter the Academics year : ";
        fflush(stdin);
        cin >> year;
        cout << "\t\tEnter Student contact : ";
        cin >> student_cont;
        cout << "\t\tEnter Parent contact : ";
        cin >> parent_cont;
        Room_alllocation();
        student_room = room_no;
        update_code = 'y';

        print_star();
    }
    void Display_Data();
    void store_data();
    void search_data();
    void delete_data();
    void delete_data(char);
    void update_data();
    void Room_alllocation();
    void view_complaint();
};

void New_Admission::store_data()
{
    ofstream obj;
    obj.open("data.dat", ios::app);
    obj.write((char *)this, sizeof(*this));
    obj.close();
}

void New_Admission::search_data()
{
    SetConsoleTextAttribute(h, 10);

    long long int roll;
    fflush(stdin);
    cout << "\t\tEnter the registration number of the student: ";
    cin >> roll;
    ifstream obj1;
    obj1.open("data.dat", ios::in);
    obj1.read((char *)this, sizeof(*this));
    bool flag = true;
    while (!obj1.eof())
    {
        if (roll == id)
        {
            Display_Data();
            flag = false;
        }
        obj1.read((char *)this, sizeof(*this));
    }
    if (flag)
        cout << "\t\tData is not found in system" << endl;

    obj1.close();
    print_star();
}

void New_Admission::delete_data()
{
    SetConsoleTextAttribute(h, 8);

    long long int roll;
    cout << "\t\tEnter Registration Number: ";
    cin >> roll;
    ifstream fin;
    ofstream fout;
    fin.open("data.dat", ios::in);
    if (!fin)
        cout << "\t\tRecord not found.\n";
    else
    {
        fout.open("tempfile.dat", ios::out);
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (roll != id)
            {
                fout.write((char *)this, sizeof(*this));
            }
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("data.dat");
        rename("tempfile.dat", "data.dat");

        SetConsoleTextAttribute(h, 4);
        cout << "\t\tData deleted Successfully";
    }
    print_star();
}

void New_Admission::delete_data(char x)
{

    ifstream fin;
    ofstream fout;
    fin.open("data.dat", ios::in);

    fout.open("tempfile.dat", ios::out);
    fin.read((char *)this, sizeof(*this));
    while (!fin.eof())
    {
        if (x != update_code)
        {
            fout.write((char *)this, sizeof(*this));
        }
        fin.read((char *)this, sizeof(*this));
    }
    fin.close();
    fout.close();
    remove("data.dat");
    rename("tempfile.dat", "data.dat");
}

void New_Admission::update_data()
{
    SetConsoleTextAttribute(h, 11);

    long long int a;
    New_Admission temp;
    cout << "Please enter your registration number: ";
    cin >> a;
    bool flag = false;
    int x;
    char y[100];
    fstream obj;
    obj.open("data.dat", ios::in | ios::out | ios::ate | ios::binary);
    obj.seekg(0);
    obj.read((char *)&temp, sizeof(temp));
    while (!obj.eof())
    {
        if (a == temp.id)
        {
            flag = true;
            // update_code = 'n';
            int opt;
            cout << "Select the field to edit\n";
            cout << "1. Name" << endl
                 << "2. Registration Number" << endl
                 << "3. Address" << endl
                 << "4. Academic Year" << endl
                 << "5. Student Contact" << endl
                 << "6. Parent Contact" << endl;
            cin >> opt;
            switch (opt)
            {
            case 1:
                cout << "Enter Name: ";
                fflush(stdin);
                cin.getline(temp.name, 100);
                break;
            case 2:
                cout << "Enter Registration Number: ";
                cin >> temp.id;
                break;
            case 3:
                cout << "Enter Address: ";
                fflush(stdin);
                cin.getline(temp.address, 100);
                break;
            case 4:
                cout << "Enter Academic Year: ";
                cin >> temp.year;
                break;
            case 5:
                cout << "Enter Students Contact: ";
                fflush(stdin);
                cin >> temp.student_cont;
                break;
            case 6:
                cout << "Enter Parents Contact: ";
                fflush(stdin);
                cin >> temp.parent_cont;
                break;
            default:
                cout << "Please Enter Valid Input.\n";
            }
            int pos = obj.tellp();
            obj.seekp(pos - sizeof(*this));
            obj.write((char *)&temp, sizeof(temp));
        }
        obj.read((char *)&temp, sizeof(temp));
    }
    SetConsoleTextAttribute(h, 10);
    obj.close();
    if (flag)
        cout << "Details Updated Successfully...:)";
    else
    {
        SetConsoleTextAttribute(h, 4);
        cout << "Data not found...";
    }
    print_star();
}

void New_Admission::view_complaint()
{
    cout << "Student Complaints :" << endl;
    SetConsoleTextAttribute(h, 5);
    complaint temp2;
    ifstream obj4;
    obj4.open("complaint.dat", ios::in | ios::binary);
    obj4.read((char *)&temp2, sizeof(temp2));

    while (!obj4.eof())
    {
        cout << "Registration Number: " << temp2.id2 << endl;
        cout << "Complaint: " << temp2.comp << endl
             << endl;
        obj4.read((char *)&temp2, sizeof(temp2));
    }
    obj4.close();
    print_star();
}

class Student_login : New_Admission
{
public:
    long long int roll_no;
    friend class New_Admission;
    ~Student_login() {}
    void get_detail(long long int);
    void pay_fees(long long int);
    void complaint();
    void update_payment(long long int);
    void store_payment_info();
    int payment_code(long long int);
};

int Student_login::payment_code(long long int a)
{
    ifstream obj;
    obj.open("payment.dat", ios::in | ios::binary);
    if (!obj)
        return 1;
    obj.read((char *)this, sizeof(*this));
    while (!obj.eof())
    {
        if (a == roll_no)
            return 0;
        obj.read((char *)this, sizeof(*this));
    }
    return 1;
}
void New_Admission::Display_Data()
{
    SetConsoleTextAttribute(h, 14);
    cout << "\t\tRequired Student Details\n";
    cout << "\t\tName: " << name << endl;
    cout << "\t\tRegistration Number: " << id << endl;
    cout << "\t\tAddress: " << address << endl;
    cout << "\t\tPursuing Year: " << year << endl;
    cout << "\t\tStudent Contact: " << student_cont << endl;
    cout << "\t\tParents Contact: " << parent_cont << endl;
    cout << "\t\tAlloted Room Number: " << student_room << endl;
}

void Student_login::get_detail(long long int roll)
{
    SetConsoleTextAttribute(h, 1);
    New_Admission temp;
    ifstream obj1;
    obj1.open("data.dat", ios::in);
    obj1.read((char *)&temp, sizeof(temp));
    bool flag = true;
    while (!obj1.eof())
    {
        if (roll == temp.id)
        {
            temp.Display_Data();
            flag = false;
        }
        obj1.read((char *)&temp, sizeof(temp));
    }
    if (flag)
        cout << "Sorry!!! Data is not found in the system... :(" << endl;
    obj1.close();
    print_star();
}

void Student_login ::pay_fees(long long int a)
{
    SetConsoleTextAttribute(h, 2);
    Student_login obj;
    fflush(stdin);
    if(obj.payment_code(a)==1)
        {hostel_fees = 10000;
    mess_fees = 15000;}
    int temp1 = hostel_fees, temp2 = mess_fees;
    roll_no = a;
    int n, temp=0;
    fflush(stdin);
    cout << "Enter 1 to make Hostel Fees payment\nEnter 2 to make Mess Fees payment." << endl;
    cin >> n;
    switch (n)
    {
    case 1:
    {
        cout << "Remaining fees : " << hostel_fees << endl;
        if (hostel_fees)
        {
            cout << "Enter the amount to be paid : ";
            cin >> temp;
            hostel_fees -= temp;
            cout << "Remaining fees : " << hostel_fees << endl;
            mess_fees = temp2;
        }
    }
    break;
    case 2:
    {
        cout << "Remaining fees : " << mess_fees << endl;
        if (mess_fees)
        {
            cout << "Enter the amount to be paid : ";
            cin >> temp;
            mess_fees -= temp;
            cout << "Remaining fees : " << mess_fees << endl;
            hostel_fees = temp1;
        }
    }
    break;
    }
    print_star();
}

void Student_login::update_payment(long long int y)
{
    fstream obj;
    bool flag = false;
    obj.open("payment.dat", ios::in | ios::out | ios::ate);
    obj.seekg(0);
    obj.read((char *)this, sizeof(*this));
    while (!obj.eof())
    {
        if (y == roll_no)
        {
            flag = true;
            pay_fees(y);
            int pos = obj.tellp();
            obj.seekp(pos - sizeof(*this));
            obj.write((char *)this, sizeof(*this));
        }
        obj.read((char *)this, sizeof(*this));
    }
    obj.close();
}

void Student_login ::store_payment_info()
{
    ofstream obj;
    obj.open("payment.dat", ios::app | ios::binary);
    obj.write((char *)this, sizeof(*this));
    obj.close();
}

void complaint::store_complaint()
{
    ofstream obj;
    obj.open("complaint.dat", ios::app | ios::binary);
    obj.write((char *)this, sizeof(*this));
    obj.close();
}

void complaint ::set_complaint()
{
    SetConsoleTextAttribute(h, 8);
    cout << "Enter your complaint : ";
    fflush(stdin);
    cin.getline(comp, 250);
    cout << "Thanks !" << endl;
}

void complaint ::complete_complaint(long long int x)
{
    SetConsoleTextAttribute(h, 3);
    ifstream fin;
    ofstream fout;
    fin.open("complaint.dat", ios::in);
    if (!fin)
        cout << "Record not found.\n";
    else
    {
        fout.open("tempfile1.dat", ios::out);
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (x != id2)
            {
                fout.write((char *)this, sizeof(*this));
            }
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("complaint.dat");
        rename("tempfile1.dat", "complaint.dat");
    }
}

void New_Admission ::Room_alllocation()
{
    int i = 0;
    for (i = 1; i <= room_no; i++)
    {
        if (m.find(i) == m.end() || m[i] < 3) // no one in room || less than 3 in room
        {
            m[i]++;
            return;
        }
    }
    if (m[i - 1] == 3) // room is full
    {
        room_no++;
        m[i]++;
        return;
    }
}

int main()
{
    SetConsoleTextAttribute(h, 9);

    while (1)
    {
        int opt;
        cout << "\t\t 1. Faculty Login" << endl
             << "\t\t 2. Student Login" << endl
             << "\t\t 3. Exit" << endl;
        cout << "Choose Login Option: ";
        cin >> opt;
        if (opt == 1)
        {
            SetConsoleTextAttribute(h, 5);
            int n;
            New_Admission obj;
            cout << "Please Enter Your Choice" << endl;

            cout << "\t\t\t 1. New Admission" << endl
                 << "\t\t\t 2. Search Student Data" << endl
                 << "\t\t\t 3. Delete Student Data" << endl
                 << "\t\t\t 4. Update Student Data" << endl
                 << "\t\t\t 5. Complaints" << endl
                 << "\t\t\t 6. Exit" << endl;
            cin >> n;
            if (n == 1)
            {
                obj.set_info();
                obj.store_data();
            }
            else if (n == 2)
                obj.search_data();
            else if (n == 3)
                obj.delete_data();
            else if (n == 4)
                obj.update_data();
            else if (n == 5)
                obj.view_complaint();
            else if (n = 6)
            {
                cout << "Thank you...:)" << endl;
                exit(0);
            }
            else
                cout << "Please Choose Valid Option..." << endl;
        }

        else if (opt == 2)
        {
            int n;
            long long int p;
            cout << "Please Enter Your Registration Number: ";
            cin >> p;
            Student_login obj1;
            complaint one(p);
            cout << "Please Enter Your Choice " << endl;
            cout << "\t\t\t 1. View Your Detaila" << endl
                 << "\t\t\t 2. Pay Fees" << endl
                 << "\t\t\t 3. Register Complaint" << endl
                 << "\t\t\t 5. Exit" << endl;
            fflush(stdin);
            cin >> n;
            if (n == 1)
                obj1.get_detail(p);
            else if (n == 2)
            {
                fflush(stdin);
                if (obj1.payment_code(p) == 0)
                    obj1.update_payment(p);
                else
                {
                fflush(stdin);
                    obj1.pay_fees(p);
                    obj1.store_payment_info();
                }
            }
            else if (n == 3)
            {
                one.set_complaint();
                one.store_complaint();
            }
            else if (n == 4)
            {
                cout << "Thank You...:)" << endl;
                exit(0);
            }
            else
                cout << "Please Enter Valid Input..." << endl;
        }

        else if (opt == 3)
        {
            cout << "Thank You...:)";
            exit(0);
        }
        else
            cout << "Please enter valid input...." << endl;
    }
}