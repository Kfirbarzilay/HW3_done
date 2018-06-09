#include "List.h"

// a struct that hold a generic element.
typedef struct Node_ 
{
	struct Node_ *next;
	PElem element;
} NODE, *PNODE;

//a struct that holds two pointers to the head and tail of the list. 
//gets approriate functions pointers.
typedef struct List_ 
{
	PNODE head, tail;
	GET_KEY get_key_f;
	CLONE_FUNC clone_f;
	DESTROY_FUNC destroy_f;
	COMPARE_KEYS_FUNC compare_f;
	PRINT_FUNC print_f;
} LIST;

// creating an iterator for the list_Get_Next.
static PNODE itr = NULL;

/***************************************************************************************************
function: InternalFind.
abstract: checks if an elements exists.
parameters: gets apointer to a list, PList, and a pointer to an element PElem.
returns: true if it finds the element and false otherwise.
******************************************************************************************************/
static bool InternalFind(PList list, PElem elem){
	//get the key from the element.
	PKey ElemKey = list->get_key_f(elem);
	PNODE cur_node = list->head;

	// If head node itself holds the key return SUCCESS.
	if (cur_node != NULL && list->compare_f(ElemKey, list->get_key_f(cur_node->element)))
	{
		return true;
	}

	//traverse through the list and search for the element.
	while (cur_node != NULL && !list->compare_f(ElemKey, list->get_key_f(cur_node->element)))
	{
		cur_node = cur_node->next;
	}

	// If key was not present in linked list
	if (cur_node == NULL) return false;

	//found the key. 
	return true;
}

PList List_Create(GET_KEY get_key_f,
				CLONE_FUNC clone_f,
				DESTROY_FUNC destroy_f,
				COMPARE_KEYS_FUNC compare_f,
				PRINT_FUNC print_f){
		PList list = NULL;
		//allocating memory and checking allocation.
		list = (PList)malloc(sizeof(*list));
		if (list != NULL){
			//initializing list pointers and functions.
			list->head = NULL;
			list->tail = NULL;
			list->get_key_f = get_key_f;
			list->compare_f = compare_f;
			list->destroy_f = destroy_f;
			list->clone_f = clone_f;
			list->print_f = print_f;
		}
		return list;
}

void List_Delete(PList list){
	if (list == NULL) return;
	PNODE cur_node = list->head;
	PNODE next_node;
	while(cur_node != NULL) {
		//getting the next node.
		next_node = cur_node->next;

		//deleting the element and the node.
		list->destroy_f(cur_node->element);
		cur_node->element = NULL;
		free(cur_node);

		//advancing the current node.
		cur_node = next_node;
	}
	//initialize head and tail.
	free(list);

}

void List_Print(PList Plist){
	if (Plist->head == NULL) return;
	PNODE cur_Node = Plist->head;
	//print the list.
	while (cur_Node != NULL) {
		Plist->print_f(cur_Node->element);
		cur_Node = cur_Node->next;
	}
}

Result List_Add_Elem(PList list, PElem Pelem){
	//first check if one or more of the paramters is NULL. if so return FAILURE.
	if (list == NULL || Pelem == NULL) return FAILURE;

	//if element exists don't add it to the list.
	if (InternalFind(list, Pelem) == true) return FAILURE;

	//copying the element, creating a new node and adding it to at the tail.
	PElem new_Element = list->clone_f(Pelem);
	if (new_Element == NULL) return FAILURE;

	//allocate node.
	PNODE new_Node = (PNODE)malloc(sizeof(NODE));
	if (new_Node == NULL) {
		list->destroy_f(new_Element);
		return FAILURE;
	}
	//put in the data
	new_Node->element = new_Element;

	//This new node is going to be the last node, so make next of it as NULL
	new_Node->next = NULL;

	//If the Linked List is empty, then make the new node as head.
	if (list->head == NULL) {
		list->head = new_Node;
		list->tail = new_Node;
		return SUCCESS;
	}
	 //the head of the list isn't NULL. linking the tail to the new node.
	list->tail->next = new_Node;
	list->tail = new_Node;
	return SUCCESS;
}

Result List_Remove_Elem(PList list, PKey key) {
	//if there are no nodes int the list. 
	if (list->head == NULL) return FAILURE;

	//store the head node. initialize prev pointer to a node.
	PNODE cur_node = list->head, prev_node= list->head;

	// If head node itself holds the key to be deleted, delete it.
	//the second condition is for checking the keys.
	if (cur_node != NULL && list->compare_f(list->get_key_f(cur_node->element), key))
	{
		list->head = cur_node->next;   // Changed head
		if (list->tail == cur_node) list->tail = cur_node->next;//change tail if it points to the same node.
		list->destroy_f(cur_node->element);   //delete the element.
		cur_node->element = NULL;
		free(cur_node);               // free old head
		cur_node = NULL;
		return SUCCESS;
	}

	//traverse through the list and search for the element.
	while (cur_node != NULL && !(list->compare_f(list->get_key_f(cur_node->element), key)))
	{
		prev_node = cur_node;
		cur_node = cur_node->next;
	}

	// If key was not present in linked list
	if (cur_node == NULL) return FAILURE;

	// otherwise, unlink the node from linked list
	if (list->tail == cur_node) list->tail = prev_node;//change tail if it points to the same node.
	prev_node->next = cur_node->next;
	list->destroy_f(cur_node->element);//delete the element.
	free(cur_node);  // Free memory
	return SUCCESS;
}


PElem List_Get_First(PList list)
{
	//check if list is empty
	if (list->head == NULL) return NULL;

	//initializing itr. returning head.
	itr = list->head;
	return list->head->element;
}
//
PElem List_Get_Next(PList list)
{	
	//no elements on the list.
	if (itr == NULL) return NULL;
	
	//the next node.
	itr = itr->next;

	//no more nodes.
	if (itr == NULL) return NULL;

	return itr->element;//return the element.
}

void List_Duplicate(PList src, PList dst)
{
	//adding the first element;
	Result res = List_Add_Elem(dst, List_Get_First(src));

	//if there are no elements on the list exit.
	if (res == FAILURE) {
		return;
	}
	//adding the other elements on the list.
	Result added;
	while (itr != NULL) {
		added = List_Add_Elem(dst, List_Get_Next(src));//itr changes here.
		if (added == FAILURE) {//reached the end of the list and exiting.
			return;
		}
	}
}

PElem List_Get_Elem(PList list, PKey key)
{	//checking if it's the first element on the list.
	if (list == NULL || key == NULL) return NULL;
	//checking the first element;
	PElem elem;
	elem = List_Get_First(list);
	
	//if there are no elements on the list exit.
	if (elem == NULL) {
		return NULL;
	}

	//checking if the the head node stores the key.
	if (list->compare_f(key, list->get_key_f(elem))) 
		return elem;

	//search for the next elements on the list.
	elem = List_Get_Next(list);//itr changes here.
	while (itr != NULL) {
		if (list->compare_f(key, list->get_key_f(elem)))
			return elem;
		elem = List_Get_Next(list);//itr changes here.
	}
	return NULL;

}

CLONE_FUNC List_Get_Clone_Func(PList list)
{
	return list->clone_f;
}

DESTROY_FUNC List_Get_Des_Func(PList list)
{
	return list->destroy_f;
	
}

COMPARE_KEYS_FUNC List_Get_Cmp_Func(PList list)
{
	return list->compare_f;
}

PRINT_FUNC List_Get_Print_Func(PList list)
{
	return list->print_f;
}

GET_KEY List_Get_Key_Func(PList list)
{
	return list->get_key_f;
}

Result Add_Two_Lists(PList src, PList dst)
{
	//check if NULL
	if (src == NULL || dst == NULL) return FAILURE;
	if (src->head == NULL) return FAILURE;

	if (src != dst) {
		//if there are no element on the list.
		if (dst->head == NULL) {
			dst->head = src->head;
		}

		//one or more.
		else {
			dst->tail->next = src->head;
		}
		
		dst->tail = src->tail;

		//empty the source list.
		src->head = NULL;
		src->tail = NULL;
		return SUCCESS;
	}

	if (src == dst) {
		return SUCCESS;
	}
	return FAILURE;
}










