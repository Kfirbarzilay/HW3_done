#ifndef _WARZONE_h_
#define _WARZONE_h_

#include "List.h"
#include "Squad.h"

typedef struct WarZone_ *PWarZone;

/* Interface functions */

/****************************************************************
function: WarZone_Create.
abstract: creating a new WarZone by it's ID.
parameters: char array (fixed size) and necessary functions for
			the lists of squads: clone, delete, compare keys,
			print and get key functions.
Returns: a pointer to the created WarZone or NULL if failed.
***************************************************************/
PWarZone WarZone_Create(char ID[MAX_ID_LENGTH],
						CLONE_FUNC,
						DESTROY_FUNC,
						COMPARE_KEYS_FUNC,
						PRINT_FUNC,
						GET_KEY
						);



/****************************************************************
function: WarZone_Delete.
abstract: Deleting a WarZone.
parameters: A pointer to a WarZone.
returns: NONE.
***************************************************************/
void WarZone_Delete(PWarZone);


/****************************************************************
function: WarZone_Print.
abstract: Prints the WarZone.
parameters: A pointer to a WarZone.
returns: NONE.
*****************************************************************/
void WarZone_Print(PWarZone);

/****************************************************************
function: WarZone_Duplicate.
abstract: Duplicates an existing Warzone.
parameters: A pointer to a Warzone.
Returns: A pointer to the dup. Warzone or NULL if it fails.
*****************************************************************/
PWarZone WarZone_Duplicate(PWarZone WarZone);

/****************************************************************
function: WarZone_Raise_Alert.
abstract: raises the alert level in given warzone.
parameters: A pointer to a Warzone.
Returns: new warzone level, as integer.
*****************************************************************/
int WarZone_Raise_Alert(PWarZone WarZone);

/****************************************************************
function: WarZone_Add_Squad.
abstract: adding a squad to a warzone.
parameters: A pointer to a Warzone, the squad ID: char array(const. size).
Returns: SUCCESS when squad added and FAILURE otherwise.
*****************************************************************/
Result WarZone_Add_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH]);

/****************************************************************
function: WarZone_Add_Sol_To_Squad.
abstract: adding a soldier to a squad found in a warzone.
parameters: A pointer to a Warzone, the squad ID char array(const. size),
			Sol_ID: char array(const. size), Sol_Pos:char array(const. size).
Returns: SUCCESS when soldier added and FAILURE otherwise.
*****************************************************************/
Result WarZone_Add_Sol_To_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH], char Sol_ID[MAX_ID_LENGTH], char Sol_Pos[MAX_ID_LENGTH]);

/****************************************************************
function: WarZone_Add_APC_To_Squad.
abstract: adding an APC to a squad found in a warzone.
parameters: A pointer to a Warzone, the squad ID char array(const. size),
			APC_ID:char array(const. size).
Returns: SUCCESS when APC added and FAILURE otherwise.
*****************************************************************/
Result WarZone_Add_APC_To_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH], char APC_ID[MAX_ID_LENGTH]);

/****************************************************************
function: WarZone_Add_Sol_To_APC_In_Squad.
abstract: adding a soldier to an APC in a squad fighting in the warzone.
parameters: A pointer to a Warzone, the squad ID char array(const. size),
	Sol_ID:char array(const. size), APC_ID:char array(const. size).
Returns: SUCCESS when soldier added to APC and FAILURE otherwise.
*****************************************************************/
Result WarZone_Add_Sol_To_APC_In_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH], char Sol_Id[MAX_ID_LENGTH], char APC_ID[MAX_ID_LENGTH]);

/****************************************************************
function: WarZone_APC_Pop_Found_In_Squad.
abstract: removing a soldier from an APC listed in a squad fighting in the warzone.
parameters: A pointer to a Warzone, the squad ID char array(const. size),
			APC_ID:char array(const. size).
Returns: SUCCESS when Soldier is removed from the APC and FAILURE otherwise.
*****************************************************************/
Result WarZone_APC_Pop_Found_In_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH], char APC_ID[MAX_ID_LENGTH]);


/****************************************************************
function: WarZone_Remove_Soldier_From_Squad.
abstract: removing a soldier from a squad fighting in the warzone.
parameters: A pointer to a Warzone, the squad ID char array(const. size),
			SOL_ID:char array(const. size).
Returns: SUCCESS when Soldier is removed from the squad and FAILURE otherwise.
*****************************************************************/
Result WarZone_Remove_Soldier_From_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH], char Sol_ID[MAX_ID_LENGTH]);

/****************************************************************
function: WarZone_Remove_APC_From_Squad.
abstract: removing an APC from a squad fighting in the warzone.
parameters: A pointer to a Warzone, the squad ID char array(const. size),
			APC_ID:char array(const. size).
Returns: SUCCESS when APC is removed from the squad and FAILURE otherwise.
*****************************************************************/
Result WarZone_Remove_APC_From_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH], char APC_ID[MAX_ID_LENGTH]);

/****************************************************************
function: WarZone_Remove_Squad.
abstract: removing a squad from a warzone.
parameters: A pointer to a Warzone, the squad ID char array(const. size).
Returns: SUCCESS when APC is removed from the squad and FAILURE otherwise.
*****************************************************************/
Result WarZone_Remove_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH]);

/****************************************************************
function: WarZone_ID.
abstract: gets the WZ ID.
parameters: A pointer to a wz.
Returns: an array of chars(fixed size).
***************************************************************/
char* WarZone_ID(PWarZone warzone);

/****************************************************************
function: War_Zone_Move_Squad.
abstract: moving a squad from a warzone to destination war zone.
parameters: A pointer to the Source ,src, a pointer to the Destination
			,dst ,the squad ID char array(const. size).
Returns: SUCCESS when squad is removed from the squad and FAILURE otherwise.
*****************************************************************/
Result War_Zone_Move_Squad(PWarZone src, PWarZone dst, char Squad_ID[MAX_ID_LENGTH]);

/****************************************************************
function: War_Zone_Move_All_Squads.
abstract: moves all squads from a warzone to destination war zone.
parameters: A pointer to the Source ,src, a pointer to the Destination
			,dst .
Returns: SUCCESS when squad is removed from the squad and FAILURE otherwise.
*****************************************************************/
Result War_Zone_Move_All_Squads(PWarZone src, PWarZone dst);

/****************************************************************
function: War_Zone_Alert_Level_Zero.
abstract: initializes war zone alert level.
parameters: A pointer to the war zone that's in level 3.
Returns: NONE
*****************************************************************/
void War_Zone_Alert_Level_Zero(PWarZone);
#endif
