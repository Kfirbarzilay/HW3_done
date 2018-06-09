#ifndef _Battlefield_h
#define _Battlefield_h

/*includes & defines*/
#include "WarZone.h"
/*necessary definitions*/
typedef struct Battlefield_ *BF;


/****************************************************************
function: Check_If_WarZone_Exists.
abstract: searching for a given warzone ID.
parameters: a pointer to the battlefield, BF, and the War Zone
			ID as char array.
Returns: a pointer to the  WarZone or NULL if not found.
***************************************************************/
PWarZone Check_If_WarZone_Exists(BF BattleField, char WarZone_ID[MAX_ID_LENGTH]);

/****************************************************************
function: Create_Battlefield.
abstract: searching for a given warzone ID.
parameters: a pointer to the battlefield, BF, and the War Zone
ID as char array.
Returns: a pointer to the  WarZone or NULL if not found.
***************************************************************/
BF Create_Battlefield(	CLONE_FUNC,
						DESTROY_FUNC,
						COMPARE_KEYS_FUNC,
						PRINT_FUNC,
						GET_KEY);

/****************************************************************
function: BF_Delete.
abstract: Deleting the battlefield.
parameters: A pointer to a Battlefield, BF.
returns: NONE.
***************************************************************/
void BF_Delete(BF);

/****************************************************************
function: BF_Add_WarZone.
abstract: adds a war zone to the battlefield.
parameters: a pointer to the battlefield, BF, and the War Zone
			ID as char array.
Returns: SUCCESS if added and FAILURE otherwise.
***************************************************************/
Result BF_Add_WarZone(BF Battlefield, char WZ_ID[MAX_ID_LENGTH]);

/****************************************************************
function: BF_Remove_WarZone.
abstract: Removes a war zone frm the battlefield.
parameters: a pointer to the battlefield, BF, and the War Zone
			ID as char array.
Returns: SUCCESS if Removed and FAILURE otherwise.
***************************************************************/
Result BF_Remove_WarZone(BF Battlefield, char WZ_ID[MAX_ID_LENGTH]);

/****************************************************************
function: initiate_Battlefield_Func.
abstract: creates the battlefield.
parameters: NONE.
Returns: a pointer to the created battlefield.
***************************************************************/
BF initiate_Battlefield_Func(void);

/****************************************************************
function: BF_Print.
abstract: Prints the Battlefield.
parameters: A pointer to a BattleField.
returns: NONE.
*****************************************************************/
void BF_Print(BF);


/****************************************************************
function: BF_Raise_WarZone.
abstract: Raises a war zone Alert.
parameters: a pointer to the battlefield, BF, and the War Zone
			ID as char array.
Returns: SUCCESS if Raised and FAILURE otherwise.
***************************************************************/
int BF_Raise_WarZone(BF Battlefield, char WZ_ID[MAX_ID_LENGTH]);


/****************************************************************
function: BF_Move_All_Squads.
abstract: Moves all squads to the level 3 war zone.
parameters: a pointer to the battlefield, BF.
Returns: SUCCESS if Raised and FAILURE otherwise.
***************************************************************/
Result BF_Move_All_Squads(BF Battlefield, char dst_Wz_ID[MAX_ID_LENGTH]);

/****************************************************************
function: BF_Initialize_War_Zone_Alert_Level.
abstract: initializes a war zone Alert.
parameters: a pointer to the battlefield, BF, and the War Zone
			ID as char array.
Returns: SUCCESS if Raised and FAILURE otherwise.
***************************************************************/
Result BF_Initialize_War_Zone_Alert_Level(BF Battlefield, char WZ_ID[MAX_ID_LENGTH]);


/****************************************************************
function: BF_Move_Squad_From_War_Zone.
abstract: moving a squad from a warzone to destination war zone.
parameters: A pointer to the Source ,src, a pointer to the Destination
,dst ,the squad ID char array(const. size).
Returns: SUCCESS when APC is removed from the squad and FAILURE otherwise.
*****************************************************************/
Result BF_Move_Squad_From_War_Zone(BF battle, char src[MAX_ID_LENGTH], char dst[MAX_ID_LENGTH], char Squad_ID[MAX_ID_LENGTH]);



#endif