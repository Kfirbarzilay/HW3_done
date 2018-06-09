/**includes**/
#include "defs.h"
#include "Battlefield.h"
#include "WarZone.h"
#include "Squad.h"
#include "Soldier.h"
#include "APC.h"
#include "List.h"


//creating the commands struct.
typedef struct Command_ {
	int command_Num;
	char* command_Data;
}Command, *Pcommand;

/*functions*/
/****************************************************************
function: Command_Duplicate.
abstract: Duplicates the command.
parameters: A pointer to a command, Pcommand.
Returns: Pcommand, a pointer  to a commend element.
***************************************************************/
Pcommand Command_Duplicate(Pcommand command);

/****************************************************************
function: Del_Command.
abstract: Deletes the command.
parameters: A pointer to a command, Pcommand.
Returns: NONE.
***************************************************************/
void Del_Command(Pcommand command);












//creating the ID's struct.
typedef struct IDs_ {
	char* obj_ID;
}IDs, *PIDs;


//user functions for battlefield Id list.

/****************************************************************
function: Get_warrior_ID.
abstract: gets the ID.
parameters: A pointer to a Element.
Returns: PKey(void*).
***************************************************************/
PKey Get_warrior_ID(PElem elem) {
	PIDs ID = (PIDs)elem;
	return (PKey)ID->obj_ID;
}

/****************************************************************
function: Comp_Obj_ID.
abstract: compares two ID's.
parameters: PKey1 and Pkey2 (type PKey).
Returns: true if both keys are the same, false otherwise.
***************************************************************/
bool Comp_Obj_ID(PKey pKey1, PKey pKey2) {
	if (pKey1 == NULL || pKey2 == NULL) return false;
	return (!strcmp((char*)pKey1, (char*)pKey2));
}

/****************************************************************
function: ID_Delete_Func.
abstract: Deletes an ID from list.
parameters: PElem.
returns: NONE.
***************************************************************/
void ID_Delete_Func(PElem elem) {
	if (elem != NULL) {
		PIDs ID = (PIDs)elem;
		free(ID->obj_ID);
		free(ID);
	}
}

/****************************************************************
function: ID_Duplicate_Func.
abstract: Duplicates the command.
parameters: A pointer to an element.
Returns: a Pointer to the element copied or NULL if failed.
***************************************************************/
PElem ID_Duplicate_Func(PElem elem) {
	
	//cast to ID struct type
	PIDs ID = (PIDs)elem;
	
	//create the copy.
	PIDs ID_CPY = (PIDs)malloc(sizeof(IDs));
	if (ID_CPY == NULL) return NULL;
	
	ID_CPY->obj_ID = (char*)malloc(strlen(ID->obj_ID) + 1);
	if(ID_CPY->obj_ID == NULL){
		free(ID_CPY);
		return NULL;
	}
	
	//copy the ID
	strcpy(ID_CPY->obj_ID, ID->obj_ID);
	
	return (PElem)ID_CPY;
}

/****************************************************************
function: ID_Print_Func.
abstract: prints the Command. //only for debug purposes.
parameters: A pointer to an element.
***************************************************************/
void ID_Print_Func(PElem Data) {
	//empty.
}


/****************************************************************
function: Create_ID_Object.
	abstract : creates the object id.
	parameters: char array.
	returns : A pointer to an element.
***************************************************************/
PIDs Create_ID_Object(char ID[MAX_ID_LENGTH]) {
	//allocating new command memory.
	PIDs new_ID = (PIDs)malloc(sizeof(*new_ID));
	if (new_ID == NULL) return NULL;
	new_ID->obj_ID = (char*)malloc(strlen(ID) + 1);		//+1 is for '\0'
	if (new_ID->obj_ID == NULL) {
		free(new_ID);
		return NULL;
	}
	strcpy(new_ID->obj_ID, ID);			//copying the ID.
	return new_ID;
}







//user functions for command list.

/****************************************************************
function: Get_Command.
abstract: gets the command num.
parameters: A pointer to a Element.
Returns: PKey(void*).
***************************************************************/
PKey Get_Command_Num(PElem elem) {
	Pcommand CM = (Pcommand)elem;
	return (PKey)(&(CM->command_Num));
}

/****************************************************************
function: Comp_Command_Num.
abstract: compares two command numbers.
parameters: PKey1 and Pkey2 (type PKey).
Returns: true if both keys are the same, false otherwise.
***************************************************************/
bool Comp_Command_Num(PKey pKey1, PKey pKey2) {
	if (pKey1 == NULL || pKey2 == NULL) return false;
	return ((*(int*)pKey1) == (*(int*)pKey2));
}

/****************************************************************
function: command_Delete_Func.
abstract: Deletes a command after execution.
parameters: PElem.
returns: NONE.
***************************************************************/
void command_Delete_Func(PElem elem) {
	if (elem != NULL) {
		Del_Command((Pcommand)elem);
	}
}

/****************************************************************
function: Command_Duplicate_Func.
abstract: Duplicates the command.
parameters: A pointer to an element.
Returns: a Pointer to the element copied or NULL if failed.
***************************************************************/
PElem Command_Duplicate_Func(PElem elem) {
	Pcommand Cm_Cpy = Command_Duplicate((Pcommand)(elem));
	if (Cm_Cpy == NULL) return NULL;
	return (PElem)Cm_Cpy;
}

/****************************************************************
function: Command_Print_Func.
abstract: prints the Command. //only for debug purposes.
parameters: A pointer to an element.
***************************************************************/
void Command_Print_Func(PElem Data) {
	/*if (Data == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	printf((PWarZone)Data);*/
}

Pcommand Command_Duplicate(Pcommand CM){
	//if command is NULL exit.
	if (CM == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	//creating the new duplicant command.
	Pcommand New_Command = (Pcommand)malloc(sizeof(Command));
	if (New_Command == NULL) {  //check memory allocation.
		return NULL;
	}
	
	//copying the command itself.
	New_Command->command_Data = (char*)malloc(strlen(CM->command_Data) + 1);		//+1 is for '\0'
	if (New_Command->command_Data == NULL) {
		free(New_Command);
		return NULL;
	}

	//copying command number and the command itself.
	strcpy(New_Command->command_Data, CM->command_Data);
	New_Command->command_Num = CM->command_Num;
	return New_Command;
}

void Del_Command(Pcommand CM) {
	free(CM->command_Data);
	free(CM);
}

Result check_If_Valid(char* command) {

	//all are valid commands.
	if (!strcmp(command, "Create_B")) return SUCCESS;
	if (!strcmp(command, "Add_W")) return SUCCESS;
	if (!strcmp(command, "Del_W")) return SUCCESS;
	if (!strcmp(command, "R_W")) return SUCCESS;
	if (!strcmp(command, "Add_Sq")) return SUCCESS;
	if (!strcmp(command, "Del_Sq")) return SUCCESS;
	if (!strcmp(command, "M_Sq")) return SUCCESS;
	if (!strcmp(command, "Add_Sold")) return SUCCESS;
	if (!strcmp(command, "Del_Sold")) return SUCCESS;
	if (!strcmp(command, "Add_APC")) return SUCCESS;
	if (!strcmp(command, "Del_APC")) return SUCCESS;
	if (!strcmp(command, "Sold_Insert")) return SUCCESS;
	if (!strcmp(command, "APC_Pop")) return SUCCESS;
	if (!strcmp(command, "Print")) return SUCCESS;

	//not a valid command
	printf("Error: Illegal Command\n");
	return FAILURE;

}




/****************************************************************
function: Add_W.
abstract: Adds a WarZone.
parameters: Command Arguments in string array, number of Args - int
			a pointer to the battlefield - BF.
returns: SUCCESS when Added and FAILURE otherwise.
***************************************************************/
Result Add_W(char* Command_Arguments[], int Args_Num, BF Battlefield) {

	//first check if the war zone already exists. if so, can't add it.
	PWarZone wz;
	wz = Check_If_WarZone_Exists(Battlefield, Command_Arguments[1]);   //Command_Arguments[1] == WarZone ID.
	if (wz != NULL) {
		printf("Error: War Zone Already Exists\n");
		return FAILURE;
	}
	
	//warzone doesn't exist. add it to battlefield.
	char WZ_ID[MAX_ID_LENGTH];
	strcpy(WZ_ID, Command_Arguments[1]);
	return BF_Add_WarZone(Battlefield, WZ_ID);
}

/****************************************************************
function: Del_W.
abstract: Removes a WarZone.
parameters: Command Arguments in string array, number of Args - int
			a pointer to the battlefield - BF.
returns: SUCCESS when removed and FAILURE otherwise.
***************************************************************/
Result Del_W(char* Command_Arguments[], int Args_Num, BF Battlefield) {

	//first check if the war zone exists. if not, can't remove it.
	PWarZone wz;
	wz = Check_If_WarZone_Exists(Battlefield, Command_Arguments[1]);   //Command_Arguments[1] == WarZone ID.
	if (wz == NULL) {
		printf("Error: No Such War Zone\n");
		return FAILURE;
	}

	//warzone exists.Remove it from battlefield.
	char WZ_ID[MAX_ID_LENGTH];
	strcpy(WZ_ID, Command_Arguments[1]);
	return BF_Remove_WarZone(Battlefield, WZ_ID);
}

/****************************************************************
function: WarZone_Add_Squad_Func.
abstract: adds a squad to a WarZone.
parameters: Command Arguments in string array, number of Args - int
			a pointer to the battlefield - BF.
returns: SUCCESS when squad added and FAILURE otherwise.
***************************************************************/
Result WarZone_Add_Squad_Func(char* Command_Arguments[], int Args_Num, BF Battlefield, PList objects_ID) {
	
	//first check if the war zone exists. 
	PWarZone wz;
	wz = Check_If_WarZone_Exists(Battlefield, Command_Arguments[1]);   //Command_Arguments[1] == WarZone ID.
	if (wz == NULL) {
		printf("Error: No Such War Zone\n");
		return FAILURE;
	}
	
	//check if squad exists.
	PElem sq;
	sq = List_Get_Elem(objects_ID, (PKey)Command_Arguments[2]);
	if (sq != NULL) {
		printf("Error: Squad Already Exists\n");
		return FAILURE;
	}
    
	//Add the squad.
	Result added;
	char Squad_ID[MAX_ID_LENGTH];
	strcpy(Squad_ID, Command_Arguments[2]);
	added =  WarZone_Add_Squad(wz, Squad_ID);
	if (added == FAILURE) return FAILURE;
	
	//insert the new object ID
	PIDs new_Obj_ID;
	new_Obj_ID = Create_ID_Object(Squad_ID);
	added = List_Add_Elem(objects_ID, (PElem)new_Obj_ID);
	
	//free allocated memory.
	ID_Delete_Func((PElem)new_Obj_ID);
	return added;
}


/****************************************************************
function: WarZone_Del_Squad_Func.
abstract: adds a squad to a WarZone.
parameters: Command Arguments in string array, number of Args - int
a pointer to the battlefield - BF.
returns: SUCCESS when squad added and FAILURE otherwise.
***************************************************************/
Result WarZone_Del_Squad_Func(char* Command_Arguments[], int Args_Num, BF Battlefield, PList objects_ID) {

	//first check if the war zone exists.
	PWarZone wz;
	wz = Check_If_WarZone_Exists(Battlefield, Command_Arguments[1]);   //Command_Arguments[1] == WarZone ID.
	if (wz == NULL) {
		printf("Error: No Such War Zone\n");
		return FAILURE;
	}

	//Delete the squad.
	Result removed;
	char Squad_ID[MAX_ID_LENGTH];
	strcpy(Squad_ID, Command_Arguments[2]);
	removed =  WarZone_Remove_Squad(wz, Squad_ID);
	if (removed == FAILURE) return FAILURE;

	//remove the ID from the object list.
	removed = List_Remove_Elem(objects_ID, Squad_ID);
	return SUCCESS;
}

/****************************************************************
function: WarZone_Add_Sol_To_Squad_Func.
abstract: adds a soldier to a squad in a WarZone.
parameters: Command Arguments in string array, number of Args - int
			a pointer to the battlefield - BF.
returns: SUCCESS when squad added and FAILURE otherwise.
***************************************************************/
Result WarZone_Add_Sol_To_Squad_Func(char* Command_Arguments[], int Args_Num, BF Battlefield, PList objects_ID) {

	//first check if the war zone exists.
	PWarZone wz;
	wz = Check_If_WarZone_Exists(Battlefield, Command_Arguments[1]);   //Command_Arguments[1] == WarZone ID.
	if (wz == NULL) {
		printf("Error: No Such War Zone\n");
		return FAILURE;
	}

	//copying ID's.
	char Squad_ID[MAX_ID_LENGTH];
	char Sol_ID[MAX_ID_LENGTH];
	char Sol_POS[MAX_ID_LENGTH];
	strcpy(Squad_ID, Command_Arguments[2]);
	strcpy(Sol_ID, Command_Arguments[3]);
	strcpy(Sol_POS, Command_Arguments[4]);

	//adding the soldier.
	Result added;
	added = WarZone_Add_Sol_To_Squad(wz, Squad_ID, Sol_ID, Sol_POS);
	if (added == FAILURE) return FAILURE;

	//adding to objects list.
	PIDs new_Obj_ID;
	new_Obj_ID = Create_ID_Object(Sol_ID);
	added = List_Add_Elem(objects_ID, (PElem)new_Obj_ID);

	//free allocated memory.
	ID_Delete_Func((PElem)new_Obj_ID);
	return added;

}

/****************************************************************
function: WarZone_Remove_Soldier_From_Squad_Func.
abstract: adds a soldier to a squad in a WarZone.
parameters: Command Arguments in string array, number of Args - int
a pointer to the battlefield - BF.
returns: SUCCESS when squad added and FAILURE otherwise.
***************************************************************/
Result WarZone_Remove_Soldier_From_Squad_Func(char* Command_Arguments[], int Args_Num, BF Battlefield, PList objects_ID) {

	//first check if the war zone exists.
	PWarZone wz;
	wz = Check_If_WarZone_Exists(Battlefield, Command_Arguments[1]);   //Command_Arguments[1] == WarZone ID.
	if (wz == NULL) {
		printf("Error: No Such War Zone\n");
		return FAILURE;
	}

	//warzone exists.
	//copying ID's.
	char Squad_ID[MAX_ID_LENGTH];
	char Sol_ID[MAX_ID_LENGTH];
	strcpy(Squad_ID, Command_Arguments[2]);
	strcpy(Sol_ID, Command_Arguments[3]);

	//removing soldier.
	Result removed;
	removed = WarZone_Remove_Soldier_From_Squad(wz, Squad_ID, Sol_ID);
	if (removed == FAILURE) return FAILURE;

	//remove from objects list.
	removed = List_Remove_Elem(objects_ID, (PKey)Sol_ID);
	return removed;
}

/****************************************************************
function: WarZone_Add_APC_To_Squad_Func.
abstract: adds an APC to a squad in a WarZone.
parameters: Command Arguments in string array, number of Args - int
		a pointer to the battlefield - BF.
returns: SUCCESS when APC added and FAILURE otherwise.
***************************************************************/
Result WarZone_Add_APC_To_Squad_Func(char* Command_Arguments[], int Args_Num, BF Battlefield, PList objects_ID) {

	//first check if the war zone exists.
	PWarZone wz;
	wz = Check_If_WarZone_Exists(Battlefield, Command_Arguments[1]);   //Command_Arguments[1] == WarZone ID.
	if (wz == NULL) {
		printf("Error: No Such War Zone\n");
		return FAILURE;
	}

	//warzone exists.
	//copying ID's.
	char Squad_ID[MAX_ID_LENGTH];
	char APC_ID[MAX_ID_LENGTH];
	strcpy(Squad_ID, Command_Arguments[2]);
	strcpy(APC_ID, Command_Arguments[3]);

	//adding the APC to squad.
	Result added;
	added = WarZone_Add_APC_To_Squad(wz, Squad_ID, APC_ID);
	if (added == FAILURE) return FAILURE;

	//adding to objects list.
	PIDs new_Obj_ID;
	new_Obj_ID = Create_ID_Object(APC_ID);
	added = List_Add_Elem(objects_ID, (PElem)new_Obj_ID);

	//free allocated memory.
	ID_Delete_Func((PElem)new_Obj_ID);
	return added;
}

/****************************************************************
function: WarZone_Remove_APC_From_Squad_Func.
abstract: adds an APC to a squad in a WarZone.
parameters: Command Arguments in string array, number of Args - int
a pointer to the battlefield - BF.
returns: SUCCESS when APC added and FAILURE otherwise.
***************************************************************/
Result WarZone_Remove_APC_From_Squad_Func(char* Command_Arguments[], int Args_Num, BF Battlefield, PList objects_ID) {

	//first check if the war zone exists.
	PWarZone wz;
	wz = Check_If_WarZone_Exists(Battlefield, Command_Arguments[1]);   //Command_Arguments[1] == WarZone ID.
	if (wz == NULL) {
		printf("Error: No Such War Zone\n");
		return FAILURE;
	}

	//warzone exists.
	//copying ID's.
	char Squad_ID[MAX_ID_LENGTH];
	char APC_ID[MAX_ID_LENGTH];
	strcpy(Squad_ID, Command_Arguments[2]);
	strcpy(APC_ID, Command_Arguments[3]);

	//removing APC.
	Result removed;
	removed = WarZone_Remove_APC_From_Squad(wz, Squad_ID, APC_ID);
	if (removed == FAILURE) return FAILURE;

	//remove from objects list.
	removed = List_Remove_Elem(objects_ID, (PKey)APC_ID);
	return removed;
}

/****************************************************************
function: WarZone_Add_Sol_To_APC_In_Squad_Func.
abstract: adds a soldier to an Existing APC.
parameters: Command Arguments in string array, number of Args - int
			a pointer to the battlefield - BF.
returns: SUCCESS when Soldier added and FAILURE otherwise.
***************************************************************/
Result WarZone_Add_Sol_To_APC_In_Squad_Func(char* Command_Arguments[], int Args_Num, BF Battlefield, PList objects_ID) {

	//first check if the war zone exists.
	PWarZone wz;
	wz = Check_If_WarZone_Exists(Battlefield, Command_Arguments[1]);   //Command_Arguments[1] == WarZone ID.
	if (wz == NULL) {
		printf("Error: No Such War Zone\n");
		return FAILURE;
	}

	//warzone exists.
	//copying ID's.
	char Squad_ID[MAX_ID_LENGTH];
	char APC_ID[MAX_ID_LENGTH];
	char Sol_ID[MAX_ID_LENGTH];
	strcpy(Squad_ID, Command_Arguments[2]);
	strcpy(APC_ID, Command_Arguments[3]);
	strcpy(Sol_ID, Command_Arguments[4]);

	//check if squad exists.
	PElem sq;
	sq = List_Get_Elem(objects_ID, (PKey)Squad_ID);
	if (sq == NULL) {
		printf("Error: No Such Squad\n");
		return FAILURE;
	}

	//check if APC exists.
	PElem APC;
	APC = List_Get_Elem(objects_ID, (PKey)APC_ID);
	if (APC == NULL) {
		printf("Error: No Such APC\n");
		return FAILURE;
	}

	//check if soldier exists.
	PElem soldier;
	soldier = List_Get_Elem(objects_ID, (PKey)APC_ID);
	if (soldier == NULL) {
		printf("Error: No Such Soldier\n");
		return FAILURE;
	}

	//adding the soldier to squad. no need to add to object list.
	Result added;
	added = WarZone_Add_Sol_To_APC_In_Squad(wz, Squad_ID, Sol_ID, APC_ID);
	if (added == FAILURE) return FAILURE;
	return SUCCESS;
}

/****************************************************************
function: WarZone_APC_Pop_Found_In_Squad_Func.
abstract: Pops the soldier from the top seat in an APC.
parameters: Command Arguments in string array, number of Args - int
			a pointer to the battlefield - BF.
returns: SUCCESS when Pops and FAILURE otherwise.
***************************************************************/
Result WarZone_APC_Pop_Found_In_Squad_Func(char* Command_Arguments[], int Args_Num, BF Battlefield,PList objects_ID) {

	//first check if the war zone exists.
	PWarZone wz;
	wz = Check_If_WarZone_Exists(Battlefield, Command_Arguments[1]);   //Command_Arguments[1] == WarZone ID.
	if (wz == NULL) {
		printf("Error: No Such War Zone\n");
		return FAILURE;
	}

	//warzone exists. 
	//copying ID's.
	char Squad_ID[MAX_ID_LENGTH];
	char APC_ID[MAX_ID_LENGTH];
	strcpy(Squad_ID, Command_Arguments[2]);
	strcpy(APC_ID, Command_Arguments[3]);


	return WarZone_APC_Pop_Found_In_Squad(wz, Squad_ID, APC_ID);
}

/****************************************************************
function: BF_Raise_WarZone_Func.
abstract: Raises a war zone Alert level.
parameters: Command Arguments in string array, number of Args - int
		a pointer to the battlefield - BF.
returns: SUCCESS when squad added and FAILURE otherwise.
***************************************************************/
Result BF_Raise_WarZone_Func(char* Command_Arguments[], int Args_Num, BF Battlefield) {

	//first check if the war zone exists.
	PWarZone wz;
	wz = Check_If_WarZone_Exists(Battlefield, Command_Arguments[1]);   //Command_Arguments[1] == WarZone ID.
	if (wz == NULL) {
		printf("Error: No Such War Zone\n");
		return FAILURE;
	}

	//warzone exists. Raise Alert Level.
	char WZ_ID[MAX_ID_LENGTH];
	strcpy(WZ_ID, Command_Arguments[1]);

	//raises alert level in the War Zone. if it's 3 moving all squads to the war Zone.
	if(BF_Raise_WarZone(Battlefield, WZ_ID) == 3)
	{
		BF_Move_All_Squads(Battlefield,WZ_ID);

		//return War Zone Alert Level to 0.
		BF_Initialize_War_Zone_Alert_Level(Battlefield, WZ_ID);
	}
	return SUCCESS;
}

/****************************************************************
function: BF_Move_Squad_From_War_Zone_Func.
abstract: moves a squadfrom a source to a destination War Zone.
parameters: Command Arguments in string array, number of Args - int
			a pointer to the battlefield - BF.
returns: SUCCESS when squad added and FAILURE otherwise.
***************************************************************/
Result BF_Move_Squad_From_War_Zone_Func(char* Command_Arguments[], int Args_Num, BF Battlefield, PList objects_ID) {

	//first check if the src war zone exists.
	PWarZone wz;
	wz = Check_If_WarZone_Exists(Battlefield, Command_Arguments[1]);   //Command_Arguments[1] == WarZone ID.
	if (wz == NULL) {
		printf("Error: No Such Origin War Zone\n");
		return FAILURE;
	}

	//now check if dst warzone exists.
	wz = Check_If_WarZone_Exists(Battlefield, Command_Arguments[2]);   //Command_Arguments[1] == WarZone ID.
	if (wz == NULL) {
		printf("Error: No Such Dest War Zone\n");
		return FAILURE;
	}

	//warzones exists. moving.

	//copying ID's.
	char Src_ID[MAX_ID_LENGTH];
	char Dst_ID[MAX_ID_LENGTH];
	char Squad_ID[MAX_ID_LENGTH];
	strcpy(Src_ID, Command_Arguments[1]);
	strcpy(Dst_ID, Command_Arguments[2]);
	strcpy(Squad_ID, Command_Arguments[3]);

	//check if squad exists.
	PElem sq;
	sq = List_Get_Elem(objects_ID, (PKey)Squad_ID);
	if (sq == NULL) {
		printf("Error: No Such Squad\n");
		return FAILURE;
	}

	return BF_Move_Squad_From_War_Zone(Battlefield, Src_ID, Dst_ID, Squad_ID);

}



Result	exe_Commands(char* Command_Arguments[],int Args_Num, BF Battlefield, PList objects_ID)
{
	//checking if command was executed.
	Result Executed;

	//command is Add Warzone.
	if (!strcmp("Add_W", Command_Arguments[0])) {
		Executed = Add_W(Command_Arguments, Args_Num, Battlefield);
		//BF_Print(Battlefield);
		return Executed;
	}

	//command is delete Warzone.
	if (!strcmp("Del_W", Command_Arguments[0])) {
		Executed = Del_W(Command_Arguments, Args_Num, Battlefield);
		//BF_Print(Battlefield);
		return Executed;
	}

	//command is Add Squad.
	if (!strcmp("Add_Sq", Command_Arguments[0])) {
		Executed = WarZone_Add_Squad_Func(Command_Arguments, Args_Num, Battlefield, objects_ID);
		//BF_Print(Battlefield);
		return Executed;
	}
	
	//command is delete Squad.
	if (!strcmp("Del_Sq", Command_Arguments[0])) {
		Executed = WarZone_Del_Squad_Func(Command_Arguments, Args_Num, Battlefield, objects_ID);
		//BF_Print(Battlefield);
		return Executed;
	}

	//command is add Soldier.
	if (!strcmp("Add_Sold", Command_Arguments[0])) {
		Executed = WarZone_Add_Sol_To_Squad_Func(Command_Arguments, Args_Num, Battlefield, objects_ID);
		//BF_Print(Battlefield);
		return Executed;
	}

	//command is Delete Soldier.
	if (!strcmp("Del_Sold", Command_Arguments[0])) {
		Executed = WarZone_Remove_Soldier_From_Squad_Func(Command_Arguments, Args_Num, Battlefield, objects_ID);
		//BF_Print(Battlefield);
		return Executed;
	}
	
	//command is Add APC.
	if (!strcmp("Add_APC", Command_Arguments[0])) {
		Executed = WarZone_Add_APC_To_Squad_Func(Command_Arguments, Args_Num, Battlefield, objects_ID);
		//BF_Print(Battlefield);
		return Executed;
	}
	
	//command is Delete APC.
	if (!strcmp("Del_APC", Command_Arguments[0])) {
		Executed = WarZone_Remove_APC_From_Squad_Func(Command_Arguments, Args_Num, Battlefield, objects_ID);
		//BF_Print(Battlefield);
		return Executed;
	}

	//command is Insert Soldier To APC.
	if (!strcmp("Sold_Insert", Command_Arguments[0])) {
		Executed = WarZone_Add_Sol_To_APC_In_Squad_Func(Command_Arguments, Args_Num, Battlefield, objects_ID);
		//BF_Print(Battlefield);
		return Executed;
	}
	
	//command is Pop Soldier From APC.
	if (!strcmp("APC_Pop", Command_Arguments[0])) {
		Executed = WarZone_APC_Pop_Found_In_Squad_Func(Command_Arguments, Args_Num, Battlefield, objects_ID);
		//BF_Print(Battlefield);
		return Executed;
	}
	
	//command is Print Battlefield.
	if (!strcmp("Print", Command_Arguments[0])) {
		BF_Print(Battlefield);
		return SUCCESS;
	}

	//command is Raise War Zone Alert.
	if (!strcmp("R_W", Command_Arguments[0])) {
		Executed = BF_Raise_WarZone_Func(Command_Arguments, Args_Num, Battlefield);
		//BF_Print(Battlefield);
		return Executed;
	}
	
	//command is Move Squad.
	if (!strcmp("M_Sq", Command_Arguments[0])) {
		Executed = BF_Move_Squad_From_War_Zone_Func(Command_Arguments, Args_Num, Battlefield, objects_ID);
		//BF_Print(Battlefield);
		return Executed;
	}
	
	
	//for debug purposes.
	return FAILURE;
}

PList objects_ID = NULL;


int main() {


	/**Main Initialize**/

	//1) Program Starts with Commands List
	PList Commands_List = List_Create(Get_Command_Num,
										Command_Duplicate_Func,
										command_Delete_Func,
										Comp_Command_Num,
										Command_Print_Func); 
	if (Commands_List == NULL) {
		printf("Program Init Error\n");
		return EXIT_FAILURE;
	}

	//2) Battlefield List
	objects_ID = List_Create(Get_warrior_ID,
	                            ID_Duplicate_Func,
	                            ID_Delete_Func,
	                            Comp_Obj_ID,
	                            ID_Print_Func);
    if (objects_ID == NULL) {
		printf("objects_ID  list failed\n");
		return EXIT_FAILURE;
	}

	//battlefield initialization.
	bool Battlefield_Created = false;
	bool ended = false;
	BF Battlefield = NULL;

	//3) /**STRTOK**
	/**Need two copies of program's input line: one for each strtok.(because strtok changes it's input string)**/
	char Input_Line[MAX_INPUT_LINE] = { 0 };				// stores program's input line by line
	char Input_Line_Copy[MAX_INPUT_LINE] = { 0 };
	char delimiters[] = " \t\n";
	int Args_Num;											// number of arguments in current command
	char* Curr_Command_Index;								//	will hold the current command index
	char* Command_Arguments[MAX_ARG];						//	all command's arguments after strtok completed.
	int counter = 0;				// counter to be used to hold the max command index. 

	//4) Main LOOP

	while (!ended) {												//program didnt end
		fgets(Input_Line, MAX_INPUT_LINE, stdin);					//scan next input line
		strcpy(Input_Line_Copy, Input_Line);			//making backup of input line (going to use strtok)
		Curr_Command_Index = strtok(Input_Line_Copy, delimiters);	//getting the index of current command - copied string Changed!

		//continue to next line if NULL;
		if (Curr_Command_Index == NULL) continue; //TODO: check if needed FIXME

		if (!strcmp(Curr_Command_Index, "Exit")){ //ending the program. deleting battlefield and lists. 
			ended = true; 
			List_Delete(Commands_List);
			List_Delete(objects_ID);
			BF_Delete(Battlefield);
			return 0;
		}

		/**Cases according to command's index**/

		//C.1) index is "Exe" - need to execute all commands by current order
		if (!strcmp(Curr_Command_Index, "Exe")) {
			
			
			//getting the first command.
			PElem * elem;
			int j = 1;
			if ((elem = List_Get_Elem(Commands_List,((PKey)(&j)))) == NULL) { //no commands to execute.
				printf("No Commands to Execute\n");
				printf("**********All Commands Executed**********\n\n");
				continue;
			}

			else         //execute commands. first parse the command.
			{
				for (int i = 1; i <= counter; ++i) {      //Execute all commands on the list.
			
					//getting the element by the serial number stored in each command struct.
					elem = List_Get_Elem(Commands_List, (PKey)(&i));
					Pcommand cur_command = (Pcommand)elem;
					
					//parse the command.
					Command_Arguments[0] = strtok(cur_command->command_Data, delimiters);  //takes the number index. will be overwritten in for loop.
					if(Command_Arguments[0] == NULL) continue;   
          
					Args_Num = 0;
					Command_Arguments[Args_Num] = strtok(NULL, delimiters); 
         			if(Command_Arguments[0] == NULL) continue;        
					while (Command_Arguments[Args_Num] != NULL) {
						Args_Num++;
                        Command_Arguments[Args_Num] = strtok(NULL, delimiters);    
						
					}
						
					Result valid;
					valid = check_If_Valid(Command_Arguments[0]);
					if (valid == FAILURE) {
						List_Remove_Elem(Commands_List, (PKey)(&i));
						continue;      //command is not valid.
					}

					//first check if battlefield was created. if not can't execute any other command.
					if (strcmp(Command_Arguments[0], "Create_B") && !Battlefield_Created) {
						printf("Error: No Battlefield\n");
                        List_Remove_Elem(Commands_List, (PKey)(&i));
						continue;
					}

					//command is create battlefield. Executing. the second condition is to check if Battlefield was already initialized.
					if (!strcmp(Command_Arguments[0], "Create_B") && !Battlefield_Created) {
						Battlefield = initiate_Battlefield_Func();
						Battlefield_Created = true;				//flag is true.
						List_Remove_Elem(Commands_List, (PKey)(&i));   //deleting the element.
						printf("Battlefield Created!\n");
						continue;
					}
					
					//can execute commands. check if current command is valid.
					
					//execute the specific command.
					Result Executed;
					Executed = exe_Commands(Command_Arguments, Args_Num, Battlefield,objects_ID);

					//deleting the Command element from the list.
					List_Remove_Elem(Commands_List, (PKey)(&i));
					        
				}

				//Finished Executing: printing the message.
				printf("**********All Commands Executed**********\n\n");

				//initializing counter for next Exe.
				counter = 0;

			}
		}

		//C.2) index is a number - add the command to the list of commands.
		else
		{
			//allocating new command memory.
			Pcommand new_command = (Pcommand)malloc(sizeof(*new_command));
			if (new_command == NULL) return -1;
			new_command->command_Num = atoi(Curr_Command_Index);     //storing the command idx.
			new_command->command_Data = (char*)malloc((sizeof(char))*(strlen(Input_Line)+1));		//+1 is for '\0'
			if (new_command->command_Data == NULL) {
				free(new_command);
				new_command = NULL;
				return -1;
			}
			strcpy(new_command->command_Data, Input_Line);			//copying the command to be used in exe.
			Result added = List_Add_Elem(Commands_List, (PElem)new_command);		//inserting the command to the command list.
			if (added == FAILURE){
				free(new_command->command_Data);
				new_command->command_Data = NULL;
				free(new_command);
				new_command = NULL;
				return -1;
			}
			free(new_command->command_Data);				 //after command is added to the list free allocated memory.
			new_command->command_Data = NULL;
			free(new_command);
			new_command = NULL;
			counter++;											//advancing the counter of commands.
		}
	}
}












