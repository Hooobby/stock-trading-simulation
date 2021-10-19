//
// Created by Hobby on 2021/10/14.
//

#ifndef STOCK_CUSTOMER_H
#define STOCK_CUSTOMER_H

#include <vector>
#include <string>

using namespace std;
class Client{
private:
    //vector<int> hold;
    int ID;
    string PASSWORD;
    double BALANCE;

public:
    Client(string &password);
    void buy(string code, int num);
    void sell(string code, int num);
    void show();
};
#endif //STOCK_CUSTOMER_H
