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
    KeySpace1* newKeySpace1 = (KeySpace1*)calloc(sizeof(KeySpace1), newMaxSize);
    int newIndexSize = newMaxSize;
    while(list != NULL){
        newIndexSize--;
        newKeySpace1[newIndexSize].key = newIndexSize;
        newKeySpace1[newIndexSize].node = (Node1*)malloc(sizeof(Node1));
        newKeySpace1[newIndexSize].node->item = list->item;
        newKeySpace1[newIndexSize].node->next = NULL;
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

void freeByKey1(KeySpace1* keySpace1, int maxsize1){
    printf("Введите ключ: ");
    int key = getInt();
    int index = hashFunc(key, maxsize1);
    if(keySpace1[index].node == NULL){
        printf("Тут уже пусто!\n");
        return;
    }
    if(keySpace1[index].key != key){
        printf("Введенный ключ не найден.\n");
        return;
    }
    int amountItems = keySpace1[index].node->release;
    int choose;
    printf("Удалить все элементы или только один? Введите 1 если только один элемент, 0 если все: ");
    do{
        choose = getInt();
    }while(!(0 <= choose && choose  <= 1));
    if(choose == 1){
        int releaseForDelete;
        printf("Какую верисю удалить?\n");
        do{
            releaseForDelete = getInt();
        }while(!(1 <= releaseForDelete && releaseForDelete <= amountItems));

        Node1* nodeForDelete = keySpace1[index].node, * helperForDelete = keySpace1[index].node;
        while(nodeForDelete->release != releaseForDelete){
            helperForDelete = nodeForDelete;
            helperForDelete->release--;
            nodeForDelete = nodeForDelete->next;
        }

        helperForDelete->next = nodeForDelete->next;
        freeItem(nodeForDelete->item);
        free(nodeForDelete);
    }
    else{
        Node1* nodeForDelete, * helperForDelete = keySpace1[index].node;
        keySpace1[index].node = NULL;
        while(helperForDelete != NULL){
            nodeForDelete = helperForDelete;
            helperForDelete = helperForDelete->next;
            freeItem(nodeForDelete->item);
            free(nodeForDelete);
        }
    }
}

void freeKeySpace1(KeySpace1* keySpace1, int maxsize1){
    for(int i = 0; i < maxsize1; i++){
        if(keySpace1[i].node != NULL){
            freeNode(keySpace1[i].node);
        }
    }
    free(keySpace1);
}

void freeNode(Node1* node){
    Node1 *helper = node;
    while(helper != NULL){
        node = helper;
        helper = helper->next;
        freeItem(node->item);
        free(node);
    }
}