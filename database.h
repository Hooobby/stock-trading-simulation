//
// Created by Hobby on 2021/10/8.
//

#ifndef STOCK_DATABASE_H
#define STOCK_DATABASE_H

#include <mysql.h>
#include <iostream>
#include <string>
using namespace std;

string plusone(string str);
string minusone(string str);
bool query(string sql);
bool ConnectMysql();//连接数据库
bool QueryDatabase(string sql);//查询并输出结果
bool GetMarketprice(string code, double &ret);
void OutputMysql();//输出查询结果
bool UpdateData(string sql);//插入删除修改操作
bool NewCustomer(int id);
void FreeConnect();//释放资源
void Gettodayall();//更新数据库信息
bool Signup(int &ID,const string password);
bool Logoff(const int ID);
int Login(const int ID,const string password);
bool Logout();

#endif //STOCK_DATABASE_H
