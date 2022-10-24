#ifndef __CLI_H__
#define __CLI_H__

#include <stdlib.h>
#include <stdio.h>
#include "../utils/cli/utils-cli.h"
#include "../afd/afd.h"

typedef enum operations
{
    VISUALIZATION = 1,
    COMPLEMENT = 2,
    INTERSECTION = 3,
    UNION = 4,
    MINIMIZATION = 5,
    RECOGNIZE = 6,

} Operations;

typedef enum readSteps
{
    READ_QUANT_STATES = 1,
    READ_STATES = 2,
    READ_QUANT_SYMBOLS = 3,
    READ_SYMBOLS = 4,
    READ_QUANT_TRANSITIONS = 5,
    READ_TRANSITIONS = 6,
    READ_INITIAL_STATE = 7,
    READ_QUANT_FINAL_STATES = 8,
    READ_FINAL_STATES = 9,

} ReadSteps;

typedef struct _CLI
{
    Operations operation;
    char *inputfile;
    char *secondfile;
    char *output;

} CLI;

CLI *createCLI(int argc, char *argv[]);

Operations getOperation(char *command);

Operations getOperationByText(char *command);

int *isValidInputs(int argc, char *argv[]);

AFD *readFile(CLI *cli, char *filename);

void *writeFile(AFD *afd, FILE *file);

#endif