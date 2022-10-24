#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./product.h"

AFD afdProduct(AFD afd1, AFD afd2)
{
    // Criar AFD vazio
    AFD product;

    // Quantidade de estados ( m * n )
    int quantStates = (afd1.quant_states) * (afd2.quant_states);
    product.quant_states = quantStates;

    // Alocação de memória para os estados do AFD produto
    product.states = malloc(sizeof(char *) * quantStates);

    // Símbolos utilizados
    product.quant_symbols = afd2.quant_symbols;
    product.symbols = malloc((product.quant_symbols) * sizeof(char *));

    // Adiciona os símbolos que foram utilizados nos AFDs no AFD produto
    for (int i = 0; i < afd2.quant_symbols; i++)
    {
        char *aux = afd2.symbols[i];
        int size = strlen(aux);
        char *symbol = malloc((size + 1) * sizeof(char));
        strcpy(symbol, aux);
        product.symbols[i] = symbol;
    }

    // Cria estados possíveis realizando o produto entre dois AFDs
    int index = 0;
    int indexFinalState = 0;
    for (int i = 0; i < afd1.quant_states; i++)
    {

        // Estado do AFD1
        char *state1 = afd1.states[i];
        for (int j = 0; j < afd2.quant_states; j++)
        {

            // Estado do AFD2
            char *state2 = afd2.states[j];

            // Concatenação entre dois estados
            int size = strlen(state1);
            char *stateProduct = malloc((size + 1) * sizeof(char));
            strcpy(stateProduct, state1);
            strcat(stateProduct, "and");
            strcat(stateProduct, state2);
            product.states[index] = stateProduct;

            // Indicar o estado inicial do AFD do produto, neste caso, verifica se os estados são iniciais em suas AFDs de origem
            if ((strcmp(state1, afd1.initial_state) == 0) && (strcmp(state2, afd2.initial_state) == 0))
            {
                product.initial_state = stateProduct;
            }

            index++;
        }
    }

    // Realizar transição dos estados

    product.quant_transitions = quantStates * (product.quant_symbols);
    product.transitions = malloc(sizeof(Transition *) * (product.quant_transitions));

    index = 0;

    for (int i = 0; i < product.quant_states; i++)
    {
        char *state = product.states[i];

        // Cópia do estado que será utilizado
        char *copy = state;
        int size = strlen(copy);
        char *newState = malloc((size + 1) * sizeof(char));
        strcpy(newState, copy);

        /* Separa os estados para verificar qual foi a transição feita
        por cada para encontrar o estado de transição correspondente
        ao AFD de cada produto.
        */

        char *aux;
        char **split = malloc(2 * sizeof(char *));
        aux = strtok(newState, "and");
        int x = 0;

        while (aux != NULL)
        {
            split[x] = aux;
            aux = strtok(NULL, "and");
            x++;
        }

        for (int j = 0; j < product.quant_symbols; j++)
        {
            char *symbol = strtok(product.symbols[j], "\n");
            char *to1;
            char *to2;

            // Transição para o estado 1

            for (int k = 0; k < afd1.quant_symbols; k++)
            {

                if (strcmp(split[0], afd1.transitions[k].from) == 0)
                {
                    if (strcmp(symbol, afd1.transitions[k].read) == 0)
                    {
                        to1 = strtok(afd1.transitions[k].to, "\n");
                    }
                }
            }

            for (int k = 0; k < afd2.quant_transitions; k++)
            {
                if (strcmp(split[1], afd2.transitions[k].from) == 0)
                {
                    if (strcmp(symbol, afd2.transitions[k].read) == 0)
                    {
                        to2 = strtok(afd2.transitions[k].to, "\n");
                    }
                }
            }

            char *stateTo = malloc((strlen(to1) + 1 + strlen(to2)) * sizeof(char));
            strcpy(stateTo, to1);
            strcat(stateTo, "and");
            strcat(stateTo, to2);

            Transition *transitionProduct = getEmptyTransition();

            strcpy(transitionProduct->from, state);
            strcpy(transitionProduct->read, symbol);
            strcpy(transitionProduct->to, stateTo);

            product.transitions[index] = *transitionProduct;
            index++;
        }
    }

    return product;
}