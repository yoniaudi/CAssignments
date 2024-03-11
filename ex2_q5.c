// Course: Advanced C programming
// exercise 2, question 5
// file name: ex2_q5.c

// --------------------------- //
// DO NOT CHANGE anything in the following macro:
#ifdef FUNC_DECLARE
#include "ex2_q5.h"
#else
// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define FUNC_DECLARE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf
// --------------------------------------- //
// Types declration section:
// --------------------------------------- //
typedef struct list
{
	char data;
	struct list* next;
} list;
// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //
unsigned long student_id();
list* createElement(char data, list* next);
list* createCircleListFromString(char* str);
int compareCircleLists(list** lst1, list** lst2);
int circleListLength(list* lst);
void printList(list* lst);
void freeList(list** lst);
// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	unsigned long id_num;
	int result;
	list* lst1 = NULL, * lst2 = NULL;
	char str1[] = "duezax";
	char str2[] = "zaxdue";

	// call functions:
	id_num = student_id();
	printf("[id: %lu] start main\n", id_num);
	lst1 = createCircleListFromString(str1);
	lst2 = createCircleListFromString(str2);

	// write output:
	printf("Output:\n");
	result = compareCircleLists(&lst1, &lst2);
	printList(lst1);
	printList(lst2);

	// free list:
	freeList(&lst1);
	freeList(&lst2);

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
///// <param>char data - value from type char, the value of the element</param>
///// <param>list* next - pointer to the next value after the newly created element</param>
///// <returns>dynamic value from type list</returns>
list* createElement(char data, list* next)
{
	list* item = (list*)(malloc(sizeof(list)));
	item->data = data;
	item->next = next;
	return item;
}
// --------------------------- //

/// <summary>
/// The function receives a string array
/// and returns a newly created list
/// </summary>
/// <param>char* str - The array string</param>
/// <returns>newly created list</returns>
list* createCircleListFromString(char* str)
{
	list* head = NULL;
	list* tail = NULL;
	while (*str != '\0')
	{
		if (!head)
			head = tail = createElement((*str++), NULL);
		else
		{
			tail->next = createElement((*str++), NULL);
			tail = tail->next;
		}
	}
	if (tail)
		tail->next = head;
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
		printf("%c\t", lst->data);
		lst = lst->next;
	}
		lst = temp;

		if (lst) printf("\n");
		
		temp = NULL;
}
// --------------------------- //


/// <summary>
/// The function receives a pointer to the head of the list 
/// set first element to be the pivot and split all elements in lst to small and big accordingly
/// </summary>
/// <param>list** lst1 - Pointer to the pointer of the head of the 1st circle list</param>
/// <param>list** lst2 - Pointer to the pointer of the head of the 2nd circle list</param>
/// <returns>true if both lists are circly equal</returns>
int compareCircleLists(list** lst1, list** lst2)
{
	// your code:

	if (!(*lst1) && !(*lst2)) return 1;

	list* lst1Head = *lst1, * lst2Head = *lst2;
	int i;
	int len1 = 0, len2 = 0;

	len1 = circleListLength(*lst1);
	len2 = circleListLength(*lst2);

	// Checking smallest Ascii value and saving it's adress:

	for (i = 0; i < len1; i++) {
		if (lst1Head->data > (*lst1)->data) {
			lst1Head = *lst1;
		}
		*lst1 = (*lst1)->next;
	}

	for (i = 0; i < len2; i++) {
		if (lst2Head->data > (*lst2)->data) {
			lst2Head = *lst2;
		}
		*lst2 = (*lst2)->next;
	}

	*lst1 = lst1Head;
	*lst2 = lst2Head;

	// Last element = NULL:

	for (i = 0; i < len1 - 1; i++) {
		*lst1 = (*lst1)->next;
	}
	if (*lst1) (*lst1)->next = NULL;
	*lst1 = lst1Head;

	for (i = 0; i < len2 - 1; i++) {
		*lst2 = (*lst2)->next;
	}
	if (*lst2) (*lst2)->next = NULL;
	*lst2 = lst2Head;

	if (len1 != len2) return 0;

	while (*lst1 && *lst2) {
		if ((*lst1)->data != (*lst2)->data) {
			*lst1 = lst1Head;
			*lst2 = lst2Head;
			return 0;
		}
		*lst1 = (*lst1)->next;
		*lst2 = (*lst2)->next;
	}

	*lst1 = lst1Head;
	*lst2 = lst2Head;

	return 1;
}
// --------------------------- //


/// <summary>
/// The function receives a pointer to the circle linked list,
/// and returns how many elements inside.
/// </summary>
/// <param>list* lst - Pointer to an element inside the list</param>
/// <returns>amount of elements in the circle list</returns>
int circleListLength(list* lst)
{
	// your code:

	list* lstHead = NULL;
	int count = 0;

	if (lst) {

		lstHead = lst;
		lst = lst->next;

		while (lst) {
			if (lst == lstHead) {
				count++;
				break;
			}
			else {
				lst = lst->next;
				count++;
			}
		}
	}

	lstHead = NULL;

	return count;
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

	list *temp = NULL;

	while (*lst) {
		temp = *lst;
		*lst = (*lst)->next;
		free(temp);
	}

	temp = NULL;
	*lst = NULL;
}
// --------------------------- //
