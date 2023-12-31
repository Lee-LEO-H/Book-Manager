#include "iostream"
using namespace std;
#include "Manager.cpp"

int main()
{
    Manager mg; //实例化对象
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
    //借阅功能
    case 1:
        mg.Borrow();
        break;
    //归还功能
    case 2:
        mg.Return();
        break;
    //添加信息功能
    case 3:
        mg.Add_Info();
        break;
    //修改信息功能
    case 4:
        mg.Change_Info();
        break;
    //查询信息功能
    case 5:
        mg.Research_Info();
        break;
    //删除信息功能
    case 6:
        mg.Delete_Info();
        break;
    //退出系统并保存数据到记事本
    default:
        mg.Save();
        return 0;
    }
    cout<<endl;
    goto Entrance;
}