/*
    Хеш таблица на основе пробирования
*/

//TODO do member "show"
#pragma once

#include <iostream>
#include <string>
#include "sha1.h"
using namespace std;

class HashTable {                   // хеш-таблица
    public:    
        HashTable();
        ~HashTable();
        
        void add(string& userName, string& userPass);
        void del(string& userName, string& userPass);
        bool find(string& userName, string& userPass);
        void show();

        int getCount();
        
    private:    
        enum enPairStatus {
            free,               // свободен
            engaged,            // занят
            deleted             // удален
        };
    
        struct Pair {           // пара ключ-значение            
            Pair():             // конструктор по умолчанию
                _userName("username"), 
                _userPassHash(nullptr),
                _status(free) 
                {}

            Pair(string& userName, string& userPass):
                _status(engaged),
                _userName(userName)
            { 
                _userPassHash = sha1(userPass.data(), userPass.size());
            }

            ~Pair() 
            { 
                if(_userPassHash != nullptr) delete[] _userPassHash;
            }

            Pair& operator = (const Pair& other) {      //  оператор присваивания
                // need copy of array uint[5]
                if(_userPassHash == nullptr) _userPassHash = new uint[5]{};

                for (size_t i = 0; i < 5; i++)
                {
                    _userPassHash[i] =  other._userPassHash[i];
                }                
                _userName = other._userName;
                _status = other._status;
                return *this;
            };
            
            string _userName;       // имя (ключ)
            uint* _userPassHash;    // хеш пароля (значение)            
            enPairStatus _status;   // состояние ячейки
        };
    
        int hash_index(string& val, int offset);        // возвращает индекс в массиве
        void resize();
        void add(string& userName, uint* userPassHash); // добавление после resize
        int hfunc(string& str);                         // возвращает хеш ключа
        bool hashCompare(uint* first, uint* second);    // сравнение хешей

        Pair* _array;
        int _mem_size;
        int _count;
};