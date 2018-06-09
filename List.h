#ifndef _LIST_h_
#define _LIST_h_

/**Includes**/
#include "defs.h"

/* Some necessary type definitions:
List: An ADT for different types of linked lists.
PKEY: An ID.
PELEMENT: A pointer to an unknown element.
*/
typedef struct List_* PList;
typedef void* PKey; 
typedef void* PElem;

/* Function types */

typedef PKey(*GET_KEY)(PElem);//the ID of the element.
typedef PElem(*CLONE_FUNC)(PElem);
typedef void(*DESTROY_FUNC)(PElem);
typedef bool(*COMPARE_KEYS_FUNC)(PKey, PKey);
typedef void(*PRINT_FUNC)(PElem);

/* Interface functions */

/*********************************************************************************************
function: List_Create.
abstract: creating a new List of the appropriate key.
parameters: the key, DESTROY_FUNC - a function that deletes the list,
			COMPARE_KEYS_FUNC - compares two keys, PRINT_FUNC - prints the list elements.
Returns: a pointer to the new list created or NULL if failed.
*********************************************************************************************/
PList List_Create(GET_KEY, CLONE_FUNC, DESTROY_FUNC, COMPARE_KEYS_FUNC, PRINT_FUNC);

/*********************************************************************************************
function: List_Delete.
abstract: deleting a List and it's memory allocation.
parameters: a pointer to a list (PList).
*********************************************************************************************/
void List_Delete(PList);

/*********************************************************************************************
function: List_Print.
abstract: printing a List by the order of it's nodes.
parameters: a pointer to a list (PElem).
*********************************************************************************************/
void List_Print(PList);

/***************************************************************************************************
function: List_Add_Elem.
abstract: creates a copy of the element pointed at and adds the element to the end of the list.
parameters: gets apointer to a list, PList, and a pointer to the element, PElem, from which will retrieve
			the key(ID)
returns: SUCCESS if the addition occured FAILURE otherwise.
******************************************************************************************************/
Result List_Add_Elem(PList, PElem);

/***************************************************************************************************
function: List_Remove_Elem.
abstract: deletes the appropriate element.
parameters: gets apointer to a list, PList, and a key ,PKey.
returns: SUCCESS if the deletion occured FAILURE otherwise.
******************************************************************************************************/
Result List_Remove_Elem(PList, PKey);

/***************************************************************************************************
function: List_Get_First.
abstract: gets the first element of the list.
parameters: gets apointer to a list, PList.
returns: A pointer to the first element or NULL if failed.
******************************************************************************************************/
PElem List_Get_First(PList);

/***************************************************************************************************
function: List_Get_Next.
abstract: gets the next element on the list. Necessary to know where we stopped on the list
parameters: gets apointer to a list, PList.
returns: A pointer to the next element or NULL if it's the end of the list.
******************************************************************************************************/
PElem List_Get_Next(PList);

/***************************************************************************************************
function: List_Duplicate.
abstract:  copies all the elements of the source to the destination list.
parameters: gets a pointer to a source list and a destination list.
******************************************************************************************************/
void List_Duplicate(PList src, PList dst);

/***************************************************************************************************
function: List_Get_Elem.
abstract: returns a pointer to an element that matches the key.
parameters: gets apointer to a list, PList and a key.
returns: A pointer to the element or NULL if it doesn't exist.
******************************************************************************************************/
PElem List_Get_Elem(PList, PKey);

/***************************************************************************************************
function: List_Get_Clone_Func.
abstract: returns a pointer to function type CLONE_FUNC returning an element pointer, PElem.
parameters: gets apointer to a list, PList.
returns: A pointer to the function.
******************************************************************************************************/
CLONE_FUNC List_Get_Clone_Func(PList);

/***************************************************************************************************
function: List_Get_Des_Func.
abstract: returns a pointer to function type DESTROY_FUNC returning nothing.
parameters: gets apointer to a list, PList.
returns: A pointer to the function.
******************************************************************************************************/
DESTROY_FUNC List_Get_Des_Func(PList);

/***************************************************************************************************
function: List_Get_Cmp_Func.
abstract: returns a pointer to function type COMPARE_KEYS_FUNC returning boolean result.
parameters: gets apointer to a list, PList.
returns: A pointer to the function.
******************************************************************************************************/
COMPARE_KEYS_FUNC List_Get_Cmp_Func(PList);

/***************************************************************************************************
function: List_Get_Print_Func.
abstract: returns a pointer to function type PRINT_FUNC returning nothing.
parameters: gets apointer to a list, PList.
returns: A pointer to the function.
******************************************************************************************************/
PRINT_FUNC List_Get_Print_Func(PList);

/***************************************************************************************************
function: List_Get_Key_Func.
abstract: returns a pointer to function type GET_KEY returning PKey, pointer type void*.
parameters: gets apointer to a list, PList.
returns: A pointer to the function.
******************************************************************************************************/
GET_KEY List_Get_Key_Func(PList);

/***************************************************************************************************
function: Add_Two_Lists.
abstract: concatanates two lists
parameters: two pointers to lists, Plist.
returns: A pointer to the function.
******************************************************************************************************/
Result Add_Two_Lists(PList, PList);


#endif
