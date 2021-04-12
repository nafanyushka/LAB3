//
// Created by Nafany on 07.04.2021.
//

#include "keyspace1.h"
#include "keyspace2.h"
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

Item* addKeySpace1(KeySpace1* keySpace1, int maxsize, int* nsize1){
    KeySpace1* keySpace = keySpace1;
    int key;
    do{
        printf("Введите ключ для первого пространства (целое число, не равное нулю): ");
        key = getInt();
    }while(key == 0);
    for(int index = 0; index < *nsize1; index++, keySpace++){
        if(keySpace->key == key){
            Node1* list = (Node1*)malloc(sizeof(Node1));
            list->item = createItem();
            list->item->key1 = keySpace;
            int release = keySpace->node->release;
            list->next = keySpace->node;
            list->release = release  + 1;
            keySpace->node = list;
            list->item->node1 = list;
            *nsize1++;
            return list->item;
        }
    }
    if(*nsize1 == maxsize){
        printf("Отказано в доступе: в таблице не оказалось места для элемента.\n");
        return NULL;
    }
    keySpace->key = key;
//    if(keySpace->node == NULL){
        keySpace->node = (Node1*)malloc(sizeof(Node1));
        Node1* node = keySpace->node;
        node->item = createItem();
        node->release = 1;
        node->next = NULL;
        node->item->key1 = keySpace;
        node->item->node1 = node;
        *nsize1++;
        return node->item;
//    }
//    Node1* list = (Node1*)malloc(sizeof(Node1));
//    list->item = createItem();
//    list->item->key1 = keySpace;
//    int release = keySpace->node->release;
//    list->next = keySpace->node;
//    list->release = release  + 1;
//    keySpace->node = list;
//    list->item->node1 = list;
//    *nsize1++;
//    return list->item;
}

int addItemKeySpace1(Item* item1, KeySpace1* keySpace1, int maxsize, int* nsize1) {
//    printf("Введите ключ для первого пространства (целое число, не равное нулю): ");
//    int key;
//    do{
//        key = getInt();
//    }while(key == 0);
//    int index = hashFunc(key, maxsize);
//    KeySpace1* keySpace = keySpace1 + index;
//    if(keySpace->node != NULL && keySpace->key != key){
//        printf("Отказано в доступе: данный индекс уже занят другим ключом.\n");
//        return -1;
//    }
//    keySpace->key = key;
//    if(keySpace->node == NULL){
//        keySpace->node = (Node1*)malloc(sizeof(Node1));
//        Node1* node = keySpace->node;
//        node->item = item1;
//        node->release = 1;
//        node->next = NULL;
//        node->item->key1 = keySpace;
//        node->item->node1 = node;
//        return 1;
//    }
//    Node1* list = (Node1*)malloc(sizeof(Node1));
//    list->item = item1;
//    list->item->key1 = keySpace;
//    int release = keySpace->node->release;
//    list->next = keySpace->node;
//    list->release = release  + 1;
//    keySpace->node = list;
//    list->item->node1 = list;
//    return 1;
    KeySpace1* keySpace = keySpace1;
    int key;
    do{
        printf("Введите ключ для первого пространства (целое число, не равное нулю): ");
        key = getInt();
    }while(key == 0);
    for(int index = 0; index < *nsize1; index++, keySpace++){
        if(keySpace->key == key){
            Node1* list = (Node1*)malloc(sizeof(Node1));
            list->item = item1;
            list->item->key1 = keySpace;
            int release = keySpace->node->release;
            list->next = keySpace->node;
            list->release = release  + 1;
            keySpace->node = list;
            list->item->node1 = list;
            return 1;
        }
    }
    if(*nsize1 == maxsize){
        printf("Отказано в доступе: в таблице не оказалось места для элемента.\n");
        return -1;
    }
    keySpace->key = key;
//    if(keySpace->node == NULL){
    keySpace->node = (Node1*)malloc(sizeof(Node1));
    Node1* node = keySpace->node;
    node->item = item1;
    node->release = 1;
    node->next = NULL;
    node->item->key1 = keySpace;
    node->item->node1 = node;
    (*nsize1)++;
    return 1;
}

KeySpace1* getAllKeys(KeySpace1* keySpace1, int maxsize, int nsize1){
    printf("Введите ключ: ");
    int key = getInt();
    KeySpace1* keyPointer = keySpace1;
    for(int index = 0; index < nsize1; index++, keyPointer++){
        if(keyPointer->key == key){
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
            printf("Найдено %d элемент/а/ов, введите номер версии, которая вам необходима, либо 0, чтобы вывести все: ",
                   newMaxSize);
            int newIndex;
//            do {
                newIndex = getInt();
//            }while(!(0 <= newIndex && newIndex <= newMaxSize));
            if(newIndex == 0){
                for(int item = 0; item < newMaxSize; item++){
                    printf("%d элемент.", item + 1);
                    printInfo(newKeySpace1[item].node->item);
                }
            }
            if((0 < newIndex && newIndex <= newMaxSize)) {
                printf("%d элемент.", newIndex);
                printInfo(newKeySpace1[newIndex - 1].node->item);
            }
            if(newIndex > newMaxSize){
                printf("Ну не хотите выводить по-хорошему ну и не надо...\n");
                return NULL;
            }
            return newKeySpace1;
            break;
        }
    }
    printf("Ошибка: такой объект не найден!\n");
    return NULL;
}

void freeByKey1(KeySpace1* keySpace1, KeySpace2* keySpace2, int maxsize1, int maxsize2, int* nsize1){
    printf("Введите ключ для первого пространства: ");
    KeySpace1* keyPointer = keySpace1;
    int key = getInt();
    int index = 0;
    for(int i = 0; i < *nsize1; i++, keyPointer++){
        if(keyPointer->key == key){
            index = i;
            break;
        }
        index = i;
    }
    if(*nsize1 == index) {
        printf("Не удалось найти такой ключ!\n");
        return;
    }
    int amountItems = keySpace1[index].node->release;
    int choose;
    do{
        printf("Удалить все элементы или только один? Введите 1 если только один элемент, 0 если все: ");
        choose = getInt();
    }while(!(0 <= choose && choose  <= 1));
    if(choose == 1){
        int releaseForDelete;
        printf("Какую верисю удалить?\nВведите номер версии: ");
        releaseForDelete = getInt();
        if(!(1 <= releaseForDelete && releaseForDelete <= amountItems)){
            printf("Такой версии нет.\n");
            return;
        }
        Node1* nodeForDelete = keySpace1[index].node, * helperForDelete = keySpace1[index].node;
//        if(releaseForDelete == amountItems){
//            keySpace1[index].node = keySpace1[index].node->next;
//            freeItem(nodeForDelete->item);
//            free(nodeForDelete);
//            return;
//        }
        while(nodeForDelete->release != releaseForDelete){
            nodeForDelete = nodeForDelete->next;
        }
        deleteByKey(keySpace2, keySpace1, nodeForDelete->item->key2->key, maxsize2, nsize1);
//
//        helperForDelete->next = nodeForDelete->next;
//        freeItem(nodeForDelete->item);
//        free(nodeForDelete);
    }
    if(keySpace1[index].node == NULL){
        deleteAllItems1(keySpace1, keySpace2, key, maxsize1, maxsize2, nsize1);
        return;
    }
    else{
        deleteAllItems1(keySpace1, keySpace2, key, maxsize1, maxsize2, nsize1);
//        return;
        }
}

void freeKeySpace1(KeySpace1* keySpace1, int nsize){
    for(int i = 0; i < nsize; i++){
        if(keySpace1[i].node != NULL){
            freeNode(keySpace1[i].node);
        }
    }
    free(keySpace1);
    printf("Удаление первого пространства ключей прошло успешно!\n");
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

void printNode(Node1* node1){
    Node1* nodePrint = node1;
    while(nodePrint != NULL){
        printf("\t\tИнформация: \"%s\" (вер. %d, ключ второго пространства: %s).\n",
               nodePrint->item->info, nodePrint->release, nodePrint->item->key2->key);
        nodePrint = nodePrint->next;
    }
}

void printKeySpace1(KeySpace1* keySpace1, int nsize1){
    KeySpace1* keySpacePrint1 = keySpace1;
    printf("\n\n/////////////////////// ТАБЛИЦА. ПРОСТРАНСТВО КЛЮЧЕЙ 1. ///////////////////////\n");
    for(int i = 0; i < nsize1; i++, keySpacePrint1++){
        printf("%d.\tКлюч первого пространства: %d:\n", i + 1, keySpacePrint1->key);
        printNode(keySpacePrint1->node);
    }
    printf("\n\n");
}

void deleteOneKeySpace1(Item* item, KeySpace1* keySpace1, int* nsize1){
    KeySpace1* pointHelper = item->key1;
    Node1* pointerNode = pointHelper->node;
    int key = item->key1->key;
    if(pointerNode->item == item){
        pointHelper->node = pointerNode->next;
        free(item);
    }
    else{
        while (pointerNode->next->item != item) {
            pointerNode->release--;
            pointerNode = pointerNode->next;
        }
        pointerNode->next = pointerNode->next->next;
        (pointerNode->release)--;
        free(item->node1);
        free(item);
    }
    if(pointHelper->node == NULL){
        for(int index = 0; index < *nsize1; index++){
            if(keySpace1[index].key == key){
                push(keySpace1, index, *nsize1);
                (*nsize1)--;
                return;
            }
        }
    }
}

void deleteAllItems1(KeySpace1* keySpace1, KeySpace2* keySpace2, int key, int maxsize1, int maxsize2, int* nsize1){
    KeySpace1* keyPointer = keySpace1;
    int findIndex = 0;
    for(int index = 0; index < *nsize1; index++, keyPointer++){
        if(keyPointer->key == key) {
            findIndex = index;
            while(keyPointer->node != NULL && key == keyPointer->key)
                deleteByKey(keySpace2, keySpace1, keyPointer->node->item->key2->key, maxsize2, nsize1);
//            push(keySpace1, index, *nsize1);
//            (*nsize1)--;
            break;
        }
    }
    if(findIndex == maxsize1){
        printf("Такого ключа не найдено.\n");
        return;
    }
}

void push(KeySpace1* keySpace1, int index, int nsize1){
    KeySpace1* keyPointer = &keySpace1[index];
    KeySpace1* pushKeyPointer = &keySpace1[nsize1 - 1];
    keyPointer->node = pushKeyPointer->node;
    keyPointer->key = pushKeyPointer->key;
    pushKeyPointer->node = NULL;
//    pushKeyPointer->key = 0;
    Node1* helperPoint = keySpace1[index].node;
    while(helperPoint != NULL){
        helperPoint->item->key1 = keyPointer;
        helperPoint = helperPoint->next;
    }
}