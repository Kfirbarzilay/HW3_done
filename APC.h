#ifndef _APC_h
#define _APC_h

/*includes & defines*/
#include "Soldier.h"

//A struct that defines an APC and the soldiers inside of it.
typedef struct APC_ *P_APC;

/*functions*/
/****************************************************************
function: APC_Create.
abstract: creating a new and empty APC.
parameters: char *ID 
Returns a pointer to the APC created or NULL if 
		an APC with the same name already exists.
***************************************************************/
P_APC APC_Create(char *ID);

/****************************************************************
function: APC_Delete.
abstract: Deleting an existing APC and the soldiers on it.
parameters: P_APC - a pointer to an APC.
***************************************************************/
void APC_Delete(P_APC pAPC);

/****************************************************************
function: APC_Print.
abstract: prints an APC ID and the SOldiers inside of it.
parameters: An APC pointer.
Errors: prints ARG_ERR_MSG if the APC is NULL.
***************************************************************/
void APC_Print(P_APC pAPC);

/**********************************************************************************************
function: APC_Duplicate.
abstract: creating a copy of an APC with it's ID and soldiers inside of it.
parameters: An APC pointer.
Returns a pointer to the APC copy or NULL if the pointer is NULL or if couldn't perform malloc.
Prints ARG_ERR_MSG if pointer is NULL or MALLOC_ERR_MSG if can't allocate memory
***********************************************************************************************/
P_APC APC_Duplicate(P_APC pAPC);

/***********************************************************************************************************
function: APC_Insert_Soldier.
abstract: Adding a soldier to an APC if there's room.
parameters: An APC pointer and a soldier pointer.
Returns SUCCESS if the soldier was added to the APC and FAILURE if it fails and prints "ERROR:APC is Full".
***********************************************************************************************************/
Result APC_Insert_Soldier(P_APC pAPC, PSoldier pSoldier);

/****************************************************************************************************************
function: APC_Pop.
abstract: Removing a soldier from an APC if exists. Not deleting it's memory allocation.
parameters: An APC pointer.
Returns SUCCESS if the soldier was removed from the APC and FAILURE if it fails and prints "ERROR: APC is Empty".
*****************************************************************************************************************/
PSoldier APC_Pop(P_APC pAPC);

/****************************************************************
function: APC_ID.
abstract: gets the APC's ID.
parameters: A pointer to an APC.
Returns: an ID string.
***************************************************************/
char* APC_ID(P_APC APC);


/****************************************************************
function: Get_Sol_Count.
abstract: gets the soldiers in the APC.
parameters: A pointer to an APC.
Returns: int.
***************************************************************/
int Get_Sol_Count(P_APC APC);
#endif
