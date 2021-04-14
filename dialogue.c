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
               "Введите 3, чтобы получить объект по ключу второго пространства.\n"
               "Введите 4, чтобы получить объект по составному ключу.\n"
               "Введите 5, чтобы вывести всю таблицу в стиле первого пространства.\n"
               "Введите 6, чтобы вывести таблицу в стиле второго пространства ключей.\n"
               "Введите 7, чтобы удалить элемент(ы) по первому ключу.\n"
               "Введите 8, чтобы удалить элемент по второму ключу.\n"
               "Введите 9, чтобы удалить заданный составным ключом элемент.\n"
               "Иначе программа закончит выполнение.\n"
               "Ваш выбор: ");
        choose = getInt();
        char* line;
        printf("\n");
        int key1;
        char* info,* key2;
        switch(choose){
            case 1:
                printf("Введите первый ключ: ");
                key1 = getInt();
                do{
                    printf("Введите второй ключ (до 4 символов): ");
                    key2 = get_String();
                }while(strlen(key2) < 1);
                if(strlen(key2) > 4){
                    printf("До 4 символов же!\n");
                    break;
                }
                do {
                    printf("Введите информацию об объекте: ");
                    info = get_String();
                }while(strlen(info) < 1);

                if(addTableComplex(table, table->keySpace1, table->keySpace2, key1, key2, info) == -1)
                    printf("Не удалось добавить элемент в таблицу.\n");
                break;
            case 2:
                printf("Введите ключ для первого пространства: ");
                key1 = getInt();
                newTable = findByKey_1(table, key1);
                if(newTable == NULL){
                    break;
                }
                if(miniDialogue(newTable, key1) == 0)
                    printf("Работа с подтаблицей успешно закончена!\n");
                freeTable(newTable);
                free(newTable);
                break;
            case 3:
                do {
                    printf("Введите ключ второго простанства (не больше 4 символов): ");
                    line = get_String();
                }while(strlen(line) < 1);
                if(strlen(line) > 4) {
                    printf("Ошибка: вы ввели слишком длинную строку.\n");
                    free(line);
                    break;
                }
                Item* item1 = findByKey_2(table, line, choose);
                if(item1 != NULL) {
                    printf("\tИнформация: %s.\tКлюч первого пространства: %d.\tКлюч второго пространства: %s.\n",
                           item1->info, item1->key_1, item1->key_2);
                    freeItem(item1);
                }
                else
                    printf("Не удалось найти объекта с таким ключом.\n");
                free(line);
                break;
            case 4:
                printf("Введите ключ первого пространства: ");
                key1 = getInt();
                do {
                    printf("Введите ключ второго пространства (не больше 4 символов): ");
                    key2 = get_String();
                }while(strlen(key2) < 1);
                if(strlen(key2) > 4){
                    printf("Ну я же просил не больше 4...");
                    free(key2);
                    break;
                }
                Item* item = findByKey_2(table, key2, choose);
                if(item == NULL) {
                    free(key2);
                    break;
                }
                if(item->key_1 == key1) {
                    printf("\tИнформация: %s.\tКлюч первого пространства: %d.\tКлюч второго пространства: %s.\n",
                           item->info, item->key_1, item->key_2);
                    freeItem(item);
                }
                else {
                    printf("Объект с таким ключом не найден!\n");
                    freeItem(item);
                }
                free(key2);
                break;
            case 5:
                printTable(table);
                break;
            case 6:
                printByKeySpace2(table);
                break;
            case 7:
                //
                printf("Введите ключ для первого пространства: ");
                key1 = getInt();
                deleteByKey1(table, key1);
                break;
            case 8:
                //
                do{
                    printf("Введите ключ для второго пространства (не более 4 символов): ");
                    key2 = get_String();
                }while(strlen(key2) < 1);
                if(strlen(key2) > 4){
                    printf("Я же просил, не более четырех...");
                    free(key2);
                    break;
                }
                deleteByKey2(table, key2);
                free(key2);
                break;
            case 9:
                printf("Введите ключ первого пространства: ");
                key1 = getInt();
                do{
                    printf("Введите ключ второго пространства (не больше 4 символов): ");
                    key2 = get_String();
                }while(strlen(key2) < 1);
                if(strlen(key2) > 4){
                    printf("Я же просил не больше 4...\n");
                    free(key2);
                    break;
                }
                deleteByKeys(table, key1, key2);
                free(key2);
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

int miniDialogue(Table* miniTable, int key1){
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
        char* key2;
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
                deleteByKey1(miniTable, key1);
                break;
            case 3:
                do{
                    printf("Введите ключ второго пространства (не больше 4 символов): ");
                    key2 = get_String();
                }while(strlen(key2) < 1);
                if(strlen(key2) > 4){
                    printf("Я же просил не более 4...\n");
                    break;
                }
                deleteByKey2(miniTable, key2);
                break;
            case 4:
                do{
                    printf("Введите ключ второго пространства (не больше 4 символов): ");
                    key2 = get_String();
                }while(strlen(key2) < 1);
                if(strlen(key2) > 4){
                    printf("Я же просил не более 4...\n");
                    break;
                }
                deleteByKeys(miniTable, key1, key2);
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