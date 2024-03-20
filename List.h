// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa4
// --------------------------------------------------------------

#ifndef LIST_H_
#define LIST_H_

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef void* ListElement;

typedef struct ListObj* List;

List newList(void);

void freeList(List* pL);

int length(List L);

int index(List L);

ListElement front(List L);

ListElement back(List L);

ListElement get(List L);

void clear(List L);

void set(List L, ListElement);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, ListElement);

void append(List L, ListElement);

void insertBefore(List L, ListElement);

void insertAfter(List L, ListElement);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

void printList(FILE* out, List L);

#endif
