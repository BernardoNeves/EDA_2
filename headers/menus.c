/**
 * @file menus.c
 * @author Bernardo Neves (a23494@alunos.ipca.pt)
 * @brief Main menu and submenus for the program
 * @date 2022-06-01
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "menus.h"
#include "calculations.h"

/**
 * @brief Main menu for the program
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
int getInt(int min, int max)
{
    for (int choiceInt = min - 1; choiceInt > max || choiceInt < min; scanf("%*c"))
        if (scanf(" %d", &choiceInt) == 1 && choiceInt <= max && choiceInt >= min)
            return choiceInt;
        else
            printf("\nInvalid input. Please try again.\n");
}

/**
 * @brief Main menu for the program
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void mainMenu()
{
    printf("Type the name of the file you want to open.\n");
    char fileName[50];
    scanf(" %s", &fileName);
    system("cls");
    job *jobHead = read(fileName);
    if (jobHead == NULL)
        printf("\n\tError: File could not be opened.\n\n");
    else
    {
        printf("\n\tFile opened successfully.\n\n");

        for (int choice; choice != 0;)
        {
            printf("\t--- MAIN MENU ---\n"
                   "\t Enter 1 - List ProcessPlan \n"
                   "\t Enter 2 - List Job \n"
                   "\t Enter 3 - Add Operation\n"
                   "\t Enter 4 - Remove Operation\n"
                   "\t Enter 5 - Add Job\n"
                   "\t Enter 6- Remove Job\n"
                   "\t Enter 7 - Minimum Time\n"
                   "\t Enter 8 - Maximum Time\n"
                   "\t Enter 9 - Average Time\n"
                   "\n\t Enter 0 - Quit\n\n\t> ");

            choice = getInt(0, 10);
            system("cls");
            printf("\n");
            switch (choice)
            {
            case 1: // List ProcessPlan
                printProcessPlan(jobHead);
                break;
            case 2: // List Job
                printf("Select a job to print: ");
                printJobList(findJob(jobHead, getInt(1, totalJobCount(jobHead))));
                break;
            case 3: // Add Operation
                userAddOperation(jobHead);
                break;
            case 4: // Remove Operation
                userRemoveOperation(jobHead);
                break;
            case 5: // Add Job
                userAddJob(jobHead);
                break;
            case 6: // Remove Job
                userRemoveJob(jobHead);
                break;
            case 7: // Minimum Time
                printf("Select a job to print minimum time: ");
                printJobMinTime(findJob(jobHead, getInt(1, totalJobCount(jobHead))));
                break;
            case 8: // Maximum Time
                printf("Select a job to print maximum time: ");
                printJobMaxTime(findJob(jobHead, getInt(1, totalJobCount(jobHead))));
                break;
            case 9: // Average Time
                printf("Select a job to print average time: ");
                printJobAverageTime(findJob(jobHead, getInt(1, totalJobCount(jobHead))));
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

/**
 * @brief Prints the process plan
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void printProcessPlan(job *jobHead)
{
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        printJobList(jobTmp);
}

/**
 * @brief Prints the job list
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void printJobList(job *jobHead)
{
    printf("\n\nJob: %d\n", jobHead->jobNumber);
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        printOperationList(operationTmp);
}

/**
 * @brief Prints the operation list
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void printOperationList(operation *operationHead)
{
    printf("\nOperation: %d\n\n", operationHead->operationNumber);
    for (machine *machineTmp = operationHead->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
        printMachineList(machineTmp);
}

/**
 * @brief Prints the machine list
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void printMachineList(machine *machineHead)
{
    printf("Machine: %d Time: %.2f\n", machineHead->machineNumber, (float)machineHead->machineTime);
}

/**
 * @brief Adds an operation to a job
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void printProcessPlanMinTime(job *jobHead)
{
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        printJobMinTime(jobTmp);
    printf("\n\nMinimum Time for Process Plan: %.2f\n\n", timeMinProcessPlan(jobHead));
}

/**
 * @brief Adds an operation to a job
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void printJobMinTime(job *jobHead)
{
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        printOperationMinTime(operationTmp);
    printf("\n\nMinimum Time for Job %d: %.2f\n\n", jobHead->jobNumber, timeMinJob(jobHead));
}

/**
 * @brief Adds an operation to a job
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void printOperationMinTime(operation *operationHead)
{
    printf("Minimum Time for Operation %d: %.2f\n", operationHead->operationNumber, timeMinOperation(operationHead));
}

/**
 * @brief Adds an operation to a job
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void printJobMaxTime(job *jobHead)
{
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        printOperationMaxTime(operationTmp);
    printf("\n\nMaximum Time for Job %d: %.2f\n\n", jobHead->jobNumber, timeMaxJob(jobHead));
}

/**
 * @brief Adds an operation to a job
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void printOperationMaxTime(operation *operationHead)
{
    printf("Maximum Time for Operation %d: %.2f\n", operationHead->operationNumber, timeMaxOperation(operationHead));
}

/**
 * @brief Adds an operation to a job
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void printJobAverageTime(job *jobHead)
{
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        printOperationAverageTime(operationTmp);
    printf("\n\nAverage Time for Job %d: %.2f\n\n", jobHead->jobNumber, timeAverageJob(jobHead));
}

/**
 * @brief Adds an operation to a job
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void printOperationAverageTime(operation *operationHead)
{
    printf("Average Time for Operation %d: %.2f\n", operationHead->operationNumber, timeAverageOperation(operationHead));
}

/**
 * @brief Adds an operation to a job
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void userAddOperation(job *jobHead)
{
    printProcessPlan(jobHead);
    printf("\nSelect a job: ");
    job *jobTmp = findJob(jobHead, getInt(1, totalJobCount(jobHead)));
    machine *machineTmp, *machineHead = NULL;
    operation *operationTmp;
    if (jobTmp == NULL)
    {
        printf("\n\tJob not found\n\n");
        return;
    }
    printf("\nSelect Operation order: ");
    for (int machineNumber; machineNumber != 0;)
    {
        printf("\nSelect a machine number: ");
        machineNumber = getInt(0, 100);
        if (machineNumber == 0)
            break;
        machineTmp = createNewMachine(machineNumber);
        machineHead = insertAtMachineEnd(&machineHead, machineTmp);
        printf("\nSelect a time: ");
        machineTmp->machineTime = getInt(0, 100);
    }
    printf("\n\tOperation added successfully\n\n");
    operationTmp = createNewOperation(0, jobTmp->jobNumber, &machineHead);
    jobTmp->operationHeadPointer = insertAtOperationEnd(&(jobTmp->operationHeadPointer), operationTmp);
    orderOperation(jobTmp->operationHeadPointer);
}

/**
 * @brief Adds an operation to a job
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void userAddJob(job *jobHead)
{
    operation *operationTmp = NULL;
    insertAtJobEnd(&jobHead, createNewJob(totalJobCount(jobHead) + 1, &operationTmp));
}

/**
 * @brief Adds an operation to a job
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void userRemoveJob(job *jobHead)
{
    printf("\nSelect job to remove: ");
    job *jobTmp = findJob(jobHead, getInt(1, totalJobCount(jobHead)));
    removeJob(&jobHead, &jobTmp);
}

/**
 * @brief Adds an operation to a job
 * @param ProcessPlan Pointer to the file with the process plan
 * @return void
 */
void userRemoveOperation(job *jobHead)
{
    printProcessPlan(jobHead);
    printf("\nSelect a job: ");
    job *jobTmp = findJob(jobHead, getInt(1, totalJobCount(jobHead)));
    printf("\nSelect Operation to remove: ");
    operation *operationTmp = findOperation(jobTmp->operationHeadPointer, getInt(1, totalOperationCountJob(jobTmp)));
    removeOperation(&(jobTmp)->operationHeadPointer, &(operationTmp));
}
