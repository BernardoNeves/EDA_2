#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

job *createNewJob(int jobNumber, operation **operationHead)
{
    job *result = malloc(sizeof(job));
    result->jobNumber = jobNumber;
    result->operationHeadPointer = *operationHead;
    result->next = NULL;
    result->prev = NULL;
    return result;
}

operation *createNewOperation(int operationNumber, int jobNumber, machine **machineHead)
{
    operation *result = malloc(sizeof(operation));
    result->operationNumber = operationNumber;
    result->jobNumber = jobNumber;
    result->machineHeadPointer = *machineHead;
    result->next = NULL;
    result->prev = NULL;
    return result;
}

machine *createNewMachine(int machineNumber)
{
    machine *result = malloc(sizeof(machine));
    result->machineNumber = machineNumber;
    result->next = NULL;
    result->prev = NULL;
    return result;
}

job *insertAfterJob(job *jobToInsertAfter, job *jobToInsert)
{
    *jobToInsert->next = *jobToInsertAfter->next;
    *jobToInsert->next->prev = *jobToInsert;
    *jobToInsertAfter->next = *jobToInsert;
    *jobToInsert->prev = *jobToInsertAfter;
    return jobToInsert;
}

operation *insertAfterOperation(operation *operationToInsertAfter, operation *operationToInsert)
{
    *operationToInsert->next = *operationToInsertAfter->next;
    *operationToInsert->next->prev = *operationToInsert;
    *operationToInsertAfter->next = *operationToInsert;
    *operationToInsert->prev = *operationToInsertAfter;
    return operationToInsert;
}

machine *insertAfterMachine(machine *machineToInsertAfter, machine *machineToInsert)
{
    *machineToInsert->next = *machineToInsertAfter->next;
    *machineToInsert->next->prev = *machineToInsert;
    *machineToInsertAfter->next = *machineToInsert;
    *machineToInsert->prev = *machineToInsertAfter;
    return machineToInsert;
}

job *insertAtJobHead(job **jobHead, job *jobToInsert)
{
    jobToInsert->next = *jobHead;
    *jobHead = jobToInsert;
    return jobToInsert;
}

operation *insertAtOperationHead(operation **operationHead, operation *operationToInsert)
{

    operationToInsert->next = *operationHead;
    *operationHead = operationToInsert;
    return operationToInsert;
}

machine *insertAtMachineHead(machine **machineHead, machine *machineToInsert)
{
    machineToInsert->next = *machineHead;
    *machineHead = machineToInsert;
    return machineToInsert;
}

job *insertAtJobEnd(job **jobHead, job *jobToInsert) //? CAN I OPTIMIZE THIS
{
    jobToInsert->next = NULL;

    if (*jobHead == NULL)
        *jobHead = jobToInsert;
    else
    {
        job *last = *jobHead;
        while (last->next != NULL)
            last = last->next;
        last->next = jobToInsert;
        jobToInsert->prev = last;
    }
    return *jobHead;
}

operation *insertAtOperationEnd(operation **operationHead, operation *operationToInsert) //? CAN I OPTIMIZE THIS
{
    operationToInsert->next = NULL;

    if (*operationHead == NULL)
        *operationHead = operationToInsert;
    else
    {
        operation *last = *operationHead;
        while (last->next != NULL)
            last = last->next;
        last->next = operationToInsert;
        operationToInsert->prev = last;
    }
    return *operationHead;
}

machine *insertAtMachineEnd(machine **machineHead, machine *machineToInsert) //? CAN I OPTIMIZE THIS
{
    machineToInsert->next = NULL;

    if (*machineHead == NULL)
        *machineHead = machineToInsert;
    else
    {
        machine *last = *machineHead;
        while (last->next != NULL)
            last = last->next;
        last->next = machineToInsert;
        machineToInsert->prev = last;
    }
    return *machineHead;
}

void orderJob(job *jobHead)
{
    int jobNumber = 1;
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
    {
        orderOperation(jobTmp->operationHeadPointer);
        jobTmp->jobNumber = jobNumber++;
    }
}

void orderOperation(operation *operationHead)
{
    int operationNumber = 1;
    for (operation *operationTmp = operationHead; operationTmp != NULL; operationTmp = operationTmp->next)
        operationTmp->operationNumber = operationNumber++;
}

job *findJob(job *jobHead, int jobNumber)
{
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        if (jobTmp->jobNumber == jobNumber)
            return jobTmp;
    return NULL;
}

operation *findOperation(operation *operationHead, int operationNumber)
{
    if (operationHead == NULL)
        return NULL;
    for (operation *operationTmp = operationHead; operationTmp != NULL; operationTmp = operationTmp->next)
        if (operationTmp->operationNumber == operationNumber)
            return operationTmp;
    return NULL;
}

machine *findMachine(machine *machineHead, int machineNumber)
{
    for (machine *machineTmp = machineHead; machineTmp != NULL; machineTmp = machineTmp->next)
        if (machineTmp->machineNumber == machineNumber)
            return machineTmp;
    return NULL;
}

void *removeJob(job **jobHead, job **jobTmp)
{
    while ((*jobTmp)->operationHeadPointer != NULL)
        removeOperation(&((*jobTmp)->operationHeadPointer), &((*jobTmp)->operationHeadPointer));
    if ((*jobTmp) == *jobHead)
        *jobHead = (*jobHead)->next;
    else
        (*jobTmp)->prev->next = (*jobTmp)->next;
    free(jobTmp);
    orderJob(*jobHead);
}

void *removeOperation(operation **operationHead, operation **operationTmp)
{
    while ((*operationTmp)->machineHeadPointer != NULL)
        removeMachine(&((*operationTmp)->machineHeadPointer), &((*operationTmp)->machineHeadPointer));
    if ((*operationTmp) == *operationHead)
        *operationHead = (*operationHead)->next;
    else
        (*operationTmp)->prev->next = (*operationTmp)->next;
    free(operationTmp);
    orderOperation(*operationHead);
}

void *removeMachine(machine **machineHead, machine **machineTmp)
{
    if ((*machineTmp) == *machineHead)
        *machineHead = (*machineHead)->next;
    else
        (*machineTmp)->prev->next = (*machineTmp)->next;
    free(machineTmp);
}
