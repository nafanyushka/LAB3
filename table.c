//
// Created by Nafany on 07.04.2021.
//


#include <string.h>
#include "table.h"
#include "input.h"

Table* createTable(){
    Table* table = (Table*)calloc(sizeof(Table), 1);
    table->keySpace1 = makeKeySpace1(&table->maxsize1);
    table->keySpace2 = makeKeySpace2(&table->maxsize2);
    return table;
}

void findByKey1(Table* table){
    KeySpace1* newKeySpace1 = getAllKeys(table->keySpace1, table->maxsize1);
    if(newKeySpace1 != NULL){
        free(newKeySpace1);
    }
}

void deleteByKeys(Table* table){
    printf("Введите первый ключ: ");
    int key1 = getInt();
    char* key2;
    do{
        printf("Введите второй ключ: ");
        key2 = get_String();
    }while(strlen(key2) > 4 || *key2 == '\0');
    Item* item = findByKey_2(table, key2);
    if(item->key1->key == key1)
        deleteByKey(table->keySpace2, key2, table->maxsize2);
    else
        printf("Не найдено элемента с таким составным ключом!\n");
    free(item); //Обычная очистка, так как это скопированный элемент и в нем ссылка на ту же инфу что и в оригинале.
}

void deleteByKey1(Table* table){
    printf("Введите ключ первого пространства ключей: ");
    deleteAllItems1(table->keySpace1, table->keySpace2, getInt(), table->maxsize1, table->maxsize2);
}

void deleteByKey2(Table* table){
    char* key2;
    do{
        printf("Введите второй ключ: ");
        key2 = get_String();
    }while(strlen(key2) > 4 || *key2 == '\0');
    deleteByKey(table->keySpace2, key2, table->maxsize2);
}

void printTable(Table* table){
    printKeySpace1(table->keySpace1, table->maxsize1);
}

void printByKeySpace2(Table* table){
    printKeySpace2(table->keySpace2, table->maxsize2);
}

void addTable(Table* table){
    addKeySpace1(table->keySpace1, table->maxsize1);
}

void freeTable(Table* table){
    freeKeySpace1(table->keySpace1, table->maxsize1);
    free(table->keySpace2);
    free(table);
    printf("Таблица успешно очищена!\n");
}

void addTableComplex(Table* table, KeySpace1* keySpace1, KeySpace2* keySpace2){
    Item* item = addNewKeySpace2(keySpace2, table->maxsize2);
    if(item == NULL)
        return;
    if(addItemKeySpace1(item, keySpace1, table->maxsize1) == -1){
        printf("Ошибка!\n");
        item->key2->busy = DELETED;
        free(item);
        return;
    };
}
Item* findByKey_2(Table* table, char* key){
    Item* item = findByKey2(table->keySpace2, key, table->maxsize2);
    printf("Информация найденного объекта: \"%s\". Ключ первого поля: %d (в. %d). Ключ второго поля: %s\n", item->info,
           item->key1->key, item->node1->release, item->key2->key);
    Item* newItem = copyItem(item);
    return newItem;
}