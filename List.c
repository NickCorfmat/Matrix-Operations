// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa4
// --------------------------------------------------------------

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "List.h"

// BEGIN code from Patrick Tantalo.

typedef struct NodeObj* Node;

typedef struct NodeObj {
	ListElement data;
	Node next;
        Node prev;
} NodeObj;

// END code from Patrick Tantalo.

typedef struct ListObj {
	Node front;
        Node back;
        Node cursor;
	int index;
	int length;
} ListObj;

Node newNode(ListElement data) {

	// ALLOCATES memory for the Node variable.
	Node N = malloc(sizeof(NodeObj));

	assert(N != NULL);

	// ASSIGN the default values of the Node.
	N->data = data;
	N->next = NULL;
	N->prev = NULL;

	return N;
}

List newList(void) {

	// ALLOCATES memory for the List variable.
	List L = malloc(sizeof(ListObj));

	assert(L != NULL);

	// ASSIGN the default values of the List.
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->index = -1;
	L->length = 0;

	return L;
}

void freeNode(Node* pN) {

	// FREES memory used by the Node object.
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

void freeList(List* pL) {

	// FREES memory used by the List object.
	if (pL != NULL && *pL != NULL) {
		while((*pL)->back != NULL) {
			deleteBack(*pL);
		}

		free(*pL);
		*pL = NULL;
	}
}

int length(List L) {
	if (L == NULL) {
		fprintf(stderr, "Error: calling length() on NULL List object.\n");
		exit(EXIT_FAILURE);
	}

	return L->length;
}

int index(List L) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling index() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	if (L->index < 0) {
		return -1;
	}

	return L->index;
}

ListElement front(List L) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling front() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	if (L->length <= 0) {
		fprintf(stderr, "Error: calling front() on empty list.\n");
                exit(EXIT_FAILURE);
	}
	
	return L->front->data;
}

ListElement back(List L) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling back() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	if (L->length <= 0) {
                fprintf(stderr, "Error: calling back() on empty list.\n");
                exit(EXIT_FAILURE);
        }

        return L->back->data;
}

ListElement get(List L) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling get() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	if (L->length <= 0 || L->index < 0) {
                fprintf(stderr, "Error: calling get() on invalid List.\n");
                exit(EXIT_FAILURE);
        }

	return L->cursor->data;
}

void clear(List L) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling clear() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	while(L->back != NULL) {
		deleteBack(L);
	}

	L->index = -1;
}

void set(List L, ListElement E) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling set() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	if (L->length <= 0 || L->index < 0) {
		fprintf(stderr, "Error: calling set() on invalid List object.\n");
                exit(EXIT_FAILURE);
	}

	L->cursor->data = E;
}

void moveFront(List L) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling moveFront() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	if (L->length == 0) { // Check if List is empty
		L->index = -1;
	} else {
		L->index = 0;
		L->cursor = L->front;
	}
}

void moveBack(List L) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling moveBack() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	if (L->length == 0) { // Check if List is empty
                L->index = -1;
        } else {
                L->index = L->length - 1;
                L->cursor = L->back;
        }
}

void movePrev(List L) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling movePrev() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	if (L->cursor != NULL) { // Checks if cursor is defined
		if (L->index != 0) { // Checks if cursor is not at front
			L->index -= 1;
			L->cursor = L->cursor->prev;
		} else {
			L->index = -1;
			L->cursor = NULL;
		}
	}
}

void moveNext(List L) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling moveNext() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	if (L->cursor != NULL) { // Checks if cursor is defined
                if (L->index != L->length - 1) { // Checks if cursor is not at back
                        L->index += 1;
			L->cursor = L->cursor->next;
                } else {
                        L->index = -1;
                        L->cursor = NULL;
                }
        }
}

void prepend(List L, ListElement E) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling prepend() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	Node N = newNode(E);

	if (L->front != NULL) { // Check if front is defined
		L->front->prev = N;
		N->next = L->front;
		L->front = N;

	} else {
		L->front = N;
		L->back = N;
	}

	if (L->index >= 0) { 
		L->index += 1;
	}
	
	L->length += 1;
}

void append(List L, ListElement E) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling append() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	Node N = newNode(E);

        if (L->length > 0) { // check if List is non-empty
                L->back->next = N;
		N->prev = L->back;
		L->back = N;
        } else {
                L->front = N;
                L->back = N;
        }

	L->length += 1;
}

void insertBefore(List L, ListElement E) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling insertBefore() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	if (L->length <= 0 || L->index < 0) {
		fprintf(stderr, "Error: calling insertBefore() on invalid List.\n");
                exit(EXIT_FAILURE);
	}

	Node N = newNode(E);

	if (L->cursor == L->front) {
		L->front->prev = N;
		N->next = L->front;
                L->front = N;
        } else {

		L->cursor->prev->next = N;
		N->prev = L->cursor->prev;
        	L->cursor->prev = N;
        	N->next = L->cursor;
	}

	L->length += 1;
	L->index += 1;
}

void insertAfter(List L, ListElement E) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling insertAfter() on NULL List object.\n");
                exit(EXIT_FAILURE);
	}

	if (L->length <= 0 || L->index < 0) {
                fprintf(stderr, "Error: calling insertAfter() on invalid List.\n");
                exit(EXIT_FAILURE);
        }

        Node N = newNode(E);

	if (L->cursor == L->back) { // Check if cursor is at the back
		L->back->next = N;
		N->prev = L->back;
		L->back = N;
	} else {
		L->cursor->next->prev = N;
		N->next = L->cursor->next;
		L->cursor->next = N;
		N->prev = L->cursor;
	}

	L->length += 1;;
}

void deleteFront(List L) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling deleteFront() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	if (L->length <= 0) {
                fprintf(stderr, "Error: calling deleteFront() on empty List.\n");
                exit(EXIT_FAILURE);
	}

	Node N = L->front;
	L->front = L->front->next;

	if (N == L->cursor) { // Check if cursor is at front
                L->index = -1;
                L->cursor = NULL;
        }

        if (L->length == 1) { // Check if List contains only one element
                L->back = NULL;
		L->index -= 1;
        } else {
                N->next->prev = NULL;
                L->index -= 1;
	}

        freeNode(&N);
        L->length -= 1;
}

void deleteBack(List L) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling deleteBack() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	if (L->length <= 0) {
                fprintf(stderr, "Error: calling deleteBack() on empty List object.\n");
                exit(EXIT_FAILURE);
	}

	Node N = L->back;
        L->back = L->back->prev;

        if (N == L->cursor) { // Check if cursor is at back
                L->index = -1;
                L->cursor = NULL;
        }

        if (L->length == 1) { // Check if List contains only one element
                L->front = NULL;
        } else {
                N->prev->next = NULL;
        }

        freeNode(&N);
        L->length -= 1;
}

void delete(List L) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling delete() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	if (L->length <= 0 || L->index < 0) {
		fprintf(stderr, "Error: calling delete() on invalid List object.\n");
                exit(EXIT_FAILURE);
	}

	Node N = L->cursor;

	if (N == L->front) {
		L->front = L->front->next;

        	if (L->length == 1) { // Check if List contains only one element
                	L->back = NULL;
                	L->index -= 1;
        	} else {
                	N->next->prev = NULL;
                	L->index -= 1;
        	}
	} else if (N == L->back) {
		L->back = L->back->prev;

        	if (L->length == 1) { // Check if List contains only one element
                	L->front = NULL;
                	L->index -= 1;
        	} else {
                	N->prev->next = NULL;
                	L->index -= 1;
		}

	} else {
		N->prev->next = N->next;
		N->next->prev = N->prev;
	}

	freeNode(&N);
	L->cursor = NULL;
	L->index = -1;
	L->length -= 1;
}

void printList(FILE* out, List L) {
	if (L == NULL) {
                fprintf(stderr, "Error: calling printList() on NULL List object.\n");
                exit(EXIT_FAILURE);
        }

	Node N = L->front;

	while (N != NULL) {
		fprintf(out, "%d%s", *(int*)N->data, N==L->back?"":" ");
		N = N->next;
	}

	fprintf(out, "\n");
}
