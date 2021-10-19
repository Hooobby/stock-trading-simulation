//
// Created by Hobby on 2021/10/14.
//

//#include <fstream>
#include <queue>
#include "client.h"
#include "database.h"

Client::Client(string &password) {
    int id;
    Login(id,password);
    ID = id;
    PASSWORD = password;
    BALANCE = 200000;
}