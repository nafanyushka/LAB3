#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#include "input.h"
#include "table.h"
#include "keyspace1.h"
#include "keyspace2.h"
#include "item.h"

int main() {
//    setlocale(LC_ALL, "Rus");
    SetConsoleOutputCP(CP_UTF8);
    int maxsize1, maxsize2, choose;
//    Item* a = createItem();
//    printInfo(a);
    KeySpace1* keySpace1 = makeKeySpace1(&maxsize1);
    do{
        addKeySpace1(keySpace1, maxsize1);
        printf("Чтобы добавить элемент в 1 пространство ключей, введите любое число, кроме 0 (выйти - 0): ");
        choose = getInt();
    }while(choose != 0);
    printf("\nВывод таблицы.\n\n");
    do{
        KeySpace1* newKeySpace1 = getAllKeys(keySpace1, maxsize1);
        printf("Чтобы вывести элементы из 1 пространство ключей, введите любое число, кроме 0 (выйти - 0): ");
        choose = getInt();
    }while(choose != 0);

    system("pause");
    return 0;
}

