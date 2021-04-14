//
// Created by Nafany on 07.04.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "item.h"
#include "keyspace1.h"
#include "keyspace2.h"
#include "input.h"

Item* createItem(){
    Item* item = (Item*)calloc(sizeof(Item), 1);
    printf("Введите информацию об объекте: ");
    item->info = get_String();
    return item;
}

void printInfo(Item* a){
    SetConsoleOutputCP(CP_UTF8);
    printf("\tИнформация: %s.\tКлюч первого пространства: %d.\tКлюч второго пространства: %s.\n", a->info, a->key1->key,
           a->key2->key);
}

void freeItem(Item* item){
    free(item->info);
    free(item);
}

Item* copyItem(Item* item){
    Item* newItem = (Item*)malloc(sizeof(Item));
    newItem->info = item->info;
    newItem->key1 = item->key1;
    newItem->key2 = item->key2;
    newItem->node1 = item->node1;
    return newItem;
}

Item* copyItemInfo(Item* item){
    Item* newItem = (Item*)calloc(sizeof(Item), 1);
    newItem->info = (char*)malloc(sizeof(char*) * strlen(item->info));
    char* paster = newItem->info;
    char* copier = item->info;
    while(*copier != '\0'){
        (*paster) = (*copier);
        paster++;
        copier++;
    }
    *paster = '\0';
    return newItem;
}