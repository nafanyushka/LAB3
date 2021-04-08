#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <unistd.h>

#include "input.h"
#include "table.h"
#include "keyspace1.h"
#include "keyspace2.h"
#include "item.h"

int main() {
//    setlocale(LC_ALL, "Rus");
    SetConsoleOutputCP(CP_UTF8);
    int maxsize1, maxsize2, choose = 0;
//    Item* a = createItem();
//    printInfo(a);
    KeySpace1* keySpace1 = makeKeySpace1(&maxsize1);
    do{
        printf("Введите 1, чтобы добавить элемент в таблицу.\nВведите 2, чтобы вывести содержимое.\nВведите 3, чтобы"
               " удалить элемент(ы).\nИначе программа закончит выполнение. Ваш выбор:\t");
        choose = getInt();
        KeySpace1* newKeySpace1 = NULL;
        int maxHelpSize;
        switch(choose){
            case 1:
                addKeySpace1(keySpace1, maxsize1);
                break;
            case 2:
                newKeySpace1 = getAllKeys(keySpace1, maxsize1);
                if(newKeySpace1 != NULL){
                    free(newKeySpace1);
                }break;
            case 3:
                freeByKey1(keySpace1, maxsize1);
                break;
            default:
                choose = 0;
        }
    }while(choose != 0);
    system("cls");
    printf("Выход.");
    sleep(1);
    system("cls");
    printf("Выход..");
    sleep(1);
    system("cls");
    printf("Выход...");
    sleep(1);
    return 0;
}

