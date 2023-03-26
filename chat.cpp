/*
    Чат с регистрацией и хранением паролей взашифрованном виде
*/

#include "chat.h"

Chat::Chat() {
    
    ht = new HashTable();
}

Chat::~Chat() {
    cout << "Chat deleted" << endl;
    delete ht;
}

// регистрация нового пользователя
void Chat::reg(string& login, string& pass) {
    if(!ht->find(login, pass)) ht->add(login, pass);
    else cout << "This user already registered." << endl;
}
// вход в чат
bool Chat::login(string& login, string& pass) {

    return ht->find(login, pass);
}

void Chat::show()
{
    ht->show();
}
