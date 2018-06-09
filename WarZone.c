#include "WarZone.h"

//the WarZone struct. contains the squads list in the warzone and it's level
//of alert level
typedef struct WarZone_ {
	PList Squads;
	int Alert_Level; //Alert level in the warzone
	char ID[MAX_ID_LENGTH];//WarZone ID.
}WarZone;



/*
Defining user functions. will be used by the list functions.
*/

/****************************************************************
function: Get_APC_ID.
abstract: gets the APC ID.
parameters: A pointer to a Element.
Returns: PKey.
***************************************************************/
PKey Get_APC_ID(PElem elem) {
	char *ID = APC_ID((P_APC)elem);
	return (PKey)ID;
}

/****************************************************************
function: Get_Sol_ID.
abstract: gets the soldiers ID.
parameters: A pointer to a an element.
Returns: PKey.
***************************************************************/
PKey Get_Sol_ID(PElem elem) {
	char *ID = Soldier_Get_ID((PSoldier)elem);
	return (PKey)ID;
}

/****************************************************************
function: Comp_ID.
abstract: compares two elements ID's.
parameters: PKey1 and Pkey2 (type PKey).
Returns: true if both keys are the same, false otherwise.
***************************************************************/
bool Comp_ID(PKey pKey1, PKey pKey2) {
	if (pKey1 == NULL || pKey2 == NULL) return false;
	return !strcmp((char*)pKey1, (char*)pKey2);
}

/****************************************************************
function: Sol_Delete.
abstract: Deletes a soldier.
parameters: PElem.
***************************************************************/
void sol_Delete_Func(PElem elem) {
	if (elem != NULL) {
		Soldier_Delete((PSoldier)elem);
	}
}

/****************************************************************
function: APC_Delete_Func.
abstract: Deletes an APC.
parameters: PElem.
***************************************************************/
void APC_Delete_Func(PElem elem) {
	if (elem != NULL) {
		APC_Delete((P_APC)elem);
	}
}

/****************************************************************
function: APC_Print_Func.
abstract: prints the APC and the soldiers inside it.
parameters: A pointer to an element.
***************************************************************/
void APC_Print_Func(PElem Data) {
	if (Data == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	APC_Print((P_APC)Data);
}

/****************************************************************
function: Sol_Print_Func.
abstract: prints the APC and the soldiers inside it.
parameters: A pointer to an element.
***************************************************************/
void Sol_Print_Func(PElem Data) {
	if (Data == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	Soldier_Print((PSoldier)Data);
}

/****************************************************************
function: APC_Dup.
abstract: Duplicates the APC.
parameters: A pointer to an element.
Returns: a Pointer to the element copied or NULL if failed.
***************************************************************/
PElem APC_Dup(PElem elem) {
	P_APC APC_Cpy = APC_Duplicate((P_APC)(elem));
	if (APC_Cpy == NULL) return NULL;
	return (PElem)APC_Cpy;
}

/****************************************************************
function: Soldier_Dup.
abstract: Duplicates the soldier.
parameters: A pointer to an element.
Returns: a Pointer to the element copied or NULL if failed.
***************************************************************/
PElem Soldier_Dup(PElem elem) {
	PSoldier sol_Cpy = Soldier_Duplicate((PSoldier)(elem));
	if (sol_Cpy == NULL) return NULL;
	return (PElem)sol_Cpy;
}





/*
Interface functions. Detailed in the WarZone.h file.
*/

PWarZone WarZone_Create(char ID[MAX_ID_LENGTH],
	CLONE_FUNC Squad_Duplicate_Func,
	DESTROY_FUNC Squad_Delete_Func,
	COMPARE_KEYS_FUNC Comp_Squad_ID,
	PRINT_FUNC Squad_Print_Func,
	GET_KEY Get_Squad_ID) {

	//creating a new warzone struct.
	PWarZone new_WarZone = (PWarZone)malloc(sizeof(WarZone));
	if (new_WarZone == NULL) return NULL;

	//initializing the squads.
	new_WarZone->Squads = List_Create(Get_Squad_ID,Squad_Duplicate_Func, Squad_Delete_Func, Comp_Squad_ID, Squad_Print_Func);
	if (new_WarZone->Squads == NULL) {
		free(new_WarZone);
		return NULL;
	}
	//initializing warzone alert level and ID.
	new_WarZone->Alert_Level = 0;
	strcpy(new_WarZone->ID, ID);
	return new_WarZone;
}

void WarZone_Delete(PWarZone WarZone) {
	if (WarZone == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	List_Delete(WarZone->Squads);
	free(WarZone);
}

void WarZone_Print(PWarZone WarZone) {
		if (WarZone == NULL) {
			printf(ARG_ERR_MSG);
			return;
		}
		printf("WarZone: %s , Alert State: %d\n\n",WarZone->ID,WarZone->Alert_Level);
		List_Print(WarZone->Squads);
}

PWarZone WarZone_Duplicate(PWarZone WarZone)
{
	//if WarZone pointer is NULL, exit.
	if (WarZone == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	//get the pointer to the squads lists.
	PList Squads = WarZone->Squads;

	//creating the new duplicant WarZone.
	PWarZone New_WarZone = WarZone_Create(WarZone->ID, List_Get_Clone_Func(Squads), List_Get_Des_Func(Squads), List_Get_Cmp_Func(Squads), List_Get_Print_Func(Squads), List_Get_Key_Func(Squads));
	if (New_WarZone == NULL) {  //check memory allocation.
		return NULL;
	}

	//duplicating the squad with all it's soldiers and APC's.
	List_Duplicate(WarZone->Squads, New_WarZone->Squads);

	//initializing alert level.
	New_WarZone->Alert_Level = WarZone->Alert_Level;

	return New_WarZone;
}

int WarZone_Raise_Alert(PWarZone WarZone)
{
	//check if warzone exists. if not return error value of -1.
	if (WarZone == NULL) return -1;

	//raise alert level. Max is 3.
	if(WarZone->Alert_Level < 3)
		WarZone->Alert_Level++;
	return WarZone->Alert_Level;
}

Result WarZone_Add_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH])
{
	Result added;
	PSquad squad;

	//creating the new squad by it's ID.
	squad = Squad_Create(Squad_ID, Soldier_Dup, APC_Dup,
							sol_Delete_Func, APC_Delete_Func,
							Comp_ID,//the same for soldiers and APC's
							Sol_Print_Func, APC_Print_Func,
							Get_Sol_ID, Get_APC_ID);
	
	//adding the new squad.
	added = List_Add_Elem(warzone->Squads,(PElem)squad);
	if (added == FAILURE) {
		printf("Error: Squad Already Exists\n");
	}

	Squad_Delete(squad);

	return added;
}

Result WarZone_Add_Sol_To_Squad(PWarZone warzone,char Squad_ID[MAX_ID_LENGTH], char Sol_ID[MAX_ID_LENGTH], char Sol_Pos[MAX_ID_LENGTH])
{
	Result added;
	PElem squad; // will be used to get the squad element on the list.
	
	//getting the squad squads list,
	squad = List_Get_Elem(warzone->Squads, (PKey)Squad_ID); //the squad list.
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return	FAILURE; //squad isn't in the warzone.
	}

	//adding the soldier to the squad soldiers list.
	added = Squad_Add_Soldier(squad, Sol_ID, Sol_Pos);
	return added;
}

Result WarZone_Add_APC_To_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH], char APC_ID[MAX_ID_LENGTH])
{
	Result added;
	PElem squad; // will be used to get the squad element on the list.

	//getting the squad squads list,
	squad = List_Get_Elem(warzone->Squads, (PKey)Squad_ID); //the squad list.
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return	FAILURE; //squad isn't in the warzone.
	}

	 //adding the APC to the squad APC's list.
	added = Squad_Add_APC((PSquad)squad, APC_ID);
	return added;
}

Result	WarZone_Add_Sol_To_APC_In_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH],
								char Sol_Id[MAX_ID_LENGTH], char APC_ID[MAX_ID_LENGTH]) {
	Result added;
	PElem squad; // will be used to get the squad element on the list.

				 //getting the squad squads list,
	squad = List_Get_Elem(warzone->Squads, (PKey)Squad_ID);    //the squad list.
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return	FAILURE; //squad isn't in the warzone.
	}

	 //adding the soldier to the APC in the squad.
	added = Squad_Insert_Sold_APC((PSquad)squad, Sol_Id,APC_ID);

	return added;

}

Result	WarZone_APC_Pop_Found_In_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH],
										char APC_ID[MAX_ID_LENGTH]) {
	Result Popped;
	PElem squad; // will be used to get the squad element on the list.

				 //getting the squad squads list,
	squad = List_Get_Elem(warzone->Squads, (PKey)Squad_ID);    //the squad list.
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return	FAILURE; //squad isn't in the warzone.
	}

	 //removing the soldier to the APC in the squad.
	Popped = Squad_APC_Pop((PSquad)squad, APC_ID);
	return Popped;
}

Result	WarZone_Remove_Soldier_From_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH],
									char Sol_ID[MAX_ID_LENGTH]) {
	Result Removed;
	PElem squad; // will be used to get the squad element on the list.

				 //getting the squad squads list,
	squad = List_Get_Elem(warzone->Squads, (PKey)Squad_ID);    //the squad list.
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return	FAILURE; //squad isn't in the warzone.
	}

	 //removing the soldier to the APC in the squad.
	Removed = Squad_Delete_Soldier((PSquad)squad, Sol_ID);
	return Removed;
}

Result	WarZone_Remove_APC_From_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH],
										char APC_ID[MAX_ID_LENGTH]) {
	Result Removed;
	PElem squad; // will be used to get the squad element on the list.

	//getting the squad squads list,
	squad = List_Get_Elem(warzone->Squads, (PKey)Squad_ID);    //the squad list.
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return	FAILURE; //squad isn't in the warzone.
	}

	//removing the soldier to the APC in the squad.
	Removed = Squad_Delete_APC((PSquad)squad, APC_ID);
	return Removed;
}

Result	WarZone_Remove_Squad(PWarZone warzone, char Squad_ID[MAX_ID_LENGTH]) {
	Result Removed;
	PElem squad; // will be used to get the squad element on the list.

	 //getting the squad squad list,
	squad = List_Get_Elem(warzone->Squads, (PKey)Squad_ID);    //the squad list.
	if (squad == NULL) {
		printf("Error: No Such Squad\n");
		return	FAILURE; //squad isn't in the warzone.
	}

	//removing the squad.
	Removed = List_Remove_Elem(warzone->Squads,(PKey)Squad_ID);
	return SUCCESS;
}

char * WarZone_ID(PWarZone warzone)
{
	return	warzone->ID;
}

Result War_Zone_Move_Squad(PWarZone src, PWarZone dst, char Squad_ID[MAX_ID_LENGTH])
{
	
	//check if the squad exists.
	PElem Squad;
	PSquad cpy_sqd;
	Squad = List_Get_Elem(src->Squads, (PKey)Squad_ID);
	if (Squad == NULL) {
		printf("Error: No Such Squad\n");
		return FAILURE;
	}

	//moving the squad to the destination war zone.
	Result Moved;
	cpy_sqd = Squad_Duplicate(Squad);
	Moved = List_Add_Elem(dst->Squads, (PElem)cpy_sqd);

	//Removing original Squad
	Result Deleted;
	Deleted = List_Remove_Elem(src->Squads, (PKey)Squad_ID);

	//freeing allocated memory.
	Squad_Delete(cpy_sqd);
	return Moved;
}

Result War_Zone_Move_All_Squads(PWarZone src, PWarZone dst)
{
	
	return	Add_Two_Lists(src->Squads,dst->Squads);

}

void War_Zone_Alert_Level_Zero(PWarZone wz)
{
	wz->Alert_Level = 0;
}


//int main() {
//	char szLine[MAX_INPUT_LINE];
//	char* delimiters = " \t\n";
//	char* WZ_ID;
//
//	while (fgets(szLine, MAX_INPUT_LINE, stdin)) {
//		WZ_ID = strtok(szLine, delimiters);
//		//PWarZone wz = WarZone_Create(WZ_ID, Squad_Duplicate_Func, Squad_Delete_Func, Comp_Squad_ID, Squad_Print_Func, Get_Squad_ID);
//		//
//		PWarZone wz = (PWarZone)malloc(sizeof(WarZone));
//		free(wz);
//		////PSquad squad = Squad_Create("sq1",Soldier_Dup, APC_Dup,
//		////	sol_Delete_Func, APC_Delete_Func,
//		////	Comp_ID,//the same for soldiers and APC's
//		////	Sol_Print_Func, APC_Print_Func,
//		////	Get_Sol_ID, Get_APC_ID);
//		//WarZone_Add_Squad(wz, "sq1");
//
//		//WarZone_Add_Sol_To_Squad(wz, "sq1", "1", "m");
//		//WarZone_Add_Sol_To_Squad(wz, "sq1", "2", "m");
//		//WarZone_Add_Sol_To_Squad(wz, "sq1", "3", "m");
//		//WarZone_Add_Sol_To_Squad(wz, "sq1", "4", "m");
//		//WarZone_Add_Sol_To_Squad(wz, "sq1", "5", "m");
//		//WarZone_Add_Sol_To_Squad(wz, "sq1", "6", "m");
//		//WarZone_Add_Sol_To_Squad(wz, "sq1", "6", "m");
//		//WarZone_Add_APC_To_Squad(wz, "sq1", "APC1");
//
//		//WarZone_Add_Sol_To_APC_In_Squad(wz, "sq1", "3", "APC1");
//		//WarZone_Add_Sol_To_APC_In_Squad(wz, "sq1", "3", "APC2");
//		//WarZone_Add_Sol_To_APC_In_Squad(wz, "sq1", "1", "APC1");
//		//WarZone_Remove_Soldier_From_Squad(wz, "sq1", "1");
//		//WarZone_Print(wz);
//		//printf("\n\n");
//
//		////WarZone_APC_Pop_Found_In_Squad(wz, "sq1", "APC2");
//		//WarZone_APC_Pop_Found_In_Squad(wz, "sq1", "APC1");
//		//WarZone_APC_Pop_Found_In_Squad(wz, "sq1", "APC1");
//		//WarZone_APC_Pop_Found_In_Squad(wz, "sq1", "APC1");
//		//WarZone_Print(wz);
//		//Result res = WarZone_APC_Pop_Found_In_Squad(wz, "sq2", "APC1");
//		//printf("\n\n");
//		//WarZone_Print(wz);
//
//		//WarZone_Remove_Soldier_From_Squad(wz, "sq1", "1");
//		//printf("\n\n");
//		//WarZone_Print(wz);
//
//
//		//WarZone_Remove_APC_From_Squad(wz, "sq2", "APC1");
//		//WarZone_Remove_APC_From_Squad(wz, "sq1", "APC1");
//		//WarZone_Remove_APC_From_Squad(wz, "sq1", "APC2");
//
//		//printf("\n\n");
//		///*WarZone_Remove_Squad(wz, "sq1");
//		//WarZone_Print(wz);*/
//		//WarZone_Delete(wz);
//		//wz = NULL;
//		
//	}
//	return 0;
//}