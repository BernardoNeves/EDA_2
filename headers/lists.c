/**
 * @file lists.c
 * @author Bernardo Neves (a23494@alunos.ipca.pt)
 * @brief  Create and manipulate lists
 * @date 2022-06-01
 */
#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * @brief  Create a new job
 * @param  jobName: name of the job
 * @param  jobTime: time of the job
 * @return job: pointer to the new job
 */
job *createNewJob(int jobNumber, operation **operationHead)
{
    job *result = malloc(sizeof(job));
    result->jobNumber = jobNumber;
    result->operationHeadPointer = *operationHead;
    result->next = NULL;
    result->prev = NULL;
    return result;
}

/**
 * @brief  Create a new operation
 * @param  operationName: name of the operation
 * @param  operationTime: time of the operation
 * @return operation: pointer to the new operation
 */
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

/**
 * @brief  Create a new machine
 * @param  machineName: name of the machine
 * @param  machineTime: time of the machine
 * @return machine: pointer to the new machine
 */
machine *createNewMachine(int machineNumber)
{
    machine *result = malloc(sizeof(machine));
    result->machineNumber = machineNumber;
    result->next = NULL;
    result->prev = NULL;
    return result;
}

/**
 * @brief  Insert a new job at the end of the job list
 * @param  jobHead: head of the job list
 * @param  newJob: pointer to the new job
 * @return jobHead: head of the job list
 */
job *insertAfterJob(job *jobToInsertAfter, job *jobToInsert)
{
    *jobToInsert->next = *jobToInsertAfter->next;
    *jobToInsert->next->prev = *jobToInsert;
    *jobToInsertAfter->next = *jobToInsert;
    *jobToInsert->prev = *jobToInsertAfter;
    return jobToInsert;
}

/**
 * @brief  Insert a new operation at the end of the operation list
 * @param  operationHead: head of the operation list
 * @param  newOperation: pointer to the new operation
 * @return operationHead: head of the operation list
 */
operation *insertAfterOperation(operation *operationToInsertAfter, operation *operationToInsert)
{
    *operationToInsert->next = *operationToInsertAfter->next;
    *operationToInsert->next->prev = *operationToInsert;
    *operationToInsertAfter->next = *operationToInsert;
    *operationToInsert->prev = *operationToInsertAfter;
    return operationToInsert;
}

/**
 * @brief  Insert a new machine at the end of the machine list
 * @param  machineHead: head of the machine list
 * @param  newMachine: pointer to the new machine
 * @return machineHead: head of the machine list
 */
machine *insertAfterMachine(machine *machineToInsertAfter, machine *machineToInsert)
{
    *machineToInsert->next = *machineToInsertAfter->next;
    *machineToInsert->next->prev = *machineToInsert;
    *machineToInsertAfter->next = *machineToInsert;
    *machineToInsert->prev = *machineToInsertAfter;
    return machineToInsert;
}

/**
 * @brief  Insert a new job at the head of the job list
 * @param  jobHead: head of the job list
 * @param  newJob: pointer to the new job
 * @return jobHead: head of the job list
 */
job *insertAtJobHead(job **jobHead, job *jobToInsert)
{
    jobToInsert->next = *jobHead;
    *jobHead = jobToInsert;
    return jobToInsert;
}

/**
 * @brief  Insert a new operation at the head of the operation list
 * @param  operationHead: head of the operation list
 * @param  newOperation: pointer to the new operation
 * @return operationHead: head of the operation list
 */
operation *insertAtOperationHead(operation **operationHead, operation *operationToInsert)
{

    operationToInsert->next = *operationHead;
    *operationHead = operationToInsert;
    return operationToInsert;
}

/**
 * @brief  Insert a new machine at the head of the machine list
 * @param  machineHead: head of the machine list
 * @param  newMachine: pointer to the new machine
 * @return machineHead: head of the machine list
 */
machine *insertAtMachineHead(machine **machineHead, machine *machineToInsert)
{
    machineToInsert->next = *machineHead;
    *machineHead = machineToInsert;
    return machineToInsert;
}

/**
 * @brief  Delete a job from the job list
 * @param  jobHead: head of the job list
 * @param  jobToDelete: pointer to the job to delete
 * @return jobHead: head of the job list
 */
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

/**
 * @brief  Delete a operation from the operation list
 * @param  operationHead: head of the operation list
 * @param  operationToDelete: pointer to the operation to delete
 * @return operationHead: head of the operation list
 */
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

/**
 * @brief  Delete a machine from the machine list
 * @param  machineHead: head of the machine list
 * @param  machineToDelete: pointer to the machine to delete
 * @return machineHead: head of the machine list
 */
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

/**
 * @brief  Delete a job from the job list
 * @param  jobHead: head of the job list
 * @param  jobToDelete: pointer to the job to delete
 * @return jobHead: head of the job list
 */
void orderJob(job *jobHead)
{
    int jobNumber = 1;
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
    {
        orderOperation(jobTmp->operationHeadPointer);
        jobTmp->jobNumber = jobNumber++;
    }
}

/**
 * @brief  Delete a operation from the operation list
 * @param  operationHead: head of the operation list
 * @param  operationToDelete: pointer to the operation to delete
 * @return operationHead: head of the operation list
 */
void orderOperation(operation *operationHead)
{
    int operationNumber = 1;
    for (operation *operationTmp = operationHead; operationTmp != NULL; operationTmp = operationTmp->next)
        operationTmp->operationNumber = operationNumber++;
}

/**
 * @brief  Delete a machine from the machine list
 * @param  machineHead: head of the machine list
 * @param  machineToDelete: pointer to the machine to delete
 * @return machineHead: head of the machine list
 */
job *findJob(job *jobHead, int jobNumber)
{
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        if (jobTmp->jobNumber == jobNumber)
            return jobTmp;
    return NULL;
}

/**
 * @brief  Delete a operation from the operation list
 * @param  operationHead: head of the operation list
 * @param  operationToDelete: pointer to the operation to delete
 * @return operationHead: head of the operation list
 */
operation *findOperation(operation *operationHead, int operationNumber)
{
    if (operationHead == NULL)
        return NULL;
    for (operation *operationTmp = operationHead; operationTmp != NULL; operationTmp = operationTmp->next)
        if (operationTmp->operationNumber == operationNumber)
            return operationTmp;
    return NULL;
}

/**
 * @brief  Delete a machine from the machine list
 * @param  machineHead: head of the machine list
 * @param  machineToDelete: pointer to the machine to delete
 * @return machineHead: head of the machine list
 */
machine *findMachine(machine *machineHead, int machineNumber)
{
    for (machine *machineTmp = machineHead; machineTmp != NULL; machineTmp = machineTmp->next)
        if (machineTmp->machineNumber == machineNumber)
            return machineTmp;
    return NULL;
}

/**
 * @brief  Delete a job from the job list
 * @param  jobHead: head of the job list
 * @param  jobToDelete: pointer to the job to delete
 * @return jobHead: head of the job list
 */
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

/**
 * @brief  Delete a operation from the operation list
 * @param  operationHead: head of the operation list
 * @param  operationToDelete: pointer to the operation to delete
 * @return operationHead: head of the operation list
 */
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

/**
 * @brief  Delete a machine from the machine list
 * @param  machineHead: head of the machine list
 * @param  machineToDelete: pointer to the machine to delete
 * @return machineHead: head of the machine list
 */
void *removeMachine(machine **machineHead, machine **machineTmp)
{
    if ((*machineTmp) == *machineHead)
        *machineHead = (*machineHead)->next;
    else
        (*machineTmp)->prev->next = (*machineTmp)->next;
    free(machineTmp);
}
