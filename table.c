//
// Created by Nafany on 07.04.2021.
//


#include "table.h"

Table* createTable(){
    Table* table = (Table*)calloc(sizeof(Table), 1);
    table->keySpace1 = makeKeySpace1(&table->maxsize1);
    return table;
}

void findByKey1(Table* table){
    KeySpace1* newKeySpace1 = getAllKeys(table->keySpace1, table->maxsize1);
    if(newKeySpace1 != NULL){
        free(newKeySpace1);
    }
}

void deleteByKeys(Table* table){
    freeByKey1(table->keySpace1, table->maxsize1);
}

void printTable(Table* table){
    printKeySpace1(table->keySpace1, table->maxsize1);
}

void addTable(Table* table){
    addKeySpace1(table->keySpace1, table->maxsize1);
}

void freeTable(Table* table){
    freeKeySpace1(table->keySpace1, table->maxsize1);
    free(table);
    printf("Таблица успешно очищена!\n");
}