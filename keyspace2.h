//
// Created by Nafany on 07.04.2021.
//

#ifndef LAB3_KEYSPACE2_H
#define LAB3_KEYSPACE2_H

#include "item.h"

#define BUSY -1
#define FREE 0
#define DELETED 1
#define MAXSTRING 4

typedef struct KeySpace2 KeySpace2;

struct KeySpace2{
    int busy;
    char* key; // *Не более 4 элементов!
    Item* info;
};

KeySpace2* makeKeySpace2(int);
KeySpace2* copyKeySpace2(KeySpace2*, Node1*, Node1*, int);
int hash1(char*);
int hash2(char*);
int getIndex(char*, int, int);
Item* addNewKeySpace2(KeySpace2*, int, char*, char*);
void addItemKeySpace2(Item*, KeySpace2*, int);
Item* findByKey2(KeySpace2*, char*, int);
void deleteByKey(KeySpace2*, KeySpace1*, char*, int, int*);
void printKeySpace2(KeySpace2*, int);

#endif //LAB3_KEYSPACE2_H
