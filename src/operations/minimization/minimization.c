#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./minimization.h"
#include "../recognition/recognition.h"

void minimizationEntryPoint(CLI *cli, AFD *afd, int argc, char *argv[])
{
    // Verifica se há uma quantidade válida de argumentos
    if (argc != 5)
    {
        printf("Quantidade de argumentos inválida, tente novamente!\n");
        return;
    }

    // Verifica se foi passado um arquivo
    if (argv[2] == NULL || argv[4] == NULL)
    {
        printf("Por favor, informe um arquivo!\n");
        return;
    }

    // Verifica se foi informado um arquivo de saída
    if (strcmp("--output", argv[3]) != 0)
    {
        printf("Por favor, informe um arquivo para saída!\n");
        return;
    }

    cli->secondfile = argv[4];

    // Abre o arquivo
    FILE *file = fopen(cli->secondfile, "a");

    // Verifica se o arquivo aberto não é NULL
    if (file == NULL)
    {
        printf("Por favor, informe um arquivo!\n");
        return;
    }
}

int isContained(int **values, int value, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (value == values[i])
        {
            return 1;
        }
    }

    return 0;
}

int getEquivalenceGroup(int **groups, int groupsSize, int *sizes, int value)
{
    for (int i = 0; i < groupsSize; i++)
    {
        for (int j = 0; j < sizes[i]; j++)
        {
            if (groups[i][j] == value)
            {
                return i;
            }
        }
    }
    return -1;
}

char mergeStates(AFD *afd, int *states, int size)
{
    int numberSeparators = size - 1;
    int currentSize = numberSeparators + 1;
    char *newState = malloc(sizeof(char) * currentSize);
    int currentIndex = 0;
    for (int i = 0; i < size; i++)
    {
        int stateIndex = states[i];
        char *state = afd->states[stateIndex];
        int stateLength = strlen(state);
        currentSize += stateLength;
        newState = realloc(newState, sizeof(char) * currentSize);
        for (int j = 0; j < stateLength; j++)
        {
            newState[currentIndex] = state[j];
            currentIndex++;
        }

        if (i != size - 1)
        {
            newState[currentIndex] = '_';
            currentIndex++;
        }
    }
    newState[currentIndex] = '\0';
    return newState;
}

AFD *copyAFDWithAccessibleStates(AFD *afd)
{
    AFD *newAFD = getEmptyAFD();
    int *reachables = malloc(sizeof(int));
    int reachableSize = 1;
    reachables[0] = *afd->initial_state;

    newAFD->quant_states = reachableSize;

    newAFD->states = malloc(sizeof(char *) * reachableSize);
    newAFD->final_states = malloc(sizeof(int));
    int finalStateAllocSize = 1;
    int finalStates = 0;
    for (int i = 0; i < reachableSize; i++)
    {
        char *state = afd->states[reachables[i]];

        if (isContained(afd->final_states, reachables[i], afd->quant_final_states))
        {
            if (finalStateAllocSize == finalStates)
            {
                finalStateAllocSize++;
                newAFD->final_states = realloc(newAFD->final_states, sizeof(int) * finalStateAllocSize);
            }

            newAFD->final_states[finalStates] = i;
            finalStates;
        }
    }

    int numberTransitions = 0;
    int allocSize = 1;
    newAFD->transitions = malloc(sizeof(Transition *));

    newAFD->quant_transitions = numberTransitions;
    newAFD->symbols = malloc(sizeof(char *) * (newAFD->quant_symbols));

    *newAFD->initial_state = *afd->initial_state;

    return newAFD;
}

AFD *minimization(AFD *initialAFD)
{
    AFD *afd = copyAFDWithAccessibleStates(initialAFD);

    int **equivalentGroups = malloc(sizeof(int *) * 2);
    int *sizes = malloc(sizeof(int) * 2);
    sizes[0] = afd->quant_final_states;
    sizes[1] = afd->quant_states - (afd->quant_final_states);
    int totalGroups = !sizes[0] || !sizes[1] ? 1 : 2;
    equivalentGroups[0] = sizes[0] ? malloc(sizeof(int) * sizes[0]) : NULL;
    equivalentGroups[1] = sizes[1] ? malloc(sizeof(int) * sizes[1]) : NULL;

    if (!sizes[0])
    {
        sizes[0] = sizes[1];
        equivalentGroups[0] = equivalentGroups[1];
    }

    for (int i = 0; i < afd->quant_final_states; i++)
    {
        equivalentGroups[0][i] = afd->final_states[i];
    }

    int currentStartStateIndex = 0;
    for (int i = 0; i < afd->quant_states; i++)
    {
        if (isContained(afd->final_states, i, afd->quant_final_states))
        {
            continue;
        }
        equivalentGroups[1][currentStartStateIndex] = i;
        currentStartStateIndex++;
    }

    int changed = 0;
}
