/*
    Модернизируйте модель чата из задания 15.4.2 так, чтобы логин и хеш от пароля теперь хранились в хеш-таблице. 
    То есть логин является ключом, хеш — значением, а вместе они составляются пару. 
    Хеш-функцию для хеш-таблицы составьте методом умножения. Хеш-таблицу реализуйте методом квадратичного пробирования.
*/


#include "main.h"

using namespace std;


int main(int argc, char* argv[]) {
    Chat ch1;
    string userName = "";
    string userPass = "";
    cout << "Введите 0 чтобы закончить регистрацию пользователей." << endl;
    while(1) {
        cout << "Введите имя пользователя\n";
        getline(cin, userName);
        if (userName == "0") break;
        
        cout << "Введите пароль\n";
        getline(cin, userPass);
        if (userPass == "0") break;
        ch1.reg(userName, userPass);

        ch1.show();
    }

    cout << "Введите 0 чтобы закончить проверку регистрации пользователей." << endl;
    while(1) {
        cout << "Введите имя пользователя\n";
        getline(cin, userName);
        if (userName == "0") break;

        cout << "Введите пароль\n";    
        getline(cin, userPass);
        if (userPass == "0") break;        

        if(ch1.login(userName, userPass)) cout << "User " << userName << " enter to chat." << endl;
        else cout << "User " << userName << " not exist." << endl;
    }

    return 0;
}