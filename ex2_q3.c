﻿// Course: Advanced C programming
// exercise 2, question 3
// file name: ex2_q3.c

// --------------------------- //
// DO NOT CHANGE anything in the following macro:
#ifdef FUNC_DECLARE
#include "ex2_q3.h"
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
int deleteFirst(list** lst);
int deleteAfter(list* curr);
int splitList(list** lst, list** new);
void freeList(list** lst);
// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	unsigned long id_num;
	int n;
	list* lst = NULL, * new = NULL;
	int arr[] = { 3, 6, 1, 9, 8, 4, 5 };

	// call functions:
	id_num = student_id();
	printf("[id: %lu] start main\n", id_num);
	lst = createListFromArray(arr, SIZE(arr));
	n = splitList(&lst, &new);

	// write output:
	printf("Output:\n");
	printf("%d elements moved from the original list to the second list\n", n);
	printList(lst);
	printList(new);

	// free lists:
	freeList(&lst);
	freeList(&new);

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

	list* temp = lst;

	while (lst) {
		printf("%d\t", lst->data);
		lst = lst->next;
	}
	
	printf("\n");

	lst = temp;
	temp = NULL;
}
// --------------------------- //


/// <summary>
/// The function receives a pointer to the head of the list 
/// and delete the first element.
/// </summary>
/// <param>list** lst - Pointer to the pointer of the head of the list</param>
/// <returns>1/0 for success/fail</returns>
int deleteFirst(list** lst)
{
	// your code:

	list* temp = NULL;

	if (*lst) {
		temp = *lst;
		*lst = (*lst)->next;
		free(temp);
		return 1;
	}

	return 0;
}
// --------------------------- //


/// <summary>
/// The function receives a pointer to an element in list 
/// and delete the element after it
/// </summary>
/// <param>list* curr - Pointer to an element inside the list</param>
/// <returns>1/0 for success/fail</returns>
int deleteAfter(list* curr)
{
	// your code:

	list* temp = NULL;

	if (curr == NULL || curr->next == NULL) return 0;

	temp = curr->next;
	curr->next = curr->next->next;
	free(temp);
	return 1;
}
// --------------------------- //


/// <summary>
/// The function receives a list with elements and a new empty list
/// function split the list into 2 according to requirments
/// </summary>
/// <param>list** lst - Pointer to the pointer of the head of the original list</param>
/// <param>list** new - Pointer to the pointer of the head of the new list</param>
/// <returns>number of elements moved to the second list</returns>
int splitList(list** lst, list** new)
{
	// your code:

	int n = 0;
	int firstElement = 1;
	list* lstHead = *lst;
	list* newHead = NULL;

	// Empty list :

	if (*lst == NULL) return 0;

	// A list of 1 value:

	if (*lst != NULL && (*lst)->next == NULL) {
		*new = createElement((*lst)->data, NULL);
		deleteFirst(lst);
		*lst = NULL;
		return 1;
	}

	// lst[0] > lst[1]: 

	if ((*lst)->data > (*lst)->next->data && firstElement) {
			*new = createElement((*lst)->data, NULL);
			newHead = *new;
			deleteFirst(lst);
			lstHead = *lst;
			firstElement = 0;
			n++;
			if ((*lst)->next == NULL) return n;
	}

	while (*lst) {

		// lst[0] < lst[1] && lst[1] > lst[2]: 

		 if ((*lst)->next->next != NULL) {
			if ((*lst)->data < (*lst)->next->data && (*lst)->next->data >(*lst)->next->next->data) {
				if (firstElement) {
					*new = createElement((*lst)->next->data, NULL);
					newHead = *new;
					deleteAfter(*lst);
					*lst = (*lst)->next;
					firstElement = 0;
					n++;
					if ((*lst)->next == NULL) break;
					continue;
				}
				else {
					(*new)->next = createElement((*lst)->next->data, NULL);
					*new = (*new)->next;
					deleteAfter(*lst);
					*lst = (*lst)->next;
					n++;
					if ((*lst)->next == NULL) break;
					continue;
				}
			}
			else {
				*lst = (*lst)->next;
				if ((*lst)->next == NULL) break;
				continue;
			}
		 }

		// lst[last] > lst[last-1]:

		 else if ((*lst)->next->next == NULL && (*lst)->next->data > (*lst)->data) {
			 if (firstElement) {
				 *new = createElement((*lst)->next->data, NULL);
				 newHead = *new;
				 deleteAfter(*lst);
				 *lst = (*lst)->next;
				 firstElement = 0;
				 n++;
				 break;
			 }
			 else {
				 (*new)->next = createElement((*lst)->next->data, NULL);
				 *new = (*new)->next;
				 deleteAfter(*lst);
				 *lst = (*lst)->next;
				 n++;
				 break;
			 }
		 }

		else if ((*lst)->next->next == NULL && ((*lst)->next->data < (*lst)->data || ((*lst)->next->data == (*lst)->data))) break;

		*lst = (*lst)->next;
	}

	//printf("\n\n%d->%d\n\n", (*lst)->data, (*lst)->next->data);
	//printf("\n\n%d\n\n", deleteAfter(*lst));
	//printf("\n\n%d->%d\n\n", (*lst)->data, (*lst)->next->data);

	*lst = lstHead;
	*new = newHead;

	return n;
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

	*lst = NULL;
}
// --------------------------- //
