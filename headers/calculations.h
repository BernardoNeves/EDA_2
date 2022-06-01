float timeMinProcessPlan(job *jobHead);

float timeMinJob(job *jobHead);
float timeMinOperation(operation *operationTmp);

float timeMaxJob(job *jobHead);
float timeMaxOperation(operation *operationTmp);

float totalMachineTimeJob(job *jobHead);
float totalMachineTimeOperation(operation *operationTmp);

float timeAverageJob(job *jobHead);
float timeAverageOperation(operation *operationTmp);

float totalJobCount(job *jobHead);
float totalMachineCountOperation(operation *operationTmp);
float totalMachineCountJob(job *jobHead);