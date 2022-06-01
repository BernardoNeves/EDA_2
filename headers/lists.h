typedef struct job
{
    int jobNumber;
    struct operation *operationHeadPointer;
    struct job *next;
    struct job *prev;
} job;

typedef struct operation
{
    int operationNumber;
    int jobNumber;
    struct machine *machineHeadPointer;
    struct operation *next;
    struct operation *prev;
} operation;

typedef struct machine
{
    int machineNumber;
    int machineTime;
    struct machine *next;
    struct machine *prev;
} machine;

job *createNewJob(int jobNumber, operation **operationHead);
operation *createNewOperation(int operationNumber, int jobNumber, machine **machineHead);
machine *createNewMachine(int machineNumber);

job insertAfterJob(struct job *jobToInsertAfter, struct job *jobToInsert);
operation insertAfterOperation(struct operation *operationToInsertAfter, struct operation *operationToInsert);
machine insertAfterMachine(struct machine *machineToInsertAfter, struct machine *machineToInsert);

job *insertAtJobHead(job **jobHead, job *jobToInsert);
operation *insertAtOperationHead(operation **operationHead, operation *operationToInsert);
machine *insertAtMachineHead(machine **machineHead, machine *machineToInsert);

job *insertAtJobEnd(job **jobHead, job *jobToInsert);
operation *insertAtOperationEnd(operation **operationHead, operation *operationToInsert);
machine *insertAtMachineEnd(machine **machineHead, machine *machineToInsert);

void orderJob(job *jobHead);
void orderOperation(operation *operationHead);

job *findJob(job *jobHead, int jobNumber);
operation *findOperation(operation *operationHead, int operationNumber);
machine *findMachine(machine *machineHead, int machineNumber);

void *removeJob(job **jobHead, int jobNumber);
void *removeOperation(operation **operationHead, int operationNumber);
void *removeMachine(machine **machineHead, int machineNumber);
