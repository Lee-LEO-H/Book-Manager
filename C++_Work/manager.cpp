#include"manager.h"

#include "Person.cpp"
#include "Student.cpp"
#include "Teacher.cpp"
#include "Administrator.cpp"
#include "Book.cpp"

#define PersonFileName    "D:/VSCODEProj/C++_Work/PersonFile.txt"
#define BookFileName    "D:/VSCODEProj/C++_Work/BookFile.txt"
//身份验证函数
//返回string类型的身份
struct check_info Manager:: check_Identity()
{
    string identity;
    string name;string number;
    cout<<"请输入姓名：";
    cin>>name;
    cout<<"请输入工号/学号:";
    cin>>number;
    struct check_info info;
    info.name="0";
    info.number="0";
    for(int i=0;i<this->person_count;i++)
    {
        if(this->person_arr[i]->Name==name && this->person_arr[i]->Number==number)
        {
            info.name=name;
            info.number=number;
            return info;
        }
    }
    cout<<"查无此人，请先添加该人信息"<<endl;
    return info;
}

void Manager::Borrow(){
    struct check_info identity;
    identity=check_Identity();
    if (identity.name=="0")
        return;
    string name;
    string number;
    // int index[10];
    for(int j=0;j<this->person_count;j++)
    {
        if(this->person_arr[j]->Number==identity.number && this->person_arr[j]->Name==identity.name)
        {
            cout<<"请输入要借阅书籍的名字：";
            cin>>name;
            int find_flag=0;
            cout<<"--------------------------------------查询到有以下图书--------------------------------------"<<endl;
            for(int i =0,k=0;i<this->book_count;i++)
            {
                if(this->book_arr[i]->Name==name)
                {
                    cout<<std::left<<setw(1)<<k+1<<".";
                    cout<<std::left<<setw(4)<<"索取号："<<std::left<<setw(12)<<this->book_arr[i]->Number;
                    cout<<std::left<<setw(3)<<"书名："<<std::left<<setw(10)<<this->book_arr[i]->Name;
                    cout<<std::left<<setw(3)<<"作者："<<std::left<<setw(10)<<this->book_arr[i]->Author;
                    cout<<std::left<<setw(4)<<"出版社："<<std::left<<setw(10)<<this->book_arr[i]->Publicer;
                    cout<<std::left<<setw(3)<<"价格："<<std::left<<setw(3)<<this->book_arr[i]->Price<<std::left<<setw(7)<<"元";
                    cout<<std::left<<setw(5)<<"可借数量："<<std::left<<setw(4)<<this->book_arr[i]->Count;
                    cout<<endl;
                    // index[k]=i;
                    k++;
                    find_flag=1;
                }
            }
            if(find_flag==0)
            {
                cout<<"馆内无该图书"<<endl;
                return;
            }
            else
            {
                cout<<"请输入你要选择借阅书籍的索取号：";
                cin>>number;
                for(int i=0;i<this->book_count;i++)
                {
                    if(this->book_arr[i]->Number==number&&this->book_arr[i]->Count>0)
                    {
                        if(this->person_arr[j]->Borrow_Count>=this->person_arr[j]->Count)
                        {
                            cout<<"已超过最大借阅量，请先归还已借书籍!"<<endl;
                            return;
                        }
                        else
                        {

                        
                            for(int m=0;m<this->person_arr[j]->borrow_record.size();m++)
                            {
                                if(this->person_arr[j]->borrow_record[m]->Name==name &&this->person_arr[j]->borrow_record[m]->Number==number )
                                {
                                    if(this->person_arr[j]->borrow_record[m]->is_Return==true)
                                    {
                                        Book * record_book=new Book(*(this->book_arr[i]));
                                        record_book->is_Return=false;
                                        this->person_arr[j]->borrow_record.push_back(record_book);
                                        this->person_arr[j]->Borrow_Count+=1;
                                        this->book_arr[i]->Count-=1;
                                        cout<<"借阅成功！"<<endl;
                                        return;
                                    }
                                    else
                                    {
                                        cout<<"你已借阅该书籍且未归还，请先归还书籍"<<endl;
                                        return;     
                                    } 
                                }
                            }
                            Book * record_book=new Book(*(this->book_arr[i]));
                            record_book->is_Return=false;
                            this->person_arr[j]->borrow_record.push_back(record_book);
                            this->person_arr[j]->Borrow_Count+=1;
                            this->book_arr[i]->Count-=1;
                            cout<<"借阅成功！"<<endl;
                            return;
                        }
                        
                    }
                    else if(this->book_arr[i]->Number==number&& this->book_arr[i]->Count<=0)
                    {
                        cout<<"该图书可借数量为0，无法借阅！"<<endl;
                        return;
                    }
                }
                cout<<"输入索取号有误！"<<endl;
            }
        }
    }

}

void Manager::Return()
{
    struct check_info identity;
    identity=check_Identity();
    if (identity.name=="0")
        return;
    string name;
    string number;
    // int index[10];
    for(int j=0;j<this->person_count;j++)
    {
        if(this->person_arr[j]->Number==identity.number && this->person_arr[j]->Name==identity.name)
        {
            cout<<"请输入要归还书籍的信息"<<endl;
            cout<<"书名：";
            cin>>name;
            cout<<"索取号：";
            cin>>number;
            for(int i=0;i<this->book_count;i++)
            {
                if(this->book_arr[i]->Name==name && this->book_arr[i]->Number==number)
                {
                    for(int k=0;k<this->person_arr[j]->borrow_record.size();k++)
                    {
                        if(this->person_arr[j]->borrow_record[k]->Name==name &&this->person_arr[j]->borrow_record[k]->Number==number && this->person_arr[j]->borrow_record[k]->is_Return==false)
                        {
                            this->person_arr[j]->return_record.push_back(this->book_arr[i]);
                            this->person_arr[j]->borrow_record[k]->is_Return=true;
                            this->book_arr[i]->Count+=1;
                            this->person_arr[j]->Borrow_Count-=1;
                            cout<<"归还成功！"<<endl;;
                            return;
                        }
                    }
                    cout<<"查询不到你有该图书的借阅记录！"<<endl;
                    return;
                }
            }
            cout<<"馆内无录入此书籍!"<<endl;
            return;
        }
    }
}

void Manager::Add_Info()
{
    cout<<"请问需要添加人员信息还是书籍信息? 1.添加人员 2.添加书籍"<<endl;
    cout<<"请输入：";
    int choice;
    cin>>choice;
    while(choice!=1&&choice!=2)
    {
        cout<<"输入错误,请输入1或2：";
        cin>>choice;
    }
    if(choice==1)
    {
        Person ** newspace =new Person*[this->person_count+1];
        if(this->person_arr!=NULL)
        {
            for(int i=0;i<this->person_count;i++)
            {
                newspace[i]=this->person_arr[i];
            }
        }
        cout<<"请输入添加人员的身份：1.student 2.teacher 3.administrator：";
        int identity;
        cin>>identity;
        while(identity<1&&identity>3)
        {
            cout<<"输入有误，请重新输入：";
            cin>>identity;
        }
        string name;
        string number;
        string academy;
        string title;
        Person * p=NULL;
        if(identity==1)
        {
            cout<<"请输入名字：";
            cin>>name;
            cout<<"请输入学号：";
            cin>>number;
            cout<<"请输入学院：";
            cin>>academy;
            p=new Student(name,number,academy);
        }
        else if(identity==2)
        {
            cout<<"请输入名字：";
            cin>>name;
            cout<<"请输入工号：";
            cin>>number;
            cout<<"请输入学院：";
            cin>>academy;
            cout<<"请输入职称：";
            cin>>title;
            p=new Teacher(name,number,academy,title);
        }
        else
        {
            cout<<"请输入名字：";
            cin>>name;
            cout<<"请输入工号：";
            cin>>number;
            p=new Administrator(name,number);
        }

        newspace[this->person_count]=p;
        this->person_count+=1;
        // delete[] this->person_arr;
        this->person_arr=newspace;
    }
    else if(choice==2)
    {
        int addNum=0;
        cout<<"请输入添加图书的数量：";
        cin>>addNum;
        if(addNum>0)
        {
            int newSize=this->book_count+addNum;
            Book ** newspace = new Book*[newSize];
            if(this->book_arr!=NULL)
            {
                for(int i=0;i<this->book_count;i++)
                {
                    newspace[i]=this->book_arr[i];
                }
            }
            for(int i=0;i<addNum;i++)
            {
                string number;string name;string author;string publicer;int price;int count;
                cout<<"请输入第"<<i+1<<"本书的信息"<<endl;
                cout<<"索取号：";
                cin>>number;
                cout<<"书名：";
                cin>>name;
                cout<<"作者：";
                cin>>author;
                cout<<"出版社：";
                cin>>publicer;
                cout<<"价格：";
                cin>>price;
                cout<<"可借数量：";
                cin>>count;
                Book* book=new Book(number,name,author,publicer,price,count);
                newspace[this->book_count+i]=book;
            }
            // delete[] this->book_arr;
            this->book_arr=newspace;
            this->book_count=newSize;
            cout<<"成功添加"<<addNum<<"本图书"<<endl;
        } 
        else
        {
            cout<<"输入有误"<<endl;

        }
    }
    return;
}

void Manager::Research_Info()
{
    cout<<"请问需要查询人员信息还是书籍信息? 1.查询人员 2.查询书籍 3.查询记录：";
    int choice;
    cin>>choice;
    while(choice!=1&&choice!=2 &&choice!=3)
    {
        cout<<"输入错误,请输入1或2或3：";
        cin>>choice;
    }
    if(choice==1)
    {
        struct check_info identity;
        identity=this->check_Identity();
        if (identity.name=="0")
            return;
        else{
            for(int i=0;i<this->person_count;i++)
            {
                if(this->person_arr[i]->Number==identity.number && this->person_arr[i]->Name==identity.name)
                {
                    if(this->person_arr[i]->Id=="student")
                    {
                        this->person_arr[i]->display_Info();

                    }
                    else if(this->person_arr[i]->Id=="teacher")
                    {
                        this->person_arr[i]->display_Info();
                    }
                    else
                    {
                        this->person_arr[i]->display_Info();
                    }
                }
            }
        }
    }
    else if(choice==2)
    {
        cout<<"--------------------------------------馆内已记录的书籍有以下--------------------------------------"<<endl;
        for(int i =0;i<this->book_count;i++)
        {
            cout<<std::left<<setw(1)<<i+1<<".";
            cout<<std::left<<setw(4)<<"索取号："<<std::left<<setw(12)<<this->book_arr[i]->Number;
            cout<<std::left<<setw(3)<<"书名："<<std::left<<setw(10)<<this->book_arr[i]->Name;
            cout<<std::left<<setw(3)<<"作者："<<std::left<<setw(10)<<this->book_arr[i]->Author;
            cout<<std::left<<setw(4)<<"出版社："<<std::left<<setw(10)<<this->book_arr[i]->Publicer;
            cout<<std::left<<setw(3)<<"价格："<<std::left<<setw(3)<<this->book_arr[i]->Price<<std::left<<setw(7)<<"元";
            cout<<std::left<<setw(5)<<"可借数量："<<std::left<<setw(4)<<this->book_arr[i]->Count;
            cout<<endl;
        }
    }
    else
    {
        cout<<"请输入要查询人员的信息："<<endl;
        struct check_info identity;
        identity=this->check_Identity();
        if (identity.name=="0")
            return;
        else
        {
            for(int i=0;i<this->person_count;i++)
            {
                if(this->person_arr[i]->Number==identity.number && this->person_arr[i]->Name==identity.name)
                {
                    
                    cout<<"--------------------------------------借阅记录--------------------------------------"<<endl;
                    if(this->person_arr[i]->borrow_record.size()==0)
                        cout<<"                                         无"<<endl;
                    for(int j=0,k=0;j<this->person_arr[i]->borrow_record.size();j++)
                    {
                        cout<<std::left<<setw(1)<<k+1<<".";
                        cout<<std::left<<setw(4)<<"索取号："<<std::left<<setw(12)<<this->person_arr[i]->borrow_record[j]->Number;
                        cout<<std::left<<setw(3)<<"书名："<<std::left<<setw(10)<<this->person_arr[i]->borrow_record[j]->Name;
                        cout<<std::left<<setw(3)<<"作者："<<std::left<<setw(10)<<this->person_arr[i]->borrow_record[j]->Author;
                        cout<<std::left<<setw(4)<<"出版社："<<std::left<<setw(10)<<this->person_arr[i]->borrow_record[j]->Publicer;
                        cout<<std::left<<setw(5)<<"归还状态："<<std::left<<setw(8)<<this->person_arr[i]->borrow_record[j]->is_Return;
                        cout<<endl;
                        k++;
                    }
                    cout<<"--------------------------------------归还记录--------------------------------------"<<endl;
                    if(this->person_arr[i]->return_record.size()==0)
                        cout<<"                                         无"<<endl;
                    for(int j=0,k=0;j<this->person_arr[i]->return_record.size();j++)
                    {
                        cout<<std::left<<setw(1)<<k+1<<".";
                        cout<<std::left<<setw(4)<<"索取号："<<std::left<<setw(12)<<this->person_arr[i]->return_record[j]->Number;
                        cout<<std::left<<setw(3)<<"书名："<<std::left<<setw(10)<<this->person_arr[i]->return_record[j]->Name;
                        cout<<std::left<<setw(3)<<"作者："<<std::left<<setw(10)<<this->person_arr[i]->return_record[j]->Author;
                        cout<<std::left<<setw(4)<<"出版社："<<std::left<<setw(10)<<this->person_arr[i]->return_record[j]->Publicer;
                        cout<<endl;
                        k++;
                    }
                }
            }
        }
    }
    return;
}

void Manager::Change_Info()
{
    int choice;
    cout<<"请输入修改信息类型：1.人员信息 2.图书信息：";
    cin>>choice;
    while(choice!=1 && choice!=2)
    {
        cout<<"输入有误，请重新输入:";
        cin>>choice;
    }
    if(choice==1)
    {
        string name;
        string number;
        string academy;
        string title;
        int count;
        cout<<"请输入需要修改信息该人的姓名和学号"<<endl;
        cout<<"姓名:";
        cin>>name;
        cout<<"学号:";
        cin>>number;
        for(int i=0;i<this->person_count;i++)
        {
            if(this->person_arr[i]->Number==number && this->person_arr[i]->Name==name)
            {
                cout<<"请根据需要进行人员信息修改，需要修改的项则输入对应信息，不需要则输入N\\n(借阅量输入-1)"<<endl;
                if(this->person_arr[i]->Id=="student")
                {
                    cout<<"姓名：";
                    cin>>name;
                    cout<<"学号：";
                    cin>>number;
                    cout<<"学院：";
                    cin>>academy;
                    cout<<"最大借阅量：";
                    cin>>count;
                    if(name !="N"&& name!="n")
                        this->person_arr[i]->Name=name;
                    if(number !="N"&& number!="n")
                        this->person_arr[i]->Number=number;
                    if(academy !="N"&& academy!="n")
                        this->person_arr[i]->Academy=academy;
                    if(count >0)
                        this->person_arr[i]->Count=count;
                }
                else if(this->person_arr[i]->Id=="teacher")
                {
                    cout<<"姓名：";
                    cin>>name;
                    cout<<"学号：";
                    cin>>number;
                    cout<<"学院：";
                    cin>>academy;
                    cout<<"职称：";
                    cin>>title;
                    cout<<"最大借阅量：";
                    cin>>count;
                    if(name !="N"&& name!="n")
                        this->person_arr[i]->Name=name;
                    if(number !="N"&& number!="n")
                        this->person_arr[i]->Number=number;
                    if(academy !="N"&& academy!="n")
                        this->person_arr[i]->Academy=academy;
                    if(title !="N"&& title!="n")
                        this->person_arr[i]->Title=title;
                    if(count >0)
                        this->person_arr[i]->Count=count;
                }
                else
                {
                    cout<<"姓名：";
                    cin>>name;
                    cout<<"学号：";
                    cin>>number;
                    if(name !="N"&& name!="n")
                        this->person_arr[i]->Name=name;
                    if(number !="N"&& number!="n")
                        this->person_arr[i]->Number=number;
                } 
                return;
            }
        }
        cout<<"查无此人"<<endl;
        return;
    }
    else
    {   
        struct check_info identity;
        cout<<"该权限仅供管理员使用，请输入管理员信息"<<endl;
        identity=this->check_Identity();
        if (identity.name=="0")
            return;
        for(int j=0;j<this->person_count;j++)
        {
            if(this->person_arr[j]->Number==identity.number && this->person_arr[j]->Name==identity.name &&this->person_arr[j]->Id=="administrator")
            {
                cout<<"--------------------------------------馆内已记录的书籍有以下--------------------------------------"<<endl;
                for(int i =0;i<this->book_count;i++)
                {
                    cout<<std::left<<setw(1)<<i+1<<".";
                    cout<<std::left<<setw(4)<<"索取号："<<std::left<<setw(12)<<this->book_arr[i]->Number;
                    cout<<std::left<<setw(3)<<"书名："<<std::left<<setw(10)<<this->book_arr[i]->Name;
                    cout<<std::left<<setw(3)<<"作者："<<std::left<<setw(10)<<this->book_arr[i]->Author;
                    cout<<std::left<<setw(4)<<"出版社："<<std::left<<setw(10)<<this->book_arr[i]->Publicer;
                    cout<<std::left<<setw(3)<<"价格："<<std::left<<setw(3)<<this->book_arr[i]->Price<<std::left<<setw(7)<<"元";
                    cout<<std::left<<setw(5)<<"可借数量："<<std::left<<setw(4)<<this->book_arr[i]->Count;
                    cout<<endl;
                }
                string number,number_change;
                string name,name_change;
                string author;
                string publicer;
                int price;
                int count;
                cout<<"请输入要修改信息的图书信息"<<endl;
                cout<<"索取号：";
                cin>>number;
                cout<<"书名：";
                cin>>name;
                for(int i=0;i<this->book_count;i++)
                {
                    if(this->book_arr[i]->Number==number && this->book_arr[i]->Name==name)
                    {
                        cout<<"请根据需要进行图书信息修改，需要修改的项则输入对应信息，不需要则输入N\\n(价格和可借数量输入-1)"<<endl;
                        cout<<"索取号：";
                        cin>>number_change;
                        cout<<"书名：";
                        cin>>name_change;
                        cout<<"作者：";
                        cin>>author;
                        cout<<"出版社：";
                        cin>>publicer;
                        cout<<"价格：";
                        cin>>price;
                        cout<<"可借数量：";
                        cin>>count;
                        if(number !="N"&& number!="n")
                            this->book_arr[i]->Number=number_change;
                        if(name !="N"&& name!="n")
                            this->book_arr[i]->Name=name_change;
                        if(author !="N"&& author!="n")
                            this->book_arr[i]->Author=author;
                        if(publicer !="N"&& publicer!="n")
                            this->book_arr[i]->Publicer=publicer;
                        if(price >0)
                            this->book_arr[i]->Price=price;
                        if(count >0)
                            this->book_arr[i]->Count=count;
                        cout<<"修改成功"<<endl;
                        }
                    else
                    {
                        cout<<"馆内未录入该书信息"<<endl;
                        return;
                    }
                }
                return;
            }
        }
        cout<<"查无此人!"<<endl;
        return;
        
    }
}

void Manager::Delate_Info()
{
    struct check_info identity;
    cout<<"该权限仅供管理员使用，请输入管理员信息"<<endl;
    identity=this->check_Identity();
    if (identity.name=="0")
        return;
    for(int i=0;i<this->person_count;i++)
    {
        if(this->person_arr[i]->Number==identity.number && this->person_arr[i]->Name==identity.name &&this->person_arr[i]->Id=="administrator")
        {
            int choice;
            cout<<"请输入删除信息类型：1.人员信息 2.图书信息：";
            cin>>choice;
            while(choice!=1 && choice!=2)
            {
                cout<<"输入有误，请重新输入:";
                cin>>choice;
            }
            if(choice==1)
            {
                if(this->person_arr==NULL|| this->person_count==0)
                {
                    cout<<"无任何人员记录，无需删除"<<endl;
                    return;
                }
                cout<<"-----------------已有人员记录如下-----------------"<<endl;
                for(int i=0;i<this->person_count;i++)
                {
                    cout<<i+1<<std::left<<setw(4)<<".身份："<<std::left<<setw(17)<<this->person_arr[i]->Id<<std::left<<setw(3)<<"姓名："<<std::left<<setw(12)<<this->person_arr[i]->Name<<std::left<<setw(6)<<"学号/工号："<<std::left<<setw(15)<<this->person_arr[i]->Number<<endl;
                }
                string name;
                string number;
                string academy;
                string title;
                int count;
                cout<<"请输入需要删除人员的姓名和学号"<<endl;
                cout<<"姓名:";
                cin>>name;
                cout<<"学号:";
                cin>>number;
                Person ** newspace =new Person*[this->person_count-1];
                int newcount=0;
                for(int i=0;i<this->person_count;i++)
                {
                    if(!(this->person_arr[i]->Number==number && this->person_arr[i]->Name==name))
                    {
                        newspace[newcount++]=this->person_arr[i];
                    }
                }
                if(newcount==this->person_count)
                    cout<<"查无此人"<<endl;
                else
                {
                    delete this->person_arr;
                    this->person_arr=newspace;
                    this->person_count=newcount;
                    cout<<"删除成功!"<<endl;
                }
                return;
            }
            else
            {
                if(this->book_arr==NULL||this->book_count==0)
                {
                    cout<<"无任何图书记录，无需删除"<<endl;
                    return;
                }
                cout<<"--------------------------------------馆内已记录的书籍有以下--------------------------------------"<<endl;
                for(int i =0;i<this->book_count;i++)
                {
                    cout<<std::left<<setw(1)<<i+1<<".";
                    cout<<std::left<<setw(4)<<"索取号："<<std::left<<setw(12)<<this->book_arr[i]->Number;
                    cout<<std::left<<setw(3)<<"书名："<<std::left<<setw(10)<<this->book_arr[i]->Name;
                    cout<<std::left<<setw(3)<<"作者："<<std::left<<setw(10)<<this->book_arr[i]->Author;
                    cout<<std::left<<setw(4)<<"出版社："<<std::left<<setw(10)<<this->book_arr[i]->Publicer;
                    cout<<std::left<<setw(3)<<"价格："<<std::left<<setw(3)<<this->book_arr[i]->Price<<std::left<<setw(7)<<"元";
                    cout<<std::left<<setw(5)<<"可借数量："<<std::left<<setw(4)<<this->book_arr[i]->Count;
                    cout<<endl;
                }
                string number;
                string name;
                cout<<"请输入要删除的图书的信息"<<endl;
                cout<<"索取号：";
                cin>>number;
                cout<<"书名：";
                cin>>name;
                Book ** newspace =new Book*[this->book_count-1];
                int newcount=0;
                for(int i=0;i<this->book_count;i++)
                {
                    if(!(this->book_arr[i]->Number==number && this->book_arr[i]->Name==name))
                    {
                        newspace[newcount++]=this->book_arr[i];
                    }
                }
                if(newcount==this->book_count)
                    cout<<"馆内未录入该书信息"<<endl;
                else
                {
                    // delete this->book_arr;
                    this->book_arr=newspace;
                    this->book_count=newcount;
                    cout<<"删除成功!"<<endl;
                }
                return;
            }
        }
    }
}

void Manager::Save()
{
    ofstream ofs;
    ofs.open(PersonFileName,ios_base::out);
    for(int i=0;i<person_count;i++)
    {
        ofs<<this->person_arr[i]->Id<<" ";
        if(this->person_arr[i]->Id=="student")
        {
            ofs<<this->person_arr[i]->Name<<" "
            <<this->person_arr[i]->Number<<" "
            <<this->person_arr[i]->Academy<<" "
            <<this->person_arr[i]->Count<<" "
            <<this->person_arr[i]->Borrow_Count<<" ";

            ofs<<this->person_arr[i]->borrow_record.size()<<" ";
            for(int k=0;k<this->person_arr[i]->borrow_record.size();k++)
            {
                ofs<<this->person_arr[i]->borrow_record[k]->Name<<" "
                <<this->person_arr[i]->borrow_record[k]->Number<<" "
                <<this->person_arr[i]->borrow_record[k]->Author<<" "
                <<this->person_arr[i]->borrow_record[k]->Publicer<<" "
                <<this->person_arr[i]->borrow_record[k]->Price<<" "
                <<this->person_arr[i]->borrow_record[k]->Count<<" "
                <<this->person_arr[i]->borrow_record[k]->is_Return<<" ";
            }
            ofs<<this->person_arr[i]->return_record.size()<<" ";
            for(int k=0;k<this->person_arr[i]->return_record.size();k++)
            {
                ofs<<this->person_arr[i]->return_record[k]->Name<<" "
                <<this->person_arr[i]->return_record[k]->Number<<" "
                <<this->person_arr[i]->return_record[k]->Author<<" "
                <<this->person_arr[i]->return_record[k]->Publicer<<" "
                <<this->person_arr[i]->return_record[k]->Price<<" "
                <<this->person_arr[i]->return_record[k]->Count<<" "
                <<this->person_arr[i]->return_record[k]->is_Return<<" ";
            }
        }
        else if(this->person_arr[i]->Id=="teacher")
        {
            ofs<<this->person_arr[i]->Name<<" "
            <<this->person_arr[i]->Number<<" "
            <<this->person_arr[i]->Academy<<" "
            <<this->person_arr[i]->Title<<" "
            <<this->person_arr[i]->Count<<" "
            <<this->person_arr[i]->Borrow_Count<<" ";
            ofs<<this->person_arr[i]->borrow_record.size()<<" ";
            for(int k=0;k<this->person_arr[i]->borrow_record.size();k++)
            {
                ofs<<this->person_arr[i]->borrow_record[k]->Name<<" "
                <<this->person_arr[i]->borrow_record[k]->Number<<" "
                <<this->person_arr[i]->borrow_record[k]->Author<<" "
                <<this->person_arr[i]->borrow_record[k]->Publicer<<" "
                <<this->person_arr[i]->borrow_record[k]->Price<<" "
                <<this->person_arr[i]->borrow_record[k]->Count<<" "
                <<this->person_arr[i]->borrow_record[k]->is_Return<<" ";
            }
            ofs<<this->person_arr[i]->return_record.size()<<" ";
            for(int k=0;k<this->person_arr[i]->return_record.size();k++)
            {
                ofs<<this->person_arr[i]->return_record[k]->Name<<" "
                <<this->person_arr[i]->return_record[k]->Number<<" "
                <<this->person_arr[i]->return_record[k]->Author<<" "
                <<this->person_arr[i]->return_record[k]->Publicer<<" "
                <<this->person_arr[i]->return_record[k]->Price<<" "
                <<this->person_arr[i]->return_record[k]->Count<<" "
                <<this->person_arr[i]->return_record[k]->is_Return<<" ";
            }
        }
        else if(this->person_arr[i]->Id=="administrator")
        {
            ofs<<this->person_arr[i]->Name<<" "
            <<this->person_arr[i]->Number<<" ";
        }
        ofs<<endl;
        
    }
    ofs.close();

    ofstream ofs_book;
    ofs.open(BookFileName,ios_base::out);
    for(int i=0;i<this->book_count;i++)
    {
        ofs<<"book"<<" ";
        ofs<<this->book_arr[i]->Number<<" "
           <<this->book_arr[i]->Name<<" "
           <<this->book_arr[i]->Author<<" "
           <<this->book_arr[i]->Publicer<<" "
           <<this->book_arr[i]->Price<<" "
           <<this->book_arr[i]->Count<<" ";
        ofs<<endl;
    }
    ofs.close();
}

int Manager::Get_Person_Num()
{
    ifstream ifs;
    ifs.open(PersonFileName,ios::in);
    string Id;
    int num=0;
    while(!ifs.eof())
    {
        ifs>>Id;
        if(Id=="student" || Id=="teacher" || Id=="administrator")
            num++;
    }
    ifs.close();
    return num;
}
int Manager::Get_Book_Num()
{
    ifstream ifs;
    ifs.open(BookFileName,ios::in);
    string ch;
    int num=0;
    while(!ifs.eof())
    {
        ifs>>ch;
        if(ch=="book")
            num++;
    }
    ifs.close();
    return num;
}
void Manager::Init_Person()
{

    ifstream ifs;
    ifs.open(PersonFileName,ios::in);
    string id;string name;string number;string academy;string title;int count;int borrow_count;
    int index=0;
    string ch;
    while(!ifs.eof())
    {
        ifs>>ch;
        if(ch=="student")
        {
            
            ifs>>name>>number>>academy>>count>>borrow_count;
            Person *p=new Student(name,number,academy,count,borrow_count);
            int record_book_num=0;
            ifs>>record_book_num;
            vector<Book*> borrow_record_list;
            for(int i=0;i<record_book_num;i++)
            {
                string book_name;string book_number;string author;string publicer;int price;int book_count;bool is_return;
                ifs>>book_name>>book_number>>author>>publicer>>price>>book_count>>is_return;
                Book* book=new Book(book_number,book_name,author,publicer,price,book_count,is_return);
                borrow_record_list.push_back(book);
            }
            ifs>>record_book_num;
            vector<Book*> return_record_list;
            for(int i=0;i<record_book_num;i++)
            {
                string book_name;string book_number;string author;string publicer;int price;int book_count;bool is_return;
                ifs>>book_name>>book_number>>author>>publicer>>price>>book_count>>is_return;
                Book* book=new Book(book_number,book_name,author,publicer,price,book_count,is_return);
                return_record_list.push_back(book);
            }
            p->borrow_record=borrow_record_list;
            p->return_record=return_record_list;
            this->person_arr[index]=p;
            index++;

        }
        else if(ch=="teacher")
        {
            ifs>>name>>number>>academy>>title>>count>>borrow_count;
            Person *p=new Teacher(name,number,academy,title,count,borrow_count);
            int record_book_num=0;
            ifs>>record_book_num;
            vector<Book*> borrow_record_list;
            for(int i=0;i<record_book_num;i++)
            {
                string book_name;string book_number;string author;string publicer;int price;int book_count;bool is_return;
                ifs>>book_name>>book_number>>author>>publicer>>price>>book_count>>is_return;
                Book* book=new Book(book_number,book_name,author,publicer,price,book_count,is_return);
                borrow_record_list.push_back(book);
            }
            ifs>>record_book_num;
            vector<Book*> return_record_list;
            for(int i=0;i<record_book_num;i++)
            {
                string book_name;string book_number;string author;string publicer;int price;int book_count;bool is_return;
                ifs>>book_name>>book_number>>author>>publicer>>price>>book_count>>is_return;
                Book* book=new Book(book_number,book_name,author,publicer,price,book_count,is_return);
                borrow_record_list.push_back(book);
            }
            p->borrow_record=borrow_record_list;
            p->return_record=return_record_list;
            this->person_arr[index]=p;
            index++;

        }
        else if(ch=="administrator")
        {
            ifs>>name>>number;
            Person *p=new Administrator(name,number);
            this->person_arr[index]=p;
            index++;
        }
    }
}
void Manager::Init_Book()
{
    ifstream ifs;
    ifs.open(BookFileName,ios::in);
    string name;string number;string author;string publicer;int price;int count;
    int index=0;
    string ch;
    while(!ifs.eof())
    {
        ifs>>ch;
        if(ch=="book")
        {
            
            ifs>>number>>name>>author>>publicer>>price>>count;
            Book *b=new Book(number,name,author,publicer,price,count);
            this->book_arr[index]=b;
            index++;
        }
    }
}
Manager::Manager(/* args */)
{

    this->book_arr=NULL;
    this->book_count=0;

    ifstream ifs;
    ifs.open(PersonFileName,ios::in);
    if(!ifs.is_open())
    {
        cout<<"文件不存在"<<endl;
        this->person_count=0;
        this->person_arr=NULL;
        this->book_arr=NULL;
        this->book_count=0;
        this->fileisEmpty=true;
        ifs.close();
        return;
    }
    char ch;
    ifs>>ch;
    if(ifs.eof())
    {
        // cout<<"文件为空!"<<endl;
        this->person_count=0;
        this->person_arr=NULL;
        this->book_arr=NULL;
        this->book_count=0;
        this->fileisEmpty=true;
        ifs.close();
        return;
    }
    int num=this->Get_Person_Num();
    this->person_count=num;
    this->person_arr=new Person*[this->person_count];
    Init_Person();
    int book_num=this->Get_Book_Num();
    this->book_count=book_num;
    this->book_arr=new Book*[this->book_count];
    Init_Book();
    
}

Manager::~Manager()
{
}