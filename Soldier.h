#ifndef _Soldier_h
#define _Soldier_h


/*includes & defines*/
#include "defs.h"
//A struct that holds the charachteristics of a soldier
typedef struct Soldier_ Soldier ,*PSoldier;

/*functions*/
/****************************************************************
function: Soldier_Create.
abstract: creating a new soldier with his\her ID and position.
parameters: char *ID and char *position
Returns: a pointer to the created soldier or NULL if 
a soldier with the same name already exists.
***************************************************************/
PSoldier Soldier_Create(char *ID, char *POS);

/*********************************************************************************
function: Soldier_Duplicate.
abstract: creating a copy of a soldier with his\her ID and position.
parameters: A Soldier pointer.
returns NULL if the pointer is NULL or if couldn't perform malloc.
prints ARG_ERR_MSG if pointer is NULL  or MALLOC_ERR_MSG if can't allocate memory
**********************************************************************************/
PSoldier Soldier_Duplicate(PSoldier Soldier);

/****************************************************************
function: Soldier_Print.
abstract: prints a soldier ID and position.
parameters: A Soldier pointer.
Errors: prints ARG_ERR_MSG if the soldier is NULL.
***************************************************************/
void Soldier_Print(PSoldier Soldier);

/****************************************************************
function: Soldier_Delete.
abstract: deletes a soldier (if exists).
parameters: A Soldier pointer.
***************************************************************/
void Soldier_Delete(PSoldier soldier);

/****************************************************************
function: Sol_ID.
abstract: gets the soldiers ID.
parameters: A pointer to a soldier.
Returns: an ID string.
***************************************************************/
char* Soldier_Get_ID(PSoldier sol);
		
/****************************************************************
function: Soldier_Get_Pos.
abstract: gets the soldiers POS.
parameters: A pointer to a soldier.
Returns: an ID string.
***************************************************************/
char * Soldier_Get_Pos(PSoldier sol);
#endif
