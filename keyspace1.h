//
// Created by Nafany on 07.04.2021.
//

#ifndef LAB3_KEYSPACE1_H
#define LAB3_KEYSPACE1_H
#include <stdio.h>
#include <stdlib.h>
#include "item.h"

typedef struct KeySpace1 KeySpace1;
typedef struct Node1 Node1;

struct KeySpace1{
    int key;
    Node1* node;
};

struct Node1{
    int release;
    Item* item;
    Node1* next;
/*TODO:
     * Вставка
     * Удаление
     * Особенное:
     * Поиск в таблице всех версий элемента, заданного ключом, или конкретной (заданной) версии элемента, также
     * заданного своим ключом; результатом поиска должна быть новая таблица, содержащая найденные элементы
     * Удаление из таблицы всех элементов с заданным ключом или элемента определенной версии, также заданного своим
     * ключом
*/
};

KeySpace1* makeKeySpace1(int*);
int hashFunc(int, int);
Item* addKeySpace1(KeySpace1*, int);
int addItemKeySpace1(Item* item, KeySpace1*, int);
KeySpace1* getAllKeys(KeySpace1*, int);
void freeByKey1(KeySpace1*, int);
void freeKeySpace1(KeySpace1*, int);
void freeNode(Node1*);
void printNode(Node1*);
void printKeySpace1(KeySpace1*, int);
void deleteOneKeySpace1(Item*);
void deleteAllItems1(KeySpace1*, KeySpace2*, int, int, int);

#endif //LAB3_KEYSPACE1_H
