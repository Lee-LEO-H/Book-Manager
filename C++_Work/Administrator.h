#pragma once
#include "bits/stdc++.h"
using namespace std;
#include "Person.h"


class Administrator :public Person
{
private:
public:
    Administrator(string name,string number,string id="administrator");
    ~Administrator();
    void display_Info();
};

