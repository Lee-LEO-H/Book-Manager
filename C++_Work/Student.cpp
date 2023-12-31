#include "Student.h"

Student::Student(string name,string number,string academy,int count,int borrow_count,string id):Person(name,number,academy,count,borrow_count,id)
{
    this->Academy=academy;
    this->Count=count;
}
void Student::display_Info()
{
    cout<<"**************该人员信息如下**************"<<endl;
    cout<<"身份："<<Person::Id<<endl;
    cout<<"姓名："<<Person::Name<<endl;
    cout<<"学号："<<Person::Number<<endl;
    cout<<"学院："<<Person::Academy<<endl;
    cout<<"最大借阅量："<<Person::Count<<endl;
}

