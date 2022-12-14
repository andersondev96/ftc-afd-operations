#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./complement.h"

void complementation(AFD entry, FILE *file)
{

    // Cria o AFD
    AFD complement;

    // Quantidade de estados, símbolos, estados finais e transições
    complement.quant_states = entry.quant_states;
    complement.quant_symbols = entry.quant_symbols;
    int quantStates = (entry.quant_states) - (entry.quant_final_states);
    complement.quant_final_states = quantStates;
    complement.quant_transitions = entry.quant_transitions;

    // Aloca espaço na memória para os estados, símbolos, estados finais e transições
    complement.states = malloc(sizeof(char *) * complement.quant_states);
    complement.symbols = malloc(sizeof(char *) * complement.quant_symbols);
    complement.final_states = malloc(sizeof(char *) * quantStates);
    complement.transitions = malloc(sizeof(Transition *) * complement.quant_transitions);

    // Atribui valor para o estado inicial
    complement.initial_state = entry.initial_state;

    // Atribui valor aos estados
    for (int i = 0; i < entry.quant_states; i++)
    {
        char *state = entry.states[i];
        char *aux = state;
        int size = strlen(aux);
        char *newState = malloc((size + 1) * sizeof(char));
        strcpy(newState, aux);
        strcpy(complement.states[i], newState);
    }

    // Atribui valor aos símbolos
    for (int i = 0; i < entry.quant_symbols; i++)
    {
        char *aux = entry.symbols[i];
        int size = strlen(aux);
        char *symbol = malloc((size + 1) * sizeof(char));
        strcpy(symbol, aux);
        complement.symbols[i] = symbol;
    }

    // Atribui valor aos estados finais
    int cont = 0;
    int index = 0;
    for (int i = 0; i < entry.quant_states; i++)
    {
        char *state = entry.states[i];

        for (int j = 0; j < entry.quant_final_states; j++)
        {
            if (strcmp(entry.states[i], entry.final_states[j]) != 0)
            {
                cont++;
            }
        }

        if (cont == entry.quant_final_states)
        {
            char *aux = state;
            int size = strlen(aux);
            char *newState = malloc((size + 1) * sizeof(char));
            strcpy(newState, aux);
            complement.final_states[index] = newState;
            index++;
        }
        cont = 0;
    }

    // Atribui valor as transições
    for (int i = 0; i < entry.quant_transitions; i++)
    {
        Transition *transitionProduct = getEmptyTransition();
        transitionProduct->from = entry.transitions[i].from;
        transitionProduct->read = entry.transitions[i].read;
        transitionProduct->to = entry.transitions[i].to;
        complement.transitions[i] = *transitionProduct;
    }

    writeFile(&complement, file);
}

void complementationEntryPoint(CLI *cli, AFD *afd, int argc, char *argv[])
{
    // Verifica se há uma quantidade válida de argumentos
    if (argc != 5)
    {
        printf("Quantidade de argumentos inválida, tente novamente!\n");
    }

    // Verifica se foi passado um arquivo
    if (argv[2] == NULL || argv[4] == NULL)
    {
        printf("Por favor, informe um arquivo!\n");
    }

    // Verifica se foi informado um arquivo de saída
    if (strcmp("--output", argv[3]) != 0)
    {
        printf("Por favor, informe um arquivo para saída!\n");
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

    complementation(*afd, file);
}