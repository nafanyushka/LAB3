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

Item* createItem(char* info){
    Item* item = (Item*)calloc(sizeof(Item), 1);
    item->info = info;
    return item;
}

void printInfo(Item* a){
    SetConsoleOutputCP(CP_UTF8);
    printf("\tИнформация: %s.\tКлюч первого пространства: %d.\tКлюч второго пространства: %s.\n", a->info, a->key1->key,
           a->key2->key);
}

void freeItem(Item* item){
    free(item->info);
    if(item->key_2 != NULL)
        free(item->key_2);
    free(item);
}

Item* copyItem(Item* item){
    if(item == NULL)
        return NULL;
    Item* newItem = (Item*)malloc(sizeof(Item));
    newItem->info = item->info;
    newItem->key1 = item->key1;
    newItem->key2 = item->key2;
    newItem->node1 = item->node1;
    return newItem;
}

Item* copyItemInfo(Item* item){
    if(item == NULL)
        return NULL;
    Item* newItem = (Item*)calloc(sizeof(Item), 1);
    newItem->info = (char*)malloc(sizeof(char*) * strlen(item->info));
    newItem->key_1 = item->key1->key;
    newItem->key_2 = (char*)malloc(sizeof(char) * strlen(item->key2->key));
    char* key2helper = newItem->key_2;
    char* helper = item->key2->key;
    while(*helper != '\0'){
        *key2helper = *helper;
        key2helper++;
        helper++;
    }
    *key2helper = '\0';
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