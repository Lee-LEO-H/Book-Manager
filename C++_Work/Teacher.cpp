#include "Teacher.h"

Teacher::Teacher(string name,string number,string academy,string title,int count,int borrow_count,string id):Person(name,number,academy,title,count,borrow_count,id)
{
    this->Academy=academy;
    this->Title=title;
    this->Count=count;
}
Teacher::~Teacher()
{
}
void Teacher::display_Info()
{
    cout<<"**************该人员信息如下**************"<<endl;
    cout<<"身份："<<Person::Id<<endl;
    cout<<"姓名："<<Person::Name<<endl;
    cout<<"工号："<<Person::Number<<endl;
    cout<<"学院："<<Person::Academy<<endl;
    cout<<"职称："<<Person::Title<<endl;
    cout<<"最大借阅量："<<Person::Count<<endl;
}