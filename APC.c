#include "APC.h"

//A struct that defines an APC and the soldiers inside of it.
typedef struct APC_{
	char ID[MAX_ID_LENGTH];
	PSoldier Soldiers[APC_MAX_Soldiers];
	int Stack_Top;
}APC;

/****************************************************************
function: APC_Create.
abstract: creating a new and empty APC.
parameters: char *ID
Returns a pointer to the APC created or NULL if
an APC with the same name already exists.
***************************************************************/
P_APC APC_Create(char *ID) {
	//first checking if the ID is not NULL and with approprite length
	if (ID == NULL) return NULL; 
	if (strlen(ID) > MAX_ID_LENGTH) return NULL;
	//initializing an APC's linked list.
	P_APC new_APC = (P_APC)malloc(sizeof(APC));
	if (new_APC == NULL) {
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	strcpy(new_APC->ID, ID);
	//initializing the APC pointers to the soldiers on it.
	for (int i = 0; i < APC_MAX_Soldiers; ++i) {
		new_APC->Soldiers[i] = NULL;
	}
	new_APC->Stack_Top = 0;
	//listInit = true; //initializing linked list
	return new_APC;
}

/****************************************************************
function: APC_Print.
abstract: prints an APC ID and the SOldiers inside of it.
parameters: An APC pointer.
Errors: prints ARG_ERR_MSG if the APC is NULL.
***************************************************************/
void APC_Print(P_APC APC) {
	if (APC == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	printf("%s , Occupancy: %d/%d\n", APC->ID, APC->Stack_Top, APC_MAX_Soldiers);
	if (APC->Stack_Top > 0) {
		for (int i = 0; i < APC->Stack_Top; i++) {
			printf("Seat %d: ", i + 1);
			Soldier_Print(APC->Soldiers[i]);
		}
	}
}

/***********************************************************************************************************
function: APC_Insert_Soldier.
abstract: Adding a soldier to an APC if there's room.
parameters: An APC pointer and a soldier pointer.
Returns SUCCESS if the soldier was added to the APC and FAILURE if it fails and prints "ERROR:APC is Full".
***********************************************************************************************************/
Result APC_Insert_Soldier(P_APC pAPC, PSoldier pSoldier) {
	//first, check parameters legality: not NULL.
	if (pAPC == NULL || pSoldier == NULL) return FAILURE;//TODO: 1. check if necessary.
	//check if the APC isn't full.
	if(pAPC->Stack_Top == APC_MAX_Soldiers){
		printf("Error: APC is Full\n");
		return FAILURE;
	}

	//There's room, inserting the soldier copy.
	pAPC->Soldiers[pAPC->Stack_Top] = pSoldier;

		//increment the stack top element index if it's smaller than APC_MAX_Soldiers.
	if (pAPC->Stack_Top < APC_MAX_Soldiers)
		pAPC->Stack_Top++;
	return SUCCESS;
}

/****************************************************************************************************************
function: APC_Pop.
abstract: Removing a soldier from an APC if exists. Not deleting it's memory allocation.
parameters: An APC pointer.
Returns a pointer to the soldier if the soldier was removed from the APC and NULL if APC's empty and 
		prints "ERROR: APC is Empty".
*****************************************************************************************************************/
PSoldier APC_Pop(P_APC pAPC) {
	//first, check parameters legality: not NULL.
	if (pAPC == NULL)return NULL;//TODO: 2.check if necessary.
	 //check if the APC isn't empty.
	if (pAPC->Stack_Top == 0) {
		printf("Error: APC is Empty\n");
		return NULL;
	}
	//APC isn't empty, removing soldier.
	PSoldier soldier = pAPC->Soldiers[pAPC->Stack_Top-1];
	pAPC->Soldiers[pAPC->Stack_Top - 1] = NULL;
	//decrease the stack top element index if it's bigger than 0 (==empty APC).
	if (pAPC->Stack_Top > 0)
		pAPC->Stack_Top--;
	return soldier;
}

char * APC_ID(P_APC APC)
{
	if (APC != NULL) {
		char* ID = APC->ID;
		return ID;
	}
	return NULL;
}

int Get_Sol_Count(P_APC APC)
{
	return APC->Stack_Top;
}

/**********************************************************************************************
function: APC_Duplicate.
abstract: creating a copy of an APC with it's ID and soldiers inside of it.
parameters: An APC pointer.
Returns a pointer to the APC copy or NULL if the pointer parameter given is NULL or if 
	couldn't perform malloc.
	Prints ARG_ERR_MSG if pointer is NULL or MALLOC_ERR_MSG if can't allocate memory
***********************************************************************************************/

P_APC APC_Duplicate(P_APC pAPC) {
	//if the pointer parameter is NULL return NULL
	if (pAPC == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	//creating the duplicant APC.
	P_APC New_APC = APC_Create(pAPC->ID);
	if (New_APC == NULL) {
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	for (int i = 0; i < pAPC->Stack_Top; ++i) {
		New_APC->Soldiers[i] = pAPC->Soldiers[i];
	}
	return New_APC;
}

/****************************************************************
function: APC_Delete.
abstract: Deleting an existing APC and the soldiers on it.
parameters: P_APC - a pointer to an APC.
***************************************************************/
void APC_Delete(P_APC pAPC) {
	if (pAPC == NULL) return;

	//deleting the APC and the soldiers on it.
	for (int i = 0; i < pAPC->Stack_Top; ++i) {
		PSoldier sol_DEl = pAPC->Soldiers[i];
		Soldier_Delete(sol_DEl);
	}
			//freeing allocated memory for the APC
	free(pAPC);
	pAPC = NULL;
}









