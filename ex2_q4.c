// Course: Advanced C programming
// exercise 2, question 4
// file name: ex2_q4.c

// --------------------------- //
// DO NOT CHANGE anything in the following macro:
#ifdef FUNC_DECLARE
#include "ex2_q4.h"
#else
// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define FUNC_DECLARE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf
#define SIZE(a) (sizeof(a) / sizeof((a)[0]))
// --------------------------------------- //
// Types declration section:
// --------------------------------------- //
typedef struct list
{
	int data;
	struct list* next;
} list;
// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //
unsigned long student_id();
list* createElement(int data, list* next);
list* createListFromArray(int* arr, int n);
void printList(list* lst);
void partition(list** lst, list** pivot, list** small, list** big);
void quickSortList(list** lst);
void freeList(list** lst);
// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	unsigned long id_num;
	int n;
	list* lst = NULL;
	int arr[] = { 5, 3, 7, 1, 9, 8, 2, 5, 6 };

	// call functions:
	id_num = student_id();
	printf("[id: %lu] start main\n", id_num);
	lst = createListFromArray(arr, SIZE(arr));
	quickSortList(&lst);

	// write output:
	printf("Output:\n");
	printList(lst);

	// free list:
	freeList(&lst);

	return 0;
}
#endif
// --------------------------- //


// --------------------------- //
// function implementation section:
unsigned long student_id()
{
	// return your id number,
	// for example if your id is 595207432
	// return 595207432;
	// your code:

	return;
}
// --------------------------- //


///// <summary>
///// The function receives a value from type int, 
//// and the pointer to the next element in list
///// and returns a dynamic element from type list  
///// </summary>
///// <param>int data - value from type int, the value of the element</param>
///// <param>list* next - pointer to the next value after the newly created element</param>
///// <returns>dynamic value from type list</returns>
list* createElement(int data, list* next)
{
	list* item = (list*)(malloc(sizeof(list)));
	item->data = data;
	item->next = next;
	return item;
}
// --------------------------- //

/// <summary>
/// The function receives an integer array and its size
/// and returns a newly created list
/// </summary>
/// <param>int* arr - The array</param>
/// <param>int n - Amount of elements in array</param>
/// <returns>newly created list</returns>
list* createListFromArray(int* arr, int n)
{
	int i;
	list* head = NULL;
	for (i = n - 1; i >= 0; i--)
		head = createElement(arr[i], head);
	return head;
}
// --------------------------- //


/// <summary>
/// The function receives a list,
/// and print its values.  
/// </summary>
/// <param>list* lst - the list</param>
/// <returns>None</returns>
void printList(list* lst)
{
	// your code:

	list* lstHead = NULL;
	
	if (lst) {

		lstHead = lst;

		while (lst) {
			printf("%d\t", lst->data);
			lst = lst->next;
		}

		printf("\n");
		lst = lstHead;
		lstHead = NULL;
	}
}
// --------------------------- //


/// <summary>
/// The function receives a pointer to the head of the list 
/// set first element to be the pivot and split all elements in lst to small and big accordingly
/// </summary>
/// <param>list** lst - Pointer to the pointer of the head of the list</param>
/// <param>list** pivot - Pointer to the pointer of the new pivot</param>
/// <param>list** small - Pointer to the pointer of the head of the small elements</param>
/// <param>list** big - Pointer to the pointer of the head of the big elements</param>
/// <returns>None</returns>
void partition(list** lst, list** pivot, list** small, list** big)
{
	// your code:

	list *smallHead = NULL, *bigHead = NULL;
	int firstSwapSmall = 1, firstSwapBig = 1;

	*pivot = *lst;
	*lst = (*lst)->next;
	(*pivot)->next = NULL;

	while (*lst) {
		if ((*lst)->data <= (*pivot)->data) {
			if (firstSwapSmall) {
				*small = *lst;
				smallHead = *small;
				*lst = (*lst)->next;
				(*small)->next = NULL;
				firstSwapSmall = 0;
				continue;
			}
			(*small)->next = *lst;
			*lst = (*lst)->next;
			*small = (*small)->next;
			(*small)->next = NULL;
		}
		else {
			if (firstSwapBig) {
				*big = *lst;
				bigHead = *big;
				*lst = (*lst)->next;
				(*big)->next = NULL;
				firstSwapBig = 0;
				continue;
			}
			(*big)->next = *lst;
			*big = (*big)->next;
			*lst = (*lst)->next;
			(*big)->next = NULL;
		}
	}
	*lst = NULL;
	*small = smallHead;
	*big = bigHead;
}
// --------------------------- //


/// <summary>
/// The function receives a pointer to the head of the list
/// and sort all elements by the quickSort method.
/// It is advisable to go over the standard implementation of quicksort on an array 
/// </summary>
/// <param>list* curr - Pointer to an element inside the list</param>
/// <returns>None</returns>
void quickSortList(list** lst)
{
	// your code:
		
	list *pivot = NULL, * small = NULL, * big = NULL, *smallHead = NULL;

	if (*lst) {

		partition(lst, &pivot, &small, &big);
		quickSortList(&small);
		quickSortList(&big);

		smallHead = small;

		if (!small) *lst = pivot;

		while (small) {
			if (small->next == NULL) {
				small->next = pivot;
				*lst = smallHead;
				break;
			}
			else small = small->next;
		}

		pivot->next = big;
		smallHead = NULL;
	}
}
// --------------------------- //


/// <summary>
/// The function free all allocated memory of a list. 
/// </summary>
/// <param>list** lst - Pointer to the pointer of the head of the list</param>
/// <returns>None</returns>
void freeList(list** lst)
{
	// your code:

	list* temp = NULL;

	while (*lst) {
		temp = *lst;
		*lst = (*lst)->next;
		free(temp);
	}

	temp = NULL;
	*lst = NULL;
}
// --------------------------- //
