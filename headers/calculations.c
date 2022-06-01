/**
 * @file calculations.c
 * @author Bernardo Neves (a23494@alunos.ipca.pt)
 * @brief   Calculates the time
 * @date 2022-06-01
 */
#include <stdio.h>
#include <stdlib.h>
#include "lists.h"
#include "calculations.h"

/**
 * @brief   Calculates the minimum time of a job
 * @param   jobHead: head of the job list
 * @return  void
 */
float timeMinProcessPlan(job *jobHead)
{
    float totalTime = 0;
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        totalTime += timeMinJob(jobTmp);
    return totalTime;
}

/**
 * @brief   Calculates the minimum time of a job
 * @param   jobHead: head of the job list
 * @return  void
 */
float timeMinJob(job *jobHead)
{
    float totalTime = 0;
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        totalTime += timeMinOperation(operationTmp);
    return totalTime;
}

/**
 * @brief   Calculates the minimum time of an operation
 * @param   operationTmp: head of the operation list
 * @return  void
 */
float timeMinOperation(operation *operationHead)
{
    machine *minTimeMachine = operationHead->machineHeadPointer;
    for (machine *machineTmp = operationHead->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
        if (minTimeMachine->machineTime > machineTmp->machineTime)
            minTimeMachine = machineTmp;
    return (float)minTimeMachine->machineTime;
}

/**
 * @brief   Calculates the maximum time of a job
 * @param   jobHead: head of the job list
 * @return  void
 */
float timeMaxJob(job *jobHead)
{
    float totalTime = 0;
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        totalTime += timeMaxOperation(operationTmp);
    return totalTime;
}

/**
 * @brief   Calculates the maximum time of an operation
 * @param   operationTmp: head of the operation list
 * @return  void
 */
float timeMaxOperation(operation *operationHead)
{
    machine *maxTimeMachine = operationHead->machineHeadPointer;
    for (machine *machineTmp = operationHead->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
        if (maxTimeMachine->machineTime < machineTmp->machineTime)
            maxTimeMachine = machineTmp;
    return (float)maxTimeMachine->machineTime;
}

/**
 * @brief   Calculates the total time of a job
 * @param   jobHead: head of the job list
 * @return  void
 */
float timeAverageOperation(operation *operationHead)
{
    return totalMachineTimeOperation(operationHead) / totalMachineCountOperation(operationHead);
}

/**
 * @brief   Calculates the total time of a job
 * @param   jobHead: head of the job list
 * @return  void
 */
float timeAverageJob(job *jobHead)
{
    float totalTime = 0;
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        totalTime += timeAverageOperation(operationTmp);
    return totalTime;
}

/**
 * @brief   Calculates the total time of a job
 * @param   jobHead: head of the job list
 * @return  void
 */
float totalMachineTimeOperation(operation *operationHead)
{
    float totalTime = 0;
    for (machine *machineTmp = operationHead->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
        totalTime += machineTmp->machineTime;
    return totalTime;
}

/**
 * @brief   Calculates the total time of a job
 * @param   jobHead: head of the job list
 * @return  void
 */
float totalJobCount(job *jobHead)
{
    float jobCount = 0;
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        jobCount++;
    return jobCount;
}

/**
 * @brief   Calculates the total time of a job
 * @param   jobHead: head of the job list
 * @return  void
 */
float totalOperationCountJob(job *jobHead)
{
    float operationCount = 0;
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        operationCount++;
    return operationCount;
}

/**
 * @brief   Calculates the total time of a job
 * @param   jobHead: head of the job list
 * @return  void
 */
float totalMachineCountProcessPlan(job *jobHead)
{
    float machineCount = 0;
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        machineCount += totalMachineCountJob(jobTmp);
    return machineCount;
}

/**
 * @brief   Calculates the total time of a job
 * @param   jobHead: head of the job list
 * @return  void
 */
float totalMachineCountJob(job *jobHead)
{
    float machineCount = 0;
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        machineCount += totalMachineCountOperation(operationTmp);
    return machineCount;
}

/**
 * @brief   Calculates the total time of a job
 * @param   jobHead: head of the job list
 * @return  void
 */
float totalMachineCountOperation(operation *operationHead)
{
    float machineCount = 0;
    for (machine *machineTmp = operationHead->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
        machineCount++;
    return machineCount;
}
