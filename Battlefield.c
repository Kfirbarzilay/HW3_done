#include "Battlefield.h"


typedef struct Battlefield_ {
	PList WarZones;
	bool initiated;
}BattleField;

/*
Defining user functions. will be used by the list functions.
*/

/****************************************************************
function: Get_WZ_ID.
abstract: gets the War Zone ID.
parameters: A pointer to a Element.
Returns: PKey(void*).
***************************************************************/
PKey Get_WZ_ID(PElem elem) {
	char *ID = WarZone_ID((PWarZone)elem);
	return (PKey)ID;
}

/****************************************************************
function: Comp_WZ_ID.
abstract: compares two WZ elements ID's.
parameters: PKey1 and Pkey2 (type PKey).
Returns: true if both keys are the same, false otherwise.
***************************************************************/
bool Comp_WZ_ID(PKey pKey1, PKey pKey2) {
	if (pKey1 == NULL || pKey2 == NULL) return false;
	return !strcmp((char*)pKey1, (char*)pKey2);
}

/****************************************************************
function: WZ_Delete_Func.
abstract: Deletes a wz.
parameters: PElem.
returns: NONE.
***************************************************************/
void WZ_Delete_Func(PElem elem) {
	if (elem != NULL) {
		WarZone_Delete((PWarZone)elem);
	}
}

/****************************************************************
function: Wz_Print_Func.
abstract: prints the wz.
parameters: A pointer to an element.
***************************************************************/
void Wz_Print_Func(PElem Data) {
	if (Data == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	WarZone_Print((PWarZone)Data);
}

/****************************************************************
function: Wz_Duplicate_Func.
abstract: Duplicates the Wz.
parameters: A pointer to an element.
Returns: a Pointer to the element copied or NULL if failed.
***************************************************************/
PElem Wz_Duplicate_Func(PElem elem) {
	PWarZone WZ_Cpy = WarZone_Duplicate((PWarZone)(elem));
	if (WZ_Cpy == NULL) return NULL;
	return (PElem)WZ_Cpy;
}


/*squad user functions*/

/****************************************************************
function: Get_Squad_ID.
abstract: gets the squad ID.
parameters: A pointer to a Element.
Returns: PKey.
***************************************************************/
PKey Get_Squad_ID(PElem elem) {
	char *ID = Squad_ID((PSquad)elem);
	return (PKey)ID;
}

/****************************************************************
function: Comp_Squad_ID.
abstract: compares two squad elements ID's.
parameters: PKey1 and Pkey2 (type PKey).
Returns: true if both keys are the same, false otherwise.
***************************************************************/
bool Comp_Squad_ID(PKey pKey1, PKey pKey2) {
	if (pKey1 == NULL || pKey2 == NULL) return false;
	return !strcmp((char*)pKey1, (char*)pKey2);
}

/****************************************************************
function: Squad_Delete_Func.
abstract: Deletes a squad.
parameters: PElem.
returns: NONE.
***************************************************************/
void Squad_Delete_Func(PElem elem) {
	if (elem != NULL) {
		Squad_Delete((PSquad)elem);
	}
}

/****************************************************************
function: Squad_Print_Func.
abstract: prints the squad.
parameters: A pointer to an element.
***************************************************************/
void Squad_Print_Func(PElem Data) {
	if (Data == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	Squad_Print((PSquad)Data);
}

/****************************************************************
function: Squad_Duplicate_Func.
abstract: Duplicates the Squad.
parameters: A pointer to an element.
Returns: a Pointer to the element copied or NULL if failed.
***************************************************************/
PElem Squad_Duplicate_Func(PElem elem) {
	PSquad Squad_Cpy = Squad_Duplicate((PSquad)(elem));
	if (Squad_Cpy == NULL) return NULL;
	return (PElem)Squad_Cpy;
}


/**Funcs**/
PWarZone Check_If_WarZone_Exists(BF BattleField, char WarZone_ID[MAX_ID_LENGTH])
{	
	//check if ID is NULL
	if (WarZone_ID == NULL) return NULL;

	//check if warzone exists.
	PElem warzone;
	warzone = List_Get_Elem(BattleField->WarZones, (PKey)WarZone_ID); //the squad list.
	if (warzone == NULL) {  //couldn't find warzone.
		return	NULL; 
	}
	return warzone;
}

BF Create_Battlefield( 
					CLONE_FUNC clone_f, 
					DESTROY_FUNC Des_f, 
					COMPARE_KEYS_FUNC comp_f, 
					PRINT_FUNC Print_f,
					GET_KEY get_key_f)
{
	//creating a Battlefield struct.
	BF battlefield = (BF)malloc(sizeof(BattleField));
	if (battlefield == NULL) return NULL;

	//initializing the wz lists.
	battlefield->WarZones = List_Create(get_key_f, clone_f, Des_f, comp_f, Print_f);
	if (battlefield->WarZones == NULL) {
		free(battlefield);
		return NULL;
	}
	//initializing Battlefield.
	battlefield->initiated = true;
	return battlefield;
}

void BF_Delete(BF battlefield)
{
	if (battlefield == NULL) {
		return;
	}
	List_Delete(battlefield->WarZones);
	battlefield->WarZones =NULL;
	free(battlefield);
	battlefield =NULL;
}

Result BF_Add_WarZone(BF BATTLEFIELD, char WZ_ID[MAX_ID_LENGTH])
{
	Result added;
	PWarZone new_WarZone;

	//creating the new War Zone by it's ID.
	new_WarZone = WarZone_Create(WZ_ID, Squad_Duplicate_Func,Squad_Delete_Func,Comp_Squad_ID,Squad_Print_Func, Get_Squad_ID);

	//adding the new War Zone.
	added = List_Add_Elem(BATTLEFIELD->WarZones, (PElem)new_WarZone);

	//freeing allocated memory.
	WarZone_Delete(new_WarZone);

	return added;
}

Result BF_Remove_WarZone(BF Battlefield, char WZ_ID[MAX_ID_LENGTH])
{
	Result removed;

	//Removing the War Zone.
	removed = List_Remove_Elem(Battlefield->WarZones, (PKey)WZ_ID);
	return removed;
}

BF initiate_Battlefield_Func(void)
{
	BF bf = Create_Battlefield(Wz_Duplicate_Func, WZ_Delete_Func, Comp_WZ_ID, Wz_Print_Func, Get_WZ_ID);
	return bf;
}


void BF_Print(BF bf) {
	if (bf == NULL) {
		printf("Error: No Battlefield\n");
		return;
	}
	printf("Battlefield:\n");
	List_Print(bf->WarZones);
}

int BF_Raise_WarZone(BF Battlefield, char WZ_ID[MAX_ID_LENGTH])
{
	Result Alert_Level;
	PElem Wz; // will be used to get the squad element on the list.

	Wz = List_Get_Elem(Battlefield->WarZones, (PKey)WZ_ID); //the squad list.
	if (Wz == NULL) {
		printf("Error: No Such War Zone\n");
		return	FAILURE; //War Zone isn't in the warzone.
	}

	//Raising alert level in the war zone.
	Alert_Level = WarZone_Raise_Alert(Wz);
	return Alert_Level;
}

Result BF_Move_All_Squads(BF Battlefield, char dst_Wz_ID[MAX_ID_LENGTH])
{
	//get the war zone in level 3 alert Pointer.
	Result added;
	PWarZone WZ_LEVEL_3, cur_WZ;
	WZ_LEVEL_3 = List_Get_Elem(Battlefield->WarZones, (PKey)dst_Wz_ID);

	//add the first war zones squads.
	cur_WZ = List_Get_First(Battlefield->WarZones);
	if (cur_WZ == NULL) return FAILURE;
	added = War_Zone_Move_All_Squads(cur_WZ, WZ_LEVEL_3);
	
	//adding the rest of the src squads.
	while ((cur_WZ = List_Get_Next(Battlefield->WarZones)) != NULL) {
		added = War_Zone_Move_All_Squads(cur_WZ, WZ_LEVEL_3);
		
	}
	
	return added;
}

Result BF_Initialize_War_Zone_Alert_Level(BF Battlefield, char WZ_ID[MAX_ID_LENGTH])
{
	//get the war zone and change it alert level
	PWarZone wz;
	wz = List_Get_Elem(Battlefield->WarZones, (PKey)WZ_ID);

	//initialize alert level.
	War_Zone_Alert_Level_Zero(wz);
	return SUCCESS;
}

Result BF_Move_Squad_From_War_Zone(BF battle, char src[MAX_ID_LENGTH], char dst[MAX_ID_LENGTH], char Squad_ID[MAX_ID_LENGTH])
{	
	//get the pointers.
	PElem Source, Dest;
	Source = List_Get_Elem(battle->WarZones, (PKey)src);
	Dest = List_Get_Elem(battle->WarZones, (PKey)dst);

	//insert the squad
	Result moved;
	moved = War_Zone_Move_Squad(Source, Dest, Squad_ID);
	return moved;
}




