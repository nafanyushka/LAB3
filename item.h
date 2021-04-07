//
// Created by Nafany on 07.04.2021.
//

#ifndef LAB3_ITEM_H
#define LAB3_ITEM_H

typedef struct Item Item;
typedef struct KeySpace1 KeySpace1;
typedef struct KeySpace2 KeySpace2;

struct Item{
    char* info;
    KeySpace1* key1;
    KeySpace2* key2;
};

Item* createItem();
void printInfo(Item*);

#endif //LAB3_ITEM_H
