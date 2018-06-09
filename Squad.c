#include "Squad.h"
#include "List.h"


//the squad struct. contains a soldiers and APC lists. the soldiers number(count)
//and the squad ID.
typedef struct Squad_ {
	PList Soldiers;
	PList APCs;
	int Count;//Number of soldiers in the squad.
	char ID[MAX_ID_LENGTH];//squad ID.
}Squad;

extern PList objects_ID;



/*
Interface functions. Detailed in the Squad.h file.
*/

PSquad Squad_Create(char ID[MAX_ID_LENGTH],
					CLONE_FUNC Soldier_Dup, CLONE_FUNC APC_Dup,
					DESTROY_FUNC sol_Delete_Func, DESTROY_FUNC APC_Delete_Func,
					COMPARE_KEYS_FUNC Comp_ID,//the same for soldiers and APC's
					PRINT_FUNC Sol_Print_Func, PRINT_FUNC APC_Print_Func,
					GET_KEY Get_Sol_ID, GET_KEY Get_APC_ID)
{
 //creating a new squad struct.
	PSquad new_Squad = (PSquad)malloc(sizeof(Squad));
	if (new_Squad == NULL) return NULL;
	//initializing the soldiers and APC's lists.
	new_Squad->Soldiers = List_Create(Get_Sol_ID, Soldier_Dup, sol_Delete_Func, Comp_ID, Sol_Print_Func);
	if (new_Squad->Soldiers == NULL) {
		free(new_Squad);
		return NULL;
	}
	new_Squad->APCs = List_Create(Get_APC_ID, APC_Dup, APC_Delete_Func, Comp_ID, APC_Print_Func);
	if (new_Squad->APCs == NULL) {
		//List_Delete(new_Squad->Soldiers);
		free(new_Squad);
		return NULL;
	}
	
	new_Squad->Count = 0;    //initializing the soldiers counter.
	strcpy(new_Squad->ID, ID);    //adding the squad ID
	return new_Squad;
}


void Squad_Delete(PSquad Squad)
{
	if (Squad != NULL) {
		List_Delete(Squad->Soldiers);
		List_Delete(Squad->APCs);
		Squad->Soldiers = NULL;
		Squad->APCs = NULL;
		free(Squad);
		Squad = NULL;
	}
}

void Squad_Print(PSquad squad)
{
	if (squad == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	//printing the squad.
	printf("Squad: %s , Total troops: %d\n", squad->ID, squad->Count);
	printf("APCs:\n");
	List_Print(squad->APCs);
	printf("Soldiers:\n");
	List_Print(squad->Soldiers);
	printf("\n");
}


PSquad Squad_Duplicate(PSquad Squad) {
	//if squad pointer is NULL, exit.
	if (Squad == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	//get the pointers to the soldiers and APC's list.
	PList Soldiers = Squad->Soldiers;
	PList APCs = Squad->APCs;
	//creating the new duplicant squad.
	PSquad New_Squad = Squad_Create(Squad->ID, List_Get_Clone_Func(Soldiers), List_Get_Clone_Func(APCs), List_Get_Des_Func(Soldiers), List_Get_Des_Func(APCs),
		List_Get_Cmp_Func(Soldiers), List_Get_Print_Func(Soldiers), List_Get_Print_Func(APCs), List_Get_Key_Func(Soldiers), List_Get_Key_Func(APCs));
	if (New_Squad == NULL) {  //check memory allocation.
		return NULL;
	}

	//duplicating soldiers and APC's lists.
	List_Duplicate(Squad->Soldiers, New_Squad->Soldiers);
	List_Duplicate(Squad->APCs, New_Squad->APCs);

	//initializing new squad count.
	New_Squad->Count = Squad->Count;

	//Delete the original squad.
	//Squad_Delete(Squad);

	return New_Squad;
}

Result Squad_Add_Soldier(PSquad squad, char ID[MAX_ID_LENGTH], char POS[MAX_ID_LENGTH])
{	
	//creating the soldier.
	Result res;
	PElem elem;
	elem = List_Get_Elem(objects_ID, (PKey)ID);
	if (elem != NULL) {
		printf("Error: Soldier Already Exists\n");
		return FAILURE;
	}

	PSoldier soldier = Soldier_Create(ID, POS);
	res = List_Add_Elem(squad->Soldiers, (PElem)soldier); //NOTE: adding a copy elem.
	if (res == SUCCESS)
		squad->Count++;
	
	//freeing allocated memory.
	Soldier_Delete(soldier);

	return res;
}

Result Squad_Add_APC(PSquad squad, char ID[MAX_ID_LENGTH])
{
	Result res;
	PElem elem;
	elem = List_Get_Elem(objects_ID, (PKey)ID);
	if (elem != NULL) {
		printf("Error: APC Already Exists\n");
		return FAILURE;
	}

	//creating an EMPTY APC.
	P_APC APC = APC_Create(ID);
	if (APC == NULL) return FAILURE;
	
	//add the APC to the list of APC's
	res = List_Add_Elem(squad->APCs, (PElem)APC);

	//Removing the allocated memory.
	APC_Delete(APC);

	return res;
}

Result Squad_Insert_Sold_APC(PSquad squad, char Sol_ID[MAX_ID_LENGTH], char APC_ID[MAX_ID_LENGTH])
{	
	//checking if the soldier and APC belong to the squad.
	PElem sol, APC;
	APC = List_Get_Elem(squad->APCs, (PKey)APC_ID);
	
	//check if APC exists.
	if (APC == NULL) {
		printf("Error: No Such APC\n");
		return	FAILURE;
	}

	//check if soldier exists.
	sol = List_Get_Elem(squad->Soldiers, (PKey)Sol_ID);
	if (sol == NULL) {
		printf("Error: No Such Soldier\n");
		return FAILURE;
	}
	
	//inserting the soldier copy(!!!) to the APC.
	Result insert;
	PSoldier sol_copy = Soldier_Create(Soldier_Get_ID((PSoldier)sol), Soldier_Get_Pos((PSoldier) sol));
	insert = APC_Insert_Soldier((P_APC)APC, sol_copy);
	if (insert == FAILURE) return FAILURE; //if APC is full return FAILURE.

	//Deleting the soldier from the soldiers list.
	Result remove_sol;
	remove_sol = List_Remove_Elem(squad->Soldiers, (PKey)Sol_ID);
	return remove_sol;
}

Result Squad_APC_Pop(PSquad squad, char APC_ID[MAX_ID_LENGTH])
{	//checking if the APC is int the squad.
	PElem APC;

	//check if APC exists.
	APC = List_Get_Elem(squad->APCs, (PKey)APC_ID);
	if (APC == NULL) {
		printf("Error: No Such APC\n");
		return	FAILURE;
	}

	//removing the top soldier from the APC.
	PSoldier rem_sol;
	rem_sol = APC_Pop((P_APC)APC);
	if (rem_sol == NULL) return FAILURE;

	//Adding the soldier to the squad.
	Result sol_added;
	sol_added = List_Add_Elem(squad->Soldiers, (PElem)rem_sol);

	//free allocated memory.
	Soldier_Delete(rem_sol);

	return sol_added;
}

Result Squad_Delete_Soldier(PSquad squad, char Sol_ID[MAX_ID_LENGTH])
{
	//check if list is empty.
	if (squad == NULL) return FAILURE;

	//remove soldier from list.
	Result removed;
	removed = List_Remove_Elem(squad->Soldiers, (PKey)Sol_ID);
	
	//if the soldier's not in the squad print an Error message
	if (removed == FAILURE)
		printf("Error: No Such Soldier\n");
	else
		squad->Count--;			//soldier was Removed. decreasing soldier number.
	
	return removed;
}

Result Squad_Delete_APC(PSquad squad, char APC_ID[MAX_ID_LENGTH])
{
	P_APC APC;
	int decrease_sol;

	//check if squad is empty.
	if (squad == NULL) return FAILURE;

	//decrease number of soldiers.
	APC = List_Get_Elem(squad->APCs, (PKey)APC_ID);
	if (APC == NULL) {
		printf("Error: No Such APC\n");
		return FAILURE;
	}


	decrease_sol = Get_Sol_Count(APC);
	squad->Count -= decrease_sol;

	//remove APC and soldiers on it.
	Result removed;
	removed = List_Remove_Elem(squad->APCs, (PKey)APC_ID);
	
	return removed;
}

char * Squad_ID(PSquad squad)
{
	char *ID = squad->ID;
	return ID;
}
