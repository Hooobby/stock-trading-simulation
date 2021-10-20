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
    //int id;
    //Signup(id,"123456");
    //Login(10000,"123456");
    //Logoff(10000);
    FreeConnect();
    return 0;
}