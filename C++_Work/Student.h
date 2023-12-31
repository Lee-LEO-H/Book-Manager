#pragma once
#include "bits/stdc++.h"
using namespace std;
#include "Person.h"


class Student:public Person
{
private:
    string Academy;
    int Count;

public:
    
    Student(string name,string number,string academy,int count=3 ,int borrow_count=0, string id="student");
    void display_Info();
    ~Student();
};

