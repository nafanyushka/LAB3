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

Item* addKeySpace1(KeySpace1* keySpace1, int maxsize){
    printf("Введите ключ для первого пространства (целое число, не равное нулю): ");
    int key;
    do{
        key = getInt();
    }while(key == 0);
    int index = hashFunc(key, maxsize);
    KeySpace1* keySpace = keySpace1 + index;
    if(keySpace->node != NULL && keySpace->key != key){
        printf("Отказано в доступе: данный индекс уже занят другим ключом.\n");
        return NULL;
    }
    keySpace->key = key;
    if(keySpace->node == NULL){
        keySpace->node = (Node1*)malloc(sizeof(Node1));
        Node1* node = keySpace->node;
        node->item = createItem();
        node->release = 1;
        node->next = NULL;
        node->item->key1 = keySpace;
        node->item->node1 = node;
        return node->item;
    }
    Node1* list = (Node1*)malloc(sizeof(Node1));
    list->item = createItem();
    list->item->key1 = keySpace;
    int release = keySpace->node->release;
    list->next = keySpace->node;
    list->release = release  + 1;
    keySpace->node = list;
    list->item->node1 = list;
    return list->item;
}

int addItemKeySpace1(Item* item1, KeySpace1* keySpace1, int maxsize) {
    printf("Введите ключ для первого пространства (целое число, не равное нулю): ");
    int key;
    do{
        key = getInt();
    }while(key == 0);
    int index = hashFunc(key, maxsize);
    KeySpace1* keySpace = keySpace1 + index;
    if(keySpace->node != NULL && keySpace->key != key){
        printf("Отказано в доступе: данный индекс уже занят другим ключом.\n");
        return -1;
    }
    keySpace->key = key;
    if(keySpace->node == NULL){
        keySpace->node = (Node1*)malloc(sizeof(Node1));
        Node1* node = keySpace->node;
        node->item = item1;
        node->release = 1;
        node->next = NULL;
        node->item->key1 = keySpace;
        node->item->node1 = node;
        return 1;
    }
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

KeySpace1* getAllKeys(KeySpace1* keySpace1, int maxsize){
    printf("Введите ключ: ");
    int key = getInt();
    int index = hashFunc(key, maxsize);
    if(keySpace1[index].node == NULL){
        printf("Тут пусто!\n");
        return NULL;
    }
    if(keySpace1[index].key != key){
        printf("Введенный ключ не найден. В данной ячейке лежат объекты с ключом %d.\n", keySpace1[index].key);
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
    printf("Найдено %d элемент/а/ов, введите номер версии, которая вам необходима, либо 0, чтобы вывести все: ",
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
        if(releaseForDelete == amountItems){
            keySpace1[index].node = keySpace1[index].node->next;
            freeItem(nodeForDelete->item);
            free(nodeForDelete);
            return;
        }
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
        printf("\tИнформация: \"%s\" (вер. %d, ключ второго пространства: %s).",
               nodePrint->item->info, nodePrint->release, nodePrint->item->key2->key);
        nodePrint = nodePrint->next;
    }
    printf(".\n");
}

void printKeySpace1(KeySpace1* keySpace1, int maxsize1){
    KeySpace1* keySpacePrint1 = keySpace1;
    for(int i = 0; i < maxsize1; i++, keySpacePrint1++){
        if(keySpacePrint1->key == 0 || keySpacePrint1->node == NULL)
            printf("%d.\n", i + 1);
        else {
            printf("%d.\tКлюч первого пространства: %d.", i + 1, keySpacePrint1->key);
            printNode(keySpacePrint1->node);
        }
    }
}

void deleteOneKeySpace1(Item* item){
    KeySpace1* pointHelper = item->key1;
    Node1* pointerNode = pointHelper->node;
    if(pointerNode->item == item){
        pointHelper->node = pointerNode->next;
        free(item);
        return;
    }
    while(pointerNode->next->item != item){
        pointerNode->release--;
        pointerNode = pointerNode->next;
    }
    pointerNode->next = pointerNode->next->next;
    (pointerNode->release)--;
    free(pointerNode->next);
    free(item);
}

void deleteAllItems1(KeySpace1* keySpace1, KeySpace2* keySpace2, int key, int maxsize1, int maxsize2){
    int index = hashFunc(key,maxsize1);
    if(keySpace1[index].node == NULL){
        printf("Такому ключу соответвтсвует уже пустая область.\n");
        return;
    }
    KeySpace1* keyHelper1 = &keySpace1[index];
    while(keyHelper1->node != NULL)
        deleteByKey(keySpace2, keyHelper1->node->item->key2->key, maxsize2);
}
