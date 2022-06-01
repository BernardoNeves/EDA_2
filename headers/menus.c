#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "menus.h"
#include "calculations.h"

int getInt(int min, int max)
{
    for (int choiceInt = min - 1; choiceInt > max || choiceInt < min; scanf("%*c"))
        if (scanf(" %d", &choiceInt) == 1 && choiceInt <= max && choiceInt >= min)
            return choiceInt;
        else
            printf("\nInvalid input. Please try again.\n");
}

void mainMenu()
{
    printf("Type the name of the file you want to open.\n");
    char fileName[50];
    scanf(" %s", &fileName);
    job *jobHead = read(fileName);
    if (jobHead == NULL)
        printf("\n\tError: File could not be opened.\n\n");
    else
    {
        printf("\n\tFile opened successfully.\n\n");

        for (int choice; choice != 0;)
        {
            printf("\t--- MAIN MENU ---\n"
                   "\t Enter 1 - List \n"
                   "\t Enter 2 - Add Operation\n"
                   "\t Enter 3 - Remove Operation\n"
                   "\t Enter 4 - Alter Operation\n"
                   "\t Enter 5 - Minimum Time\n"
                   "\t Enter 6 - Maximum Time\n"
                   "\t Enter 7 - Average Time\n"
                   "\n\t Enter 0 - Quit\n\n\t> ");

            choice = getInt(0, 7);
            system("cls");
            printf("\n");
            switch (choice)
            {
            case 1:
                printf("Select a job to print: ");
                printJobList(findJob(jobHead, getInt(1, totalJobCount(jobHead))));
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                printProcessPlanMinTime(jobHead);
                // printf("Select a job to print minimum time: ");
                // printJobMinTime(findJob(jobHead, getInt(1, totalJobCount(jobHead))));
                break;
            case 6:
                printf("Select a job to print maximum time: ");
                printJobMaxTime(findJob(jobHead, getInt(1, totalJobCount(jobHead))));
                break;
            case 7:
                printf("Select a job to print average time: ");
                printJobAverageTime(findJob(jobHead, getInt(1, totalJobCount(jobHead))));
                break;
            case 0:
                break;
            default:
                printf("\n\t//Invalid Option//\n\n");
                mainMenu();
                break;
            }
            if (choice != 0 && choice != 4)
            {
                printf("\n\tPress any key to go back");
                getch();
                system("cls");
            }
        }
        write(fileName, jobHead);
        (jobHead == NULL) ? printf("\n\tError: File could not be written.\n\n") : printf("\n\tFile written successfully.\n\n");
    }
    _Exit(0);
}

void printProcessPlan(job *jobHead)
{
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        printJobList(jobTmp);
}
void printJobList(job *jobHead)
{
    printf("\n\nJob: %d\n", jobHead->jobNumber);
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        printOperationList(operationTmp);
}

void printOperationList(operation *operationHead)
{
    printf("\nOperation: %d\n\n", operationHead->operationNumber);
    for (machine *machineTmp = operationHead->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
        printMachineList(machineTmp);
}

void printMachineList(machine *machineHead)
{
    printf("Machine: %d Time: %.2f\n", machineHead->machineNumber, (float)machineHead->machineTime);
}

void printProcessPlanMinTime(job *jobHead)
{
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        printJobMinTime(jobTmp);
    printf("\n\nMinimum Time for Process Plan: %.2f\n\n", timeMinProcessPlan(jobHead));
}
void printJobMinTime(job *jobHead)
{
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        printOperationMinTime(operationTmp);
    printf("\n\nMinimum Time for Job %d: %.2f\n\n", jobHead->jobNumber, timeMinJob(jobHead));
}

void printOperationMinTime(operation *operationHead)
{
    printf("Minimum Time for Operation %d: %.2f\n", operationHead->operationNumber, timeMinOperation(operationHead));
}

void printJobMaxTime(job *jobHead)
{
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        printOperationMaxTime(operationTmp);
    printf("\n\nMaximum Time for Job %d: %.2f\n\n", jobHead->jobNumber, timeMaxJob(jobHead));
}

void printOperationMaxTime(operation *operationHead)
{
    printf("Maximum Time for Operation %d: %.2f\n", operationHead->operationNumber, timeMaxOperation(operationHead));
}

void printJobAverageTime(job *jobHead)
{
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        printOperationAverageTime(operationTmp);
    printf("\n\nAverage Time for Job %d: %.2f\n\n", jobHead->jobNumber, timeAverageJob(jobHead));
}

void printOperationAverageTime(operation *operationHead)
{
    printf("Average Time for Operation %d: %.2f\n", operationHead->operationNumber, timeAverageOperation(operationHead));
}

//TODO MOVE THIS TO A NEW FILE AND SEPARATE PRINTS FROM CALCULATIONS AND FUNCTIONS
void userCreateOperation(job *jobHead) // TODO Optimize
{
    job *jobTmp = jobHead;
    operation *operationTmp;
    operation *operationHead;
    machine *machineTmp;
    machine *machineHeadTmp;
    machine *machineHead = NULL;
    int machineNumber = 1;
    int operationNumber;
    int jobNumber;

    // select job and operation order
    printf("Jobs:\n");
    while (jobTmp->next != NULL)
    {
        printf("%d; ", jobTmp->jobNumber);
        jobNumber = jobTmp->jobNumber;
        jobTmp = jobTmp->next;
    }
    printf("\nSelect Job: ");
    jobTmp = findJob(jobHead, getInt(1, jobNumber));

    printf("\nOperation Order Number: ");
    scanf(" %d", &operationNumber);

    //  create machines
    while (machineNumber != 0)
    {
        printf("\nMachine Number: ");
        scanf(" %d", &machineNumber);
        machineTmp = createNewMachine(machineNumber);
        machineHead = insertAtMachineEnd(&machineHead, machineTmp);

        printf("\nMachine %d Time: ", machineTmp->machineNumber);
        scanf(" %d", &machineNumber);
        machineTmp->machineTime = machineNumber;
        machineTmp = machineHead;

        printf("Enter 0 to stop adding machines: ");
        scanf(" %d", &machineNumber);
    }

    // Create Operation
    operationTmp = createNewOperation(operationNumber, jobTmp->jobNumber, &machineHead);
    while (jobTmp->operationHeadPointer->prev != NULL)
    {
        jobTmp->operationHeadPointer = jobTmp->operationHeadPointer->prev;
    }
    insertAfterOperation(findOperation(jobTmp->operationHeadPointer, operationNumber - 1), operationTmp);
    orderJob(jobHead);
}

void userRemoveOperation(job *jobHead) // TODO Optimize
{
    job *jobTmp = jobHead;
    operation *operationTmp;
    machine *machineTmp;
    machine *machineHeadTmp;
    machine *machineHead = NULL;
    int machineNumber = 1;
    int operationNumber;
    int jobNumber;

    printf("Jobs:\n");
    while (jobTmp->next != NULL)
    {
        printf("%d; ", jobTmp->jobNumber);
        jobNumber = jobTmp->jobNumber;
        jobTmp = jobTmp->next;
    }
    printf("\nSelect Job: ");
    jobTmp = findJob(jobHead, getInt(1, jobNumber));
    operationTmp = jobTmp->operationHeadPointer;

    printf("\nOperation Number: ");
    scanf(" %d", &operationNumber);

    while (operationTmp->next != NULL)
    {
        operationTmp = operationTmp->next;
    }
    while (operationTmp->prev != NULL)
    {
        machineHeadTmp = operationTmp->machineHeadPointer;
        operationTmp->machineHeadPointer = machineTmp;
        machineTmp = machineHeadTmp;
        operationTmp = operationTmp->prev;
        if (operationTmp->next->operationNumber == operationNumber)
            break;
    }

    while (operationTmp->next != NULL)
    {
        operationTmp = operationTmp->next;
    }
    operationTmp->prev->next = NULL;
    free(operationTmp);
}

void userAlterOperation(job *jobHead) // TODO Optimize
{
    job *jobTmp = jobHead;
    operation *operationTmp, *operationTmp2;
    machine *machineTmp, *machineHeadTmp, *machineHead = NULL;
    int machineNumber = 1, operationNumber, jobNumber, choice;

    printf("Jobs:\n");
    while (jobTmp->next != NULL)
    {
        printf("%d; ", jobTmp->jobNumber);
        jobNumber = jobTmp->jobNumber;
        jobTmp = jobTmp->next;
    }
    printf("\nSelect Job: ");
    jobTmp = findJob(jobHead, getInt(1, jobNumber));

    printf("\nOperation Number: ");
    scanf(" %d", &operationNumber);

    operationTmp = findOperation(jobTmp->operationHeadPointer, operationNumber);

    printf("\t--- Alter Operation ---\n"
           "\t Enter 1 - Add Machine \n"
           "\t Enter 2 - Remove Machine \n"
           "\t Enter 3 - Swap Operation Order \n"
           "\n\t Enter 0 - back\n");

    choice = getInt(0, 5);
    switch (choice)
    {
    case 1:
        while (machineNumber != 0)
        {
            machineHead = operationTmp->machineHeadPointer;
            printf("\nMachine Number: ");
            scanf(" %d", &machineNumber);
            machineTmp = createNewMachine(machineNumber);
            machineHead = insertAtMachineEnd(&machineHead, machineTmp);

            printf("\nMachine %d Time: ", machineTmp->machineNumber);
            scanf(" %d", &machineNumber);
            machineTmp->machineTime = machineNumber;
            machineTmp = machineHead;

            printf("Enter 0 to stop adding machines: ");
            scanf(" %d", &machineNumber);
        }
        break;
    case 2:
        printf("\nMachine Number: ");
        scanf(" %d", &machineNumber);
        machineTmp = findMachine(jobTmp->operationHeadPointer->machineHeadPointer, machineNumber);
        removeMachine(&operationTmp->machineHeadPointer, machineTmp->machineNumber);
        break;
    case 3:
        printf("\n Swap operation %d with: ", operationTmp->operationNumber);
        scanf("%d", &operationNumber);
        operationTmp2 = findOperation(jobTmp->operationHeadPointer, operationNumber);
        machineTmp = operationTmp->machineHeadPointer;
        operationTmp->machineHeadPointer = operationTmp2->machineHeadPointer;
        operationTmp2->machineHeadPointer = machineTmp;
        break;
    case 0:
        break;
    default:
        printf("\n\t//Invalid Option//\n\n");
        break;
    }
}