#include "Administrator.h"

Administrator::Administrator(string name,string number,string id):Person(name,number,id)
{
}
Administrator::~Administrator()
{
}
void Administrator::display_Info()
{
    cout<<"**************该人员信息如下**************"<<endl;
    cout<<"身份："<<Person::Id<<endl;
    cout<<"姓名："<<Person::Name<<endl;
    cout<<"工号："<<Person::Number<<endl;
}
