#include <stdio.h>
#include <stdlib.h>
#include "lists.h"
#include "calculations.h"

// float timeMinProcessPlan(job *jobHead)
// {
// float totalTime = 0.0;
// for (int i = 0, machineCount = 0; i < totalMachineCountProcessPlan(jobHead); i++, machineCount = 0)
//     for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
//         for (operation *operationTmp = jobTmp->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
//             for (machine *machineTmp = operationTmp->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
//             {
//                 machineCount++;
//                 if (machineCount == i)
//                 {
//                     totalTime += operationTmp->machineHeadPointer->machineTime;
//                     operationTmp = operationTmp->next;
//                     break;
//                 }
//                 else
//                     totalTime += operationTmp->machineHeadPointer->machineTime;

//             }
// }

float timeMinProcessPlan(job *jobHead)
{
    float totalTime = 0;
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        totalTime += timeMinJob(jobTmp);
    return totalTime;
}

float timeMinJob(job *jobHead)
{
    float totalTime = 0;
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        totalTime += timeMinOperation(operationTmp);
    return totalTime;
}

float timeMinOperation(operation *operationHead)
{
    machine *minTimeMachine = operationHead->machineHeadPointer;
    for (machine *machineTmp = operationHead->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
        if (minTimeMachine->machineTime > machineTmp->machineTime)
            minTimeMachine = machineTmp;
    return (float)minTimeMachine->machineTime;
}

float timeMaxJob(job *jobHead)
{
    float totalTime = 0;
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        totalTime += timeMaxOperation(operationTmp);
    return totalTime;
}

float timeMaxOperation(operation *operationHead)
{
    machine *maxTimeMachine = operationHead->machineHeadPointer;
    for (machine *machineTmp = operationHead->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
        if (maxTimeMachine->machineTime < machineTmp->machineTime)
            maxTimeMachine = machineTmp;
    return (float)maxTimeMachine->machineTime;
}

float timeAverageOperation(operation *operationHead)
{
    return totalMachineTimeOperation(operationHead) / totalMachineCountOperation(operationHead);
}

float timeAverageJob(job *jobHead)
{
    float totalTime = 0;
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        totalTime += timeAverageOperation(operationTmp);
    return totalTime;
}

float totalJobCount(job *jobHead)
{
    float jobCount = 0;
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        jobCount++;
    return jobCount;
}
float totalMachineTimeOperation(operation *operationHead)
{
    float totalTime = 0;
    for (machine *machineTmp = operationHead->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
        totalTime += machineTmp->machineTime;
    return totalTime;
}

float totalMachineCountProcessPlan(job *jobHead)
{
    float machineCount = 0;
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
        machineCount += totalMachineCountJob(jobTmp);
    return machineCount;
}

float totalMachineCountJob(job *jobHead)
{
    float machineCount = 0;
    for (operation *operationTmp = jobHead->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        machineCount += totalMachineCountOperation(operationTmp);
    return machineCount;
}

float totalMachineCountOperation(operation *operationHead)
{
    float machineCount = 0;
    for (machine *machineTmp = operationHead->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
        machineCount++;
    return machineCount;
}
