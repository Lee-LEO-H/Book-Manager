#pragma once
#include "bits/stdc++.h"
using namespace std;
#include "Person.h"

class Teacher :public Person
{
private:
    string Academy;
    string Title;
    int Count;
public:
    Teacher(string name,string number,string academy,string title,int count=3,int borrow_count=0, string id="teacher");
    ~Teacher();
    void display_Info();
};

