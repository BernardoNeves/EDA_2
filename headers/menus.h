#include "lists.h"
#include "files.h"


int getInt(int min, int max);

char selectFile();

void mainMenu();


void printProcessPlan(job *jobHead);
void printJobList(job *jobHead);
void printOperationList(operation *operationHead);
void printMachineList(machine *machineHead);

void printProcessPlanMinTime(job *jobHead);
void printJobMinTime(job *jobHead);
void printOperationMinTime(operation *operationHead);

void printJobMaxTime(job *jobHead);
void printOperationMaxTime(operation *operationHead);

void printJobAverageTime(job *jobHead);
void printOperationAverageTime(operation *operationHead);

void userCreateOperation(job *jobHead);
void userRemoveOperation(job *jobHead);
void userAlterOperation(job *jobHead);