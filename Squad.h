#ifndef _SQUAD_h
#define _SQUAD_h

/*includes & defines*/
#include "List.h"
#include "Soldier.h"
#include "APC.h"

/*necessary definitions*/
typedef struct Squad_ *PSquad;

/* Interface functions */

/****************************************************************
function: Squad_Create.
abstract: creating a new Squad by it's ID.
parameters: char array (fixed size) and necessary functions for
			the lists of soldiers and APC's to be used in the list ADT.
Returns: a pointer to the created Squad or NULL if failed.
***************************************************************/
PSquad Squad_Create(char ID[MAX_ID_LENGTH],
					CLONE_FUNC, CLONE_FUNC,
					DESTROY_FUNC, DESTROY_FUNC,
					COMPARE_KEYS_FUNC,
					PRINT_FUNC, PRINT_FUNC,
					GET_KEY, GET_KEY
					);

/****************************************************************
function: Squad_Delete.
abstract: Deleting a Squad.
parameters: A pointer to a squad.
***************************************************************/
void Squad_Delete(PSquad);


/****************************************************************
function: Squad_Print.
abstract: Prints the squad.
parameters: A pointer to a squad.
*****************************************************************/
void Squad_Print(PSquad);

/****************************************************************
function: Squad_Duplicate.
abstract: Duplicates an existing squad.
parameters: A pointer to a squad.
Returns: A pointer to the dup. squad or NULL if it fails.
*****************************************************************/
PSquad Squad_Duplicate(PSquad Squad);

/****************************************************************
function: Squad_Add_Soldier.
abstract: Adds a soldier to a squad.
parameters: A pointer to a squad, char ID[], char POS[].
Returns: SUCCESS when added and FAILURE otherwise.
*****************************************************************/
Result Squad_Add_Soldier(PSquad, char ID[MAX_ID_LENGTH], char POS[MAX_ID_LENGTH]);

/****************************************************************
function: Squad_Add_APC.
abstract: Adds an APC to a squad. 
parameters: A pointer to a squad, a soldier ID string, an PAC ID string.
Returns: SUCCESS when added and FAILURE otherwise.
*****************************************************************/
Result Squad_Add_APC(PSquad, char ID[MAX_ID_LENGTH]);

/****************************************************************
function: Squad_Insert_Sold_APC. 
abstract:	Adds a soldier to an APC in a squad. 
			NOTE: A soldier must be deleted from 
			the soldiers list after being added.
parameters: A pointer to a squad, soldier ID, APC_ID. 
Returns: SUCCESS when added and FAILURE otherwise.
*****************************************************************/
Result Squad_Insert_Sold_APC(PSquad, char Sol_Id[MAX_ID_LENGTH], char APC_ID[MAX_ID_LENGTH]);

/****************************************************************
function: Squad_APC_Pop.
abstract: removes a soldier from the top seat of the APC in a squad.
parameters: A pointer to a squad and an APC ID.
			NOTE: the APC must be in the squad.
			NOTE: after removal the soldier is added to the soldiers
				  list.
Returns: SUCCESS when removed and FAILURE otherwise.
*****************************************************************/
Result Squad_APC_Pop(PSquad, char APC_ID[MAX_ID_LENGTH]);

/****************************************************************
function: Squad_Delete_Soldier.
abstract: removes a soldier from the soldiers list.
parameters: A pointer to a squad and a soldier ID.
			NOTE: the soldier must be in the squad.
			NOTE: the soldier mustn't be removed from an APC.
Returns: SUCCESS when removed and FAILURE otherwise.
*****************************************************************/
Result Squad_Delete_Soldier(PSquad, char Sol_ID[MAX_ID_LENGTH]);

/****************************************************************
function: Squad_Delete_APC.
abstract: removes an APC from squad's APC's list.
parameters: A pointer to a squad and an APC ID.
NOTE: soldiers must be deleted from APC.
Returns: SUCCESS when deleted and FAILURE otherwise.
*****************************************************************/
Result Squad_Delete_APC(PSquad, char APC_ID[MAX_ID_LENGTH]);

/****************************************************************
function: Squad_ID.
abstract: gets the squad's ID.
parameters: A pointer to a squad.
Returns: an array of chars(fixed size).
***************************************************************/
char* Squad_ID(PSquad squad);



#endif 