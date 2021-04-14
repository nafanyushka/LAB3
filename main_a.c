#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>

#include "dialogue.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Table* table = createTable();

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