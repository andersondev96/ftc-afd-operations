
#include "./afd.h"

Transition *getEmptyTransition()
{
    Transition *transition = malloc(sizeof(Transition));
    transition->from = malloc(sizeof(int));
    transition->read = malloc(sizeof(int));
    transition->to = malloc(sizeof(int));
    return transition;
}

AFD *getEmptyAFD()
{
    AFD *afd = malloc(sizeof(AFD));
    afd->quant_states = (int)malloc(sizeof(int));
    afd->quant_symbols = (int)malloc(sizeof(int));
    afd->quant_transitions = (int)malloc(sizeof(int));
    afd->quant_final_states = (int)malloc(sizeof(int));
    afd->initial_state = malloc(sizeof(int));

    return afd;
}

void freeTransition(Transition *transition)
{
    free(transition->from);
    free(transition->to);
    free(transition->read);
}

void freeAFD(AFD *afd)
{
    for (int i = 0; i < afd->quant_states; i++)
    {
        free(afd->states[i]);
    }

    for (int i = 0; i < afd->quant_symbols; i++)
    {
        free(afd->symbols[i]);
    }

    for (int i = 0; i < afd->quant_transitions; i++)
    {
        freeTransition(&afd->transitions[i]);
    }

    free(afd->transitions);
    free(afd->symbols);
    free(afd->states);
    free(afd->final_states);
    free(afd->initial_state);
}