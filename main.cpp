#include <iostream>
#include <fstream>
#include <mysql.h>
#include <vector>
#include <string>
#include "stock10.h"
#include "database.h"
//#include <python.h>
using namespace std;

int main()
{
    cout<<"ÄãºÃ"<<endl;
//    Gettodayall();
//    ConnectMysql();
//    string code = "002612";
//    double price;
//    GetMarketprice(code,price);
//    cout<<"debug:"<<price<<endl;
//    FreeConnect();cd
    ConnectMysql();
    int id;
    Login(id,"123456");
    cout<<id<<endl;
    return 0;
}