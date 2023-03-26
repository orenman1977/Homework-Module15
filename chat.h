/*
    Чат с регистрацией и хранением паролей взашифрованном виде
*/

#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "sha1.h"
#include "HashTable.h"

class Chat {
public:
    Chat();
    ~Chat();
    void reg(string& _login, string& _pass);
    bool login(string& _login, string& _pass);
    void show();
    
private:
    HashTable* ht;
};