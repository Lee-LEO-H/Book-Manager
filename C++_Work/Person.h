#pragma once
#include "bits/stdc++.h"
using namespace std;
#include "Book.h"
#include "vector"

class Person
{
private:
    /* data */
public:
    string Name;
    string Number;
    string Id;
    string Academy;
    string Title;
    int Count;
    int Borrow_Count;
    vector<Book*> borrow_record;
    vector<Book*> return_record;

    Person(/* args */);
    Person(string name,string number,string academy,int count,int borrow_count,string id);
    Person(string name,string number,string academy,string title,int count,int borrow_count,string id);
    Person(string name,string number,string id);
    virtual void display_Info()=0;
    ~Person();
};


