#pragma once
#include "bits/stdc++.h"
using namespace std;
#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "Administrator.h"
#include "Book.h"

class Manager
{
private:
    Person** person_arr;
    int person_count;
    Book** book_arr;
    int book_count;
    bool fileisEmpty;

public:
    Manager(/* args */);
    ~Manager();
    void Borrow(void);
    void Return(void);
    void Research_Info(void);
    void Change_Info(void);
    void Add_Info(void);
    void Delete_Info(void);
    struct check_info check_Identity(void);
    void Save(void);
    void Read(void);
    int Get_Person_Num(void);
    int Get_Book_Num(void);
    void Init_Person(void);
    void Init_Book(void);
};

struct check_info
{
    string name;
    string number;
};




