//
// Created by Hobby on 2021/10/12.
//
#include "database.h"
#include <mysql.h>
#include <cstdio>
#include <sstream>
using namespace std;

MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW column;

string plusone(string str){
    stringstream ss;
    string ret;
    int a;
    ss<<str;
    ss>>a;
    ss.clear();
    ss<<(a+1);ss>>ret;
    return ret;
}

string minusone(string str){
    stringstream ss;
    string ret;
    int a;
    ss<<str;
    ss>>a;
    ss.clear();
    ss<<(a-1);ss>>ret;
    return ret;
}

bool query(string sql){
    if(mysql_query(&mysql, sql.c_str())){
        cout << "Failed ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    }
    if(!(res = mysql_store_result(&mysql))){
        cout << "Couldn't get result from " + (string) mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}

bool ConnectMysql()
{
    mysql_init(&mysql);//初始化mysql
    if (!(mysql_real_connect(&mysql,
                             "localhost",//主机
                             "root",//用户名
                             "921332",//密码
                             "stock",//数据库名 必须是已经存在的 我的mysql大小写不敏感
                             3306,//端口号 默认的0或者3306
                             NULL, 0//最后两个参数的常用写法 几乎都是这两个
    ))) {
        cout << "Error connecting to database:" + (string) mysql_error(&mysql) << endl;
        return false;
    } else {
        cout << "Connected" << endl;
        return true;
    }
}

bool UpdateData(string sql){
    mysql_query(&mysql,"set names utf8");
    if(mysql_query(&mysql, sql.c_str())){
        cout << "Update failed ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    }else{
        cout << "Update success." << endl;
        return true;
    }
}

bool QueryDatabase(string sql){
    if(mysql_query(&mysql, sql.c_str())){
        cout << "Query failed ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    }else{
        cout << "Query success." << endl;
    }
    if(!(res = mysql_store_result(&mysql))){
        cout << "Couldn't get result from " + (string) mysql_error(&mysql) << endl;
        return false;
    }
    OutputMysql();
    return true;
}

bool GetMarketprice(string code,double &ret){
    string sql = "SELECT * from today_all WHERE code = ";
    sql += code;sql += ";";

    if(mysql_query(&mysql, sql.c_str())){
        cout << "Failed ( " + (string) mysql_error(&mysql) + " )" << endl;
        return false;
    }else{
        cout << "Success." << endl;
    }
    if(!(res = mysql_store_result(&mysql))){
        cout << "Couldn't get result from " + (string) mysql_error(&mysql) << endl;
        return false;
    }
    column = mysql_fetch_row(res);
    ret = atof(column[3]);
    return true;
}

bool Login(int &ID,string password){
    //寻找可用ID：
    string sql = "SELECT * FROM available_id;";
    if(!query(sql))return false;
    int start,nums;
    if(column = mysql_fetch_row(res)){
        start = atoi(column[0]);
        nums = atoi(column[1]);
        ID = start;
        if(nums == 1){
            sql = "DELETE FROM available_id WHERE start = ";
            sql += column[0];
            sql += ";";
        }else{
            sql = "UPDATE available_id SET start = ";
            string tmp;
            tmp = plusone(column[0]);
            sql += tmp;sql += ",nums = ";
            tmp = minusone(column[1]);
            sql += tmp;sql += " WHERE start = ";
            sql += column[0];sql += ";";
        }
    }else{
        cout<<"No available ID"<<endl;
        return false;
    }
    if(!UpdateData(sql))return false;

    //更新密码库：
    sql = "INSERT INTO password (client_id,password) VALUES (";
    sql += column[0]; sql += ",";
    sql += password; sql+=");";
    if(!UpdateData(sql))return false;
    cout << "Password updated" <<endl;
    //初始化用户信息：
    sql = "INSERT INTO client (client_id,funds,available_funds,pick_up,market_val,total_val,profit) VALUES (";
    sql += column[0]; sql +=",";
    sql += "200000,200000,0,0,200000,0);";
    if(!UpdateData(sql))return false;

    return true;
}

bool Logout(int ID){
    int flg = 0;
    string sql = "SELECT * FROM available_id WHERE start > ";
    stringstream ss;
    string id;
    ss<<ID;ss>>id;
    sql += id;
    sql += " ORDER BY start;";
    if(!query(sql))return false;
    int start,nums;
    if(column = mysql_fetch_row(res)){
        start = atoi(column[0]);
        nums = atoi(column[1]);
        if(start == ID + 1){
            flg = 1;
            string tmp;
            sql = "UPDATE available_id SET start = ";
            tmp = minusone(column[0]);
            sql += tmp;sql += ",nums = ";
            tmp = plusone(column[1]);
            sql += tmp;sql += " WHERE start = ";
            sql += column[0];sql += ";";
            if(!UpdateData(sql))return false;
        }
    }

    sql = "SELECT * FROM available_id WHERE start < ";
    sql += id;
    sql += " ORDER BY start DESC;";
    query(sql);
    if(column = mysql_fetch_row(res)){
        start = atoi(column[0]);
        nums = atoi(column[1]);
        if(start + nums + 1 == ID){
            flg = 1;
            sql = "UPDATE available_id SET start = ";
            sql += column[0];sql += ",nums = ";
            string tmp;
            tmp = plusone(column[1]);
            sql += tmp;sql += " WHERE start = ";
            sql += column[0];sql += ";";
            if(!UpdateData(sql))return false;
        }
    }
    if(!flg){
        sql = "INSERT INTO available_id (start,nums) VALUE (";
        sql += id;
        sql += ",1);";
        if(!UpdateData(sql)) return false;
    }
    cout << "Return id success" << endl;
    //从密码库中删去信息：
    sql = "DELETE FROM password WHERE client_id = ";
    sql += id; sql += ";";
    if(!UpdateData(sql))return false;
    //从用户信息库中删去信息：
    sql = "DELETE FROM client WHERE client_id = ";
    sql += id; sql +=";";
    if(!UpdateData(sql))return false;
    cout << "Logout success" << endl;
}

void OutputMysql(){
    cout << "Number of dataline returned: " << mysql_affected_rows(&mysql) << endl;
    char *field[32];

    int num = mysql_num_fields(res);
    for(int i = 0; i < num; ++i) {
        field[i] = mysql_fetch_field(res)->name;
    }
    for(int i = 0; i < num; ++i) {
        cout << (string) field[i] <<"    ";
    }
    cout << endl;
    while(column = mysql_fetch_row(res)){
        for(int i = 0; i < num; ++i){
            cout << column[i] << "    ";
        }
        cout << endl;
        //cout << "debug: "<< column[3] << endl;
    }
}

void Gettodayall(){
    ConnectMysql();
    UpdateData("truncate today_all;");
    system("python C:\\Users\\Hobby\\CLionProjects\\Stock\\mysql.py");
    QueryDatabase("select * from today_all;");
}
void FreeConnect(){
    mysql_free_result(res);
    mysql_close(&mysql);
}
