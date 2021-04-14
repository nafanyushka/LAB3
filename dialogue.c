//
// Created by Nafany on 13.04.2021.
//

#include "dialogue.h"

int dialogue(Table* table){
    printf("Начинается диалог с новой табилцей!\n");
    int choose, newChoose;

    do{
        Table* newTable = NULL;
        printf("\n"
               "Введите 1, чтобы добавить элемент в таблицу.\n"
               "Введите 2, чтобы получить объекты по ключу первого пространства.\n"
               "Введите 3, чтобы вывести всю таблицу в стиле первого пространства.\n"
               "Введите 4, чтобы вывести таблицу в стиле второго пространства ключей.\n"
               "Введите 5, чтобы удалить элемент(ы) по первому ключу.\n"
               "Введите 6, чтобы удалить элемент по второму ключу.\n"
               "Введите 7, чтобы удалить заданный составным ключом элемент.\n"
               "Иначе программа закончит выполнение. Ваш выбор:\t");
        choose = getInt();
        printf("\n");
        switch(choose){
            case 1:
                addTableComplex(table, table->keySpace1, table->keySpace2);
                break;
            case 2:
                newTable = findByKey_1(table);
                if(newTable == NULL){
                    break;
                }
                if(miniDialogue(newTable) == 0)
                    printf("Работа с подтаблицей успешно закончена!\n");
                freeTable(newTable);
                free(newTable);
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
    system("cls");
    printf("Вы решили выйти из таблицы.\n");
    sleep(1);
    system("cls");
    return 0;
}

int miniDialogue(Table* miniTable){
    printf("\n\tНачинается работа с подтаблицей.\n");
    int choose;
    do{
        printf("\n\tВведите 1, чтобы выбрать, что вывести.\n"
               "\tВведите 2, чтобы удалить элемент(ы) по первому ключу.\n"
               "\tВведите 3, чтобы удалить элемент по второму ключу.\n"
               "\tВведите 4, чтобы удалить элемент по составному ключу.\n"
               "\tВведите любое другое число, чтобы закончить с этим.\n"
               "\tВаш выбор: ");
        int newChoose;
        choose = getInt();
        switch(choose) {
            case 1:
                printf("\n\tВведите 0, чтобы вывести все элементы подтаблицы.\n"
                       "\tВведите 1, чтобы вывести определенную версию элемента подтаблицы.\n"
                       "\tВаш выбор: ");
                newChoose = getInt();
                printf("\n");
                printOneOrAll(miniTable->keySpace1, miniTable->keySpace1->key, miniTable->nsize1, newChoose);
                break;
            case 2:
                deleteByKey1(miniTable);
                break;
            case 3:
                deleteByKey2(miniTable);
                break;
            case 4:
                deleteByKeys(miniTable);
                break;
            default:
                break;
        }
    }while(choose == 1 || choose == 2 || choose == 3 || choose == 4);
    system("cls");
    printf("Вы решили выйти из подтаблицы.\n");
    sleep(1);
    system("cls");
    return 0;
}