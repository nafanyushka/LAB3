#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>

#include "dialogue.h"

/* TODO:
 *  Разделение на диалоговые и бекендовые.
 *  Поиски добавить в диалоги.
 *  Пофиксить удаление по ключам.
 */

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int maxSize1, maxSize2;

    do{
        printf("Введите размер 1 пространства ключей: ");
        maxSize1 = getInt();
    }while(maxSize1 <= 0);

    do{
        printf("Введите размер 2 пространства ключей: ");
        maxSize2 = getInt();
    }while(maxSize2 <= 0);

    Table* table = createTable(maxSize1, maxSize2);

    int isGood = dialogue(table);

    if(isGood == 0)
        printf("Диалог успешно закончен.\n");

    sleep(1);
    printf("Вы решили выйти из таблицы.\n");
    sleep(1);
    system("cls");
    freeTable(table);
    free(table);
    printf("Выход.");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".");
    sleep(1);
    return 0;
}