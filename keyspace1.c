//
// Created by Nafany on 07.04.2021.
//

#include "keyspace1.h"
#include "item.h"
#include "input.h"

KeySpace1* makeKeySpace1(int* maxsize) {
    printf("Введите размер первого пространства ключей: ");
    int maxsize1 = getInt();
    KeySpace1* newKeySpace1 = (KeySpace1*)calloc(sizeof(KeySpace1), maxsize1);
    *maxsize = maxsize1;
    return newKeySpace1;
}

int hashFunc(int key, int maxsize){
    return key%maxsize;
}

void addKeySpace1(KeySpace1* keySpace1, int maxsize){
    printf("Введите ключ для первого пространства (целое число, не равное нулю): ");
    int key;
    do{
        key = getInt();
    }while(key == 0);
    int index = hashFunc(key, maxsize);
    if(keySpace1[index].node != NULL && keySpace1[index].key != key){
        printf("Отказано в доступе: данный индекс уже занят другим ключом.\n");
        return;
    }
    keySpace1[index].key = key;
    if(keySpace1[index].node == NULL){
        keySpace1[index].node = (Node1*)malloc(sizeof(Node1));
        Node1* node = keySpace1[index].node;
        node->item = createItem();
        node->release = 1;
        node->next = NULL;
        return;
    }
    Node1* list = (Node1*)malloc(sizeof(Node1));
    list->item = createItem();
    int release = keySpace1[index].node->release;
    list->next = keySpace1[index].node;
    list->release = release  + 1;
    keySpace1[index].node = list;
}

KeySpace1* getAllKeys(KeySpace1* keySpace1, int maxsize){
    printf("Введите ключ: ");
    int key = getInt();
    int index = hashFunc(key, maxsize);
    if(keySpace1[index].node == NULL){
        printf("Тут пусто!\n");
        return NULL;
    }
    if(keySpace1[index].key != key){
        printf("Введенный ключ не найден.\n");
        return NULL;
    }
    Node1* list = keySpace1[index].node;
    int newMaxSize = list->release;
    KeySpace1* newKeySpace1 = (KeySpace1*)malloc(sizeof(KeySpace1) * newMaxSize);
    int newIndexSize = newMaxSize;
    while(list != NULL){
        newIndexSize--;
        newKeySpace1[newIndexSize].key = newIndexSize;
        newKeySpace1[newIndexSize].node = (Node1*)malloc(sizeof(Node1));
        newKeySpace1[newIndexSize].node->item = list->item;
        list = list->next;
    }
    printf("Найдено %d элемент(ов), введите номер версии, которая вам необходима, либо 0, чтобы вывести все: ",
           newMaxSize);
    int newIndex;
    do {
        newIndex = getInt();
    }while(!(0 <= newIndex && newIndex <= newMaxSize));
    if(newIndex == 0){
        for(int item = 0; item < newMaxSize; item++){
            printf("%d элемент.", item + 1);
            printInfo(newKeySpace1[item].node->item);
        }
    }
    else {
        printf("%d элемент.", newIndex);
        printInfo(newKeySpace1[newIndex - 1].node->item);
    }
    return newKeySpace1;
}