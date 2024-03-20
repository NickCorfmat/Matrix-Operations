// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa4
// --------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

int main(int argc, char* argv[]) {
	List A = newList();
	List B = newList();
	List C = newList();

	int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int u = -1, v = -2, w = -3;

	// INITIALIZE Lists.
	for (int i = 1; i <= 20; i++) {
		append(A, &X[i]);
		prepend(B, &X[i]);
	}

	for (moveFront(A); index(A) >= 0; moveNext(A)) {
		printf("%d ", *(int*)get(A));
	}
	printf("\n");

	for (moveFront(B); index(B) >= 0; moveNext(B)) {
                printf("%d ", *(int*)get(B));
	}
	printf("\n");

	printf("Length A: %d\n", length(A));
	printf("Length B: %d\n", length(B));
	printf("\n");

	printf("Index A: %d\n", index(A));
	printf("Index B: %d\n", index(B));
	printf("\n");

	for (int i = 0; i < 5; i++) {
		deleteFront(A);
	}

	for (int i = 0; i < 5; i++) {
		deleteBack(B);
	}

	for (moveFront(A); index(A) >= 0; moveNext(A)) {
                printf("%d ", *(int*)get(A));
        }
        printf("\n");

        for (moveFront(B); index(B) >= 0; moveNext(B)) {
                printf("%d ", *(int*)get(B));
        }
        printf("\n\n");

	printf("Front A: %d\n", *(int*)front(A));
	printf("Front B: %d\n", *(int*)front(B));
	printf("\n");

	printf("Back A: %d\n", *(int*)back(A));
        printf("Back B: %d\n", *(int*)back(B));
        printf("\n");

	append(C, &u);
	moveFront(C);
	insertBefore(C, &v);
	insertAfter(C, &w);

	for (moveFront(C); index(C) >= 0; moveNext(C)) {
                printf("%d ", *(int*)get(C));
        }
        printf("\n\n");

	moveFront(C);
	set(C, &w);

	for (moveFront(C); index(C) >= 0; moveNext(C)) {
                printf("%d ", *(int*)get(C));
        }
        printf("\n\n");

	moveFront(C);
	delete(C);
	moveFront(C);

	insertBefore(C, &u);
	insertBefore(C, &v);
	prepend(C, &w);
	append(C, &v);
	append(C, &w);
	moveBack(C);
	insertAfter(C, &u);
	deleteFront(C);
	deleteFront(C);
	deleteBack(C);
	moveFront(C);
	insertAfter(C, &w);

	printf("Length C: %d\n", length(C));
	printf("Index C: %d\n\n", index(C));

	for (moveFront(C); index(C) >= 0; moveNext(C)) {
		printf("Get C from front: %d\n", *(int*)get(C));
	}
	printf("\n");

	for (moveBack(C); index(C) >= 0; movePrev(C)) {
		printf("Get C from back: %d\n", *(int*)get(C));
	}
	printf("\n");

	for (moveFront(C); index(C) >= 0; moveNext(C)) {
		delete(C);
		moveFront(C);
	}

	for (moveFront(A); index(A) >= 0; moveNext(A)) {
		append(C, get(A));
	}

	for (moveFront(C); index(C) >= 0; moveNext(C)) {
		printf("%d ", *(int*)get(C));
	}
	printf("\n\n");

	moveFront(B);
	for (int i = 0; i < 5; i++) moveNext(B);
	printf("Index B: %d\n", index(B));
	insertBefore(B, &w);
	for (int i = index(B); i < length(B); i++) moveNext(B);
        printf("Index B: %d\n", index(B));

	freeList(&A);
	freeList(&B);
	freeList(&C);

	return 0;
}
