
#include "./afd.h"

// Faz a alocação da Transition
Transition *getEmptyTransition()
{
    Transition *transition = malloc(sizeof(Transition));
    transition->from = malloc(sizeof(int));
    transition->read = malloc(sizeof(int));
    transition->to = malloc(sizeof(int));
    return transition;
}

// Faz a alocação do AFD
AFD *getEmptyAFD()
{
    AFD *afd = malloc(sizeof(AFD));
    afd->quant_states = (long)malloc(sizeof(int));
    afd->quant_symbols = (long)malloc(sizeof(int));
    afd->quant_transitions = (long)malloc(sizeof(int));
    afd->quant_final_states = (long)malloc(sizeof(int));
    afd->initial_state = malloc(sizeof(int));

    return afd;
}

// Libera a transition
void freeTransition(Transition *transition)
{
    free(transition->from);
    free(transition->to);
    free(transition->read);
}

// Libera a AFD
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