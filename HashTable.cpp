/*
    Хеш таблица SHA-1
    Индекс в массиве вычисляется на основе метода умножения и квадратичное пробирование
*/

#include "HashTable.h"

HashTable::HashTable() {
    _count = 0;
    _mem_size = 8;
    _array = new Pair [_mem_size]{Pair()};
}

HashTable::~HashTable() {
    delete[] _array;
}

int HashTable::getCount(){
    return this->_count;
}


// хеш-функция возвращает хеш(сумму всех char) userName
int HashTable::hfunc(string& userName) {
    int sum = 0;
    for(int i = 0; i < userName.length(); i++) {
        sum += userName[i];
    }
    return sum;
}

// сравнение хешей SHA-1 160bit
bool HashTable::hashCompare(uint *first, uint *second)
{
    for (size_t i = 0; i < 5; i++)
    {
        if(first[i] != second[i]) return false;
    }
    
    return true;
}

// хеш-функция реализующая метод умножения и квадратичное пробирование(по ключу выдаёт индекс)
int HashTable::hash_index(string& userName, int offset)
{
    int val = hfunc(userName);
    const double A = 0.7;
    const int M = 10;
    int buf = int(M * (A * (val + offset*offset) - int(A * (val + offset*offset))));
    return buf;
}

// добавление элементов в новый массив после resize
void HashTable::add(string& userName, uint* userPassHash) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for(;i < _mem_size; i++) {
        index = hash_index(userName, i);
        if(_array[index]._status != enPairStatus::engaged) { 
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }

    // если нет места, увеличиваем таблицу в два раза
    if(index >= _mem_size) {
        resize();
        add(userName, userPassHash);
        return;
    }
    // заполняем Pair
    _array[index]._userName = userName;
    _array[index]._userPassHash = new uint[5];
    for (size_t i = 0; i < 5; i++)
    {
        _array[index]._userPassHash[i] = userPassHash[i];
    }    
    _array[index]._status = enPairStatus::engaged;
    _count++;
}

// добавление нового юзера
void HashTable::add(string &userName, string &userPass) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for(;i < _mem_size; i++) {
        index = hash_index(userName, i);
        if(_array[index]._status != enPairStatus::engaged) { 
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }
    // если нет места, увеличиваем таблицу в два раза
    if(index >= _mem_size) {
        resize();
        add(userName, userPass);
        return;
    }
    // кладем в свободную ячейку пару
    _array[index] = Pair(userName, userPass);
    _count++;
}

// удаление юзера
void HashTable::del(string& userName, string& userPass) {
    for(int i = 0;i < _mem_size; i++) {
        int index = hash_index(userName, i);
        Pair& pair = _array[index];
        if(pair._status == enPairStatus::engaged && hashCompare(pair._userPassHash, sha1(userPass.data(), userPass.size())) && pair._userName == userName) { 
            // найдено
            pair._status = deleted;
            --_count;
            return;                                         // если нашёл, то помечаю удалённой
        } else {                                            // БЕЗ else БУДЕТ ИСКАТЬ ДО КОНЦА ВСЕХ ДАННЫХ!!!
            if(pair._status == enPairStatus::free)          // если нашёл пустую то нет такого ключа. Завершаю
                return;                                     
        }
    }
}

bool HashTable::find(string& userName, string& userPass) {    
    for(int i = 0;i < _mem_size; i++) {
        int index = hash_index(userName, i);
        Pair& pair = _array[index];
        if(pair._status == enPairStatus::engaged && hashCompare(pair._userPassHash, sha1(userPass.data(), userPass.size())) && pair._userName == userName) { 
            // найдено
            return true;
        } else {                                            // БЕЗ else БУДЕТ ИСКАТЬ ДО КОНЦА ВСЕХ ДАННЫХ!!!
            // не найдено
            if(pair._status == enPairStatus::free) return false;
        }
    }
    return false;
}

// увеличение в два раза массива хеш таблицы (при нехватке места)
void HashTable::resize() {
    Pair* save_ct = _array;                  // запоминаем старый массив
    int oldSize = _mem_size;

    _mem_size *= 2;
    _count = 0;
    _array = new Pair[_mem_size]{Pair()};
    
    for(int i = 0; i < oldSize; i++) {      // цикл по элементам массива(объекты Pair)
        // перебираем все старые цепочки
        Pair& current = save_ct[i];
        if(current._status == engaged)
            add(current._userName, current._userPassHash);     // добавляем элементы
    }

    // чистим за собой
    delete[] save_ct;
}

// вывод в терминал всех пользователей
void HashTable::show(){
    for (size_t i = 0; i < _mem_size; i++)
    {
        if(_array[i]._status == enPairStatus::engaged) {
            cout << i << "\tUser name: " << _array[i]._userName << " \n\tUser hash: ";

            for (size_t j = 0; j < 5; j++) { 
                cout << _array[i]._userPassHash[j] << " "; 
            }
            cout << endl;
        }
        else cout << i << " no user \n";
    }
}