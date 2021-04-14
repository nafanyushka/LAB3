//
// Created by Nafany on 07.04.2021.
//


#include <string.h>
#include "table.h"
#include "input.h"

Table* createTable(int maxsize1, int maxsize2){
    Table* table = (Table*)calloc(sizeof(Table), 1);
    table->maxsize1 = maxsize1;
    table->maxsize2 = maxsize2;
    table->keySpace1 = makeKeySpace1(maxsize1);
    table->keySpace2 = makeKeySpace2(maxsize2);
    table->nsize1 = 0;
    return table;
}

void findByKey1(Table* table){
    Table* newTable = (Table*)malloc(sizeof(Table));
    KeySpace1* newKeySpace1 = getAllKeys(table->keySpace1, table->maxsize1, table->nsize1);
    if(newKeySpace1 != NULL){
        free(newKeySpace1);
        return;
    }
    newTable->keySpace1 = newKeySpace1;
}

void deleteByKeys(Table* table, int key1, char* key2){
    Item* item = findByKey_2(table, key2, 0);
    if(item == NULL) {
        return;
    }
    if(item->key1->key == key1)
        deleteByKey(table->keySpace2, table->keySpace1, key2, table->maxsize2, &table->nsize1);
    else {
        printf("Не найдено элемента с таким составным ключом!\n");
    }
    free(item); //Обычная очистка, так как это скопированный элемент и в нем ссылка на ту же инфу что и в оригинале.
}

void deleteByKey1(Table* table, int key1){
    freeByKey1(table->keySpace1, table->keySpace2, table->maxsize1, table->maxsize2, &table->nsize1, key1);
}

void deleteByKey2(Table* table, char* key2){
    deleteByKey(table->keySpace2, table->keySpace1, key2, table->maxsize2, &table->nsize1);
}

void printTable(Table* table){
    printKeySpace1(table->keySpace1, table->nsize1);
}

void printByKeySpace2(Table* table){
    printKeySpace2(table->keySpace2, table->maxsize2);
}

void freeTable(Table* table){
    freeKeySpace1(table->keySpace1, table->nsize1);
    free(table->keySpace2);
    free(table);
    printf("Таблица успешно очищена!\n");
}

int addTableComplex(Table* table, KeySpace1* keySpace1, KeySpace2* keySpace2, int key1, char* key2, char* info){
    Item* item = addNewKeySpace2(keySpace2, table->maxsize2, key2, info);
    if(item == NULL)
        return -1;
    if(addItemKeySpace1(item, keySpace1, table->maxsize1, &table->nsize1, key1) == -1){
        item->key2->busy = DELETED;
        free(item);
        return -1;
    }
    return 0;
}
Item* findByKey_2(Table* table, char* key, int choose){
    Item* item = findByKey2(table->keySpace2, key, table->maxsize2);
    if(item == NULL){
        return NULL;
    }
//    printf("Информация найденного объекта: \"%s\". Ключ первого поля: %d (в. %d). Ключ второго поля: %s\n", item->info,
//           item->key1->key, item->node1->release, item->key2->key);
    Item* newItem;
    if(choose == 8 || choose == 9)
        return copyItemInfo(item);
    else
        newItem = item;
    return newItem;
}

Table* findByKey_1(Table* table, int key){
    Table* newTable = (Table*)calloc(sizeof(Table), 1);
    Node1* newNode = NULL;
    Node1* oldNode = NULL;
    printf("Введите ключ первого пространства: ");
    newTable->maxsize1 = 1;
    newTable->keySpace1 = getAllKeys_1(table->keySpace1, key, table->nsize1, newNode, &oldNode, &newTable->maxsize2);
    if(newTable->keySpace1 == NULL) {
        printf("Ошибка: введеный ключ не найден!\n");
        return NULL;
    }
    newNode = newTable->keySpace1->node;
    newTable->nsize1 = 1;
    newTable->keySpace2 = copyKeySpace2(table->keySpace2, oldNode, newNode, newTable->maxsize2);
    return newTable;
}