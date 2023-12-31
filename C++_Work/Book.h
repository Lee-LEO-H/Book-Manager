#pragma once
#include "bits/stdc++.h"
using namespace std;

class Book
{
private:

public:
    string Number;
    string Name;
    string Author;
    string Publicer;
    int Price;
    int Count;
    bool is_Return;
    Book(string number,string name,string author,string publicer,int price,int count,bool is_return=true);
    Book(Book& obj);
    ~Book();
};

