#include "Book.h"
Book::Book(string number,string name,string author,string publicer,int price,int count,bool is_return)
{
    this->Number=number;
    this->Name=name;
    this->Author=author;
    this->Publicer=publicer;
    this->Price=price;
    this->Count=count;
    this->is_Return=is_return;
}
Book::Book(Book &obj)
{
    this->Number=obj.Number;
    this->Name=obj.Name;
    this->Author=obj.Author;
    this->Publicer=obj.Publicer;
    this->Price=obj.Price;
    this->Count=obj.Count;
    this->is_Return=obj.is_Return;
}

Book::~Book()
{
}

