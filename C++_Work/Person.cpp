#include "Person.h"

Person::Person(/* args */)
{

}

Person::~Person()
{
}

Person::Person(string name,string number,string id)
{
    this->Name=name;
    this->Number=number;
    this->Id=id;
}
Person::Person(string name,string number,string academy,int count,int borrow_count,string id)
{
    this->Name=name;
    this->Number=number;
    this->Id=id;
    this->Academy=academy;
    this->Count=count;
    this->Borrow_Count=borrow_count;
}

Person::Person(string name,string number,string academy,string title,int count,int borrow_count,string id)
{
    this->Name=name;
    this->Number=number;
    this->Id=id;
    this->Academy=academy;
    this->Count=count;
    this->Title=title;
    this->Borrow_Count=borrow_count;
}