//
// Created by Nafany on 07.04.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "item.h"
#include "input.h"

Item* createItem(){
    Item* item = (Item*)calloc(sizeof(Item), 1);
    printf("Введите информацию об объекте: ");
    item->info = get_String();
    return item;
}

void printInfo(Item* a){
    SetConsoleOutputCP(CP_UTF8);
    printf("\tИнформация: %s\n", a->info);
}