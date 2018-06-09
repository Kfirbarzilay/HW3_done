#include "Soldier.h"

//A struct that holds the two charachteristics of a soldier
struct Soldier_{
	char Pos[MAX_ID_LENGTH];
	char ID[MAX_ID_LENGTH];
	//PSoldier nextSol;//points to the next soldier on the list
};


/****************************************************************
function: Soldier_Create.
abstract: creating a new soldier with his\her ID and position.
parameters: char *ID and char *position
Returns: a pointer to the created soldier or NULL if
		a soldier with the same name already exists.
***************************************************************/
PSoldier Soldier_Create(char *ID, char *POS) {
	if (ID == NULL || POS == NULL) return NULL; //can't hold empty fields
	if (strlen(ID) > MAX_ID_LENGTH || strlen(POS) > MAX_ID_LENGTH)return NULL; //can't add a soldier with ID or POS longer than 8 chars.
	PSoldier NewSoldier = (PSoldier)malloc(sizeof(Soldier));
	if (NewSoldier == NULL) return NULL;
	strcpy(NewSoldier->ID, ID);
	strcpy(NewSoldier->Pos, POS);
	return NewSoldier;
}

/*********************************************************************************
function: Soldier_Duplicate.
abstract: creating a copy of a soldier with his\her ID and position.
parameters: A Soldier pointer.
returns NULL if the pointer is NULL or if couldn't perform malloc.
prints ARG_ERR_MSG if pointer is NULL  or MALLOC_ERR_MSG if can't allocate memory
**********************************************************************************/
PSoldier Soldier_Duplicate(PSoldier Soldier) {
	if (Soldier == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}

	PSoldier newSoldier = Soldier_Create(Soldier->ID, Soldier->Pos);
	if (newSoldier == NULL) {
		printf(MALLOC_ERR_MSG);
		return NULL;
	}

	return newSoldier;
}

/****************************************************************
function: Soldier_Print.
abstract: prints a soldier ID and position.
parameters: A Soldier pointer.
Errors: prints ARG_ERR_MSG if thw soldier is NULL.
***************************************************************/
void Soldier_Print(PSoldier Soldier) {
	if (Soldier == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	printf("%s , %s\n", Soldier->ID, Soldier->Pos);
}
/****************************************************************
function: Soldier_Delete.
abstract: deletes a soldier.
parameters: A Soldier pointer.
***************************************************************/
void Soldier_Delete(PSoldier soldier) {
	if (soldier != NULL) {
		free(soldier);
		soldier = NULL;
	}
	else
		printf(ARG_ERR_MSG);
}

char * Soldier_Get_ID(PSoldier sol)
{
	if (sol != NULL) {
		return sol->ID;
	}
	return NULL;
}

char* Soldier_Get_Pos(PSoldier sol) {
	if (sol != NULL) {
		return sol->Pos;
	}
	return NULL;
}

