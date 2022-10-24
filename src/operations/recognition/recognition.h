#include <stdio.h>
#include "../../afd/afd.h"
#include "../../cli/cli.h"

void recognitionEntryPoint(CLI *cli, AFD *afd, int argc, char *argv[]);

char **readWords(char *fileName, int *size_ptr);

void freeWords(char **words, int size);

void writeRecognitionResult(int *result, char *fileName, int size);

char *transitionFunction(AFD *afd, char *symbol, char *current_state);

char *copyString(char *src);
