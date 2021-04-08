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
    SetConsoleOutputCP(CP_UTF8);

    int choose;
    Table* table = createTable();

    do{
        printf("\nВведите 1, чтобы добавить элемент в таблицу.\nВведите 2, чтобы вывести содержимое.\nВведите 3, чтобы"
               " удалить элемент(ы).\nВведите 4, чтобы вывести всю таблицу.\n"
               "Иначе программа закончит выполнение. Ваш выбор:\t");
        choose = getInt();
        printf("\n");
        KeySpace1* newKeySpace1 = NULL;
        int maxHelpSize;
        switch(choose){
            case 1:
                addTable(table);
                break;
            case 2:
                findByKey1(table);
                break;
            case 3:
                deleteByKeys(table);
                break;
            case 4:
                printTable(table);
                break;
            default:
                choose = 0;
                break;
        }
    }while(choose != 0);
    system("cls");
    freeTable(table);
    sleep(3);
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

