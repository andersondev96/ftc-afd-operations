#ifndef __AFD_H__
#define __AFD_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct transition_state
{
    char *from;
    char *read;
    char *to;

} Transition;

typedef struct afd_state
{
    char **states;
    int quant_states;

    char **symbols;
    char quant_symbols;

    char *initial_state;

    char **final_states;
    char quant_final_states;

    Transition *transitions;
    int quant_transitions;

} AFD;

Transition *getTransition(AFD *afd, char *from, char *to, char *read);

Transition *getEmptyTransition();

int getStatePosition(AFD *afd, char *state);

int getSymbolPosition(AFD *afd, char *symbol);

AFD *getEmptyAFD();

AFD *readAFD(char *fileName);

void writeAFD(AFD *afd, char *fileName);

void freeAFD(AFD *afd);

#endif