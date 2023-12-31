#include "iostream"
using namespace std;
#include "Manager.cpp"

int main()
{
    Manager mg;
Entrance:
    cout<<"**********  图书管理系统  ***********"<<endl;
    cout<<"********** 1、借阅书籍 **************"<<endl;
    cout<<"********** 2、归还书籍 **************"<<endl;
    cout<<"********** 3、添加信息 **************"<<endl;
    cout<<"********** 4、修改信息 **************"<<endl;
    cout<<"********** 5、查询信息 **************"<<endl;
    cout<<"********** 6、删除信息 **************"<<endl;
    cout<<"********** 7、退出系统 **************"<<endl;
    cout<<endl<<"请选择要使用的功能：";
    int step=0;
    cin>>step;
    while(step<1||step>7)
    {
        cout<<"输入错误，请重新输入:";
        cin>>step;
    }
    switch (step)
    {
    case 1:
        mg.Borrow();
        break;
    case 2:
        mg.Return();
        break;
    case 3:
        mg.Add_Info();
        break;
    case 4:
        mg.Change_Info();
        break;
    case 5:
        mg.Research_Info();
        break;
    case 6:
        mg.Delate_Info();
        break;
    default:
        mg.Save();
        return 0;
    }
    cout<<endl;
    goto Entrance;
}