#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>

#include "input.h"
#include "table.h"
#include "keyspace1.h"
#include "keyspace2.h"
#include "item.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int choose;
    Table* table = createTable();

    do{
        printf("\n"
               "Введите 1, чтобы добавить элемент в таблицу.\n"
               "Введите 2, чтобы получить определенную версию предмета из первого пространства ключей.\n"
               "Введите 3, чтобы вывести всю таблицу в стиле первого пространства.\n"
               "Введите 4, чтобы вывести таблицу в стиле второго пространства ключей.\n"
               "Введите 5, чтобы удалить элемент(ы) по первому ключу.\n"
               "Введите 6, чтобы удалить элемент по второму ключу.\n"
               "Введите 7, чтобы удалить заданный составным ключом элемент.\n"
               "Иначе программа закончит выполнение. Ваш выбор:\t");
        choose = getInt();
        printf("\n");
        KeySpace1* newKeySpace1 = NULL;
        int maxHelpSize;
        switch(choose){
            case 1:
                addTableComplex(table, table->keySpace1, table->keySpace2);
                break;
            case 2:
                findByKey1(table);
                break;
            case 3:
                printTable(table);
                break;
            case 4:
                printByKeySpace2(table);
                break;
            case 5:
                deleteByKey1(table);
                break;
            case 6:
                deleteByKey2(table);
                break;
            case 7:
                deleteByKeys(table);
                break;
            default:
                choose = 0;
                break;
        }
    }while(choose != 0);
    sleep(1);
    printf("Вы решили выйти из таблицы.\n");
    sleep(1);
    system("cls");
    freeTable(table);
    printf("Выход.");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".");
    sleep(1);
    return 0;
}