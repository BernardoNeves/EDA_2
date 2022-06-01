/**
 * @file Files.c
 * @author Bernardo Neves (a23494@alunos.ipca.pt)
 * @brief   Read and write files
 * @date 2022-06-01
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"
#include "files.h"

/**
 * @brief   Reads a file and returns a job list
 * @param   fileName: name of the file to be read
 * @return  jobHead: head of the job list
 */
job *read(char fileName[])
{
    job *jobHead = NULL, *jobTmp;
    machine *machineHead = NULL, *machineTmp;
    operation *operationHead = NULL, *operationTmp;
    int machineNumber, operationNumber;
    char buffer = '>';

    FILE *ProcessPlan = fopen(fileName, "r");
    if (ProcessPlan == NULL)
        return NULL;
    fscanf(ProcessPlan, "%*c");
    for (int jobNumber = 1; !feof(ProcessPlan); jobNumber++, fscanf(ProcessPlan, "%*c %c", &buffer))
    {
        for (operationNumber = 1, operationHead = NULL; buffer == '>'; operationNumber++, machineHead = NULL, fscanf(ProcessPlan, "%*c %c", &buffer))
        {
            while (fscanf(ProcessPlan, " %d", &machineNumber) == 1)
            {
                machineTmp = createNewMachine(machineNumber);
                machineHead = insertAtMachineEnd(&machineHead, machineTmp);
            }
            for (fscanf(ProcessPlan, "%*c %c", &buffer), machineTmp = machineHead; fscanf(ProcessPlan, " %d", &machineNumber) == 1; machineTmp = machineTmp->next)
                machineTmp->machineTime = machineNumber;
            operationTmp = createNewOperation(operationNumber, jobNumber, &machineHead);
            operationHead = insertAtOperationEnd(&operationHead, operationTmp);
        }
        jobTmp = createNewJob(jobNumber, &operationHead);
        jobHead = insertAtJobEnd(&jobHead, jobTmp);
    }
    fclose(ProcessPlan);
    return jobHead;
}

/**
 * @brief   Writes a job list to a file
 * @param   fileName: name of the file to be written
 * @param   jobHead: head of the job list
 * @return  void
 */
job *write(char fileName[], job *jobHead)
{
    for (int i = 0; i < strlen(fileName); i++)
        if (fileName[i] == '.')
            fileName[i] = '\0';
    strcat(fileName, "New.txt");

    FILE *ProcessPlan = fopen(fileName, "w");
    if (ProcessPlan == NULL)
        return NULL;
    for (job *jobTmp = jobHead; jobTmp != NULL; jobTmp = jobTmp->next)
    {
        for (operation *operationTmp = jobTmp->operationHeadPointer; operationTmp != NULL; operationTmp = operationTmp->next)
        {
            fprintf(ProcessPlan, ">");
            for (machine *machineTmp = operationTmp->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
                fprintf(ProcessPlan, (machineTmp->next != NULL) ? "%d " : "%d,\n>", machineTmp->machineNumber);
            for (machine *machineTmp = operationTmp->machineHeadPointer; machineTmp != NULL; machineTmp = machineTmp->next)
                fprintf(ProcessPlan, (machineTmp->next != NULL) ? "%d " : "%d,\n", machineTmp->machineTime);
        }
        fprintf(ProcessPlan, (jobTmp->next != NULL) ? "-,\n" : "-,");
    }
    fclose(ProcessPlan);
    return jobHead;
}
