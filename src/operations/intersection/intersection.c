#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./intersection.h"
#include "../product/product.h"

void intersectionEntryPoint(CLI *cli, AFD *afd1, AFD *afd2, int argc, char *argv[])
{

    // Verifica se há uma quantidade válida de argumentos
    if (argc != 6)
    {
        printf("Quantidade de argumentos inválida, tente novamente!\n");
        return;
    }

    // Verifica se foi passado um arquivo
    if (argv[2] == NULL || argv[3] == NULL || argv[5] == NULL)
    {
        printf("Por favor, informe um arquivo!\n");
        return;
    }

    // Verifica se foi informado um arquivo de saída
    if (strcmp("--output", argv[4]) != 0)
    {
        printf("Por favor, informe um arquivo para saída!\n");
        return;
    }

    cli->secondfile = argv[5];

    // Abre o arquivo
    FILE *file = fopen(cli->secondfile, "a");

    // Verifica se o arquivo aberto não é NULL
    if (file == NULL)
    {
        printf("Por favor, informe um arquivo!\n");
        return;
    }

    afdIntersection(*afd1, *afd2, file);
}

void afdIntersection(AFD afd1, AFD afd2, FILE *file)
{
    // Criando AFD de interseção a partir do produto entre duas AFDs
    AFD intersection = afdProduct(afd1, afd2);

    // Quantidade de estados finais
    int quantStates = (afd1.quant_final_states) * (afd2.quant_final_states);
    intersection.quant_final_states = quantStates;

    // Alocar memória para os estados finais
    intersection.final_states = malloc(sizeof(char *) * quantStates);

    int indexFinalState = 0;
    for (int i = 0; i < afd1.quant_states; i++)
    {
        // estado da AFD 1
        char *state1 = afd1.states[i];

        for (int j = 0; j < afd2.quant_states; j++)
        {

            // Estado da AFD 2
            char *state2 = afd2.states[j];

            // Concatenação entre os 2 estados
            int size = strlen(state1);
            char *stateProduct = malloc((size + 1) * sizeof(char));
            strcpy(stateProduct, state1);
            strcat(stateProduct, "and");
            strcat(stateProduct, state2);

            // Indicar o esatado final da AFD produto, neste caso os dois estados devem ser finais em suas AFDs de origem

            for (int k = 0; k < afd1.quant_final_states; k++)
            {
                for (int l = 0; l < afd2.quant_final_states; l++)
                {
                    if ((strcmp(state1, afd1.final_states[k]) == 0) && (strcmp(state2, afd2.final_states[l]) == 0))
                    {
                        intersection.final_states[indexFinalState] = stateProduct;
                        indexFinalState++;
                    }
                }
            }
        }
    }

    // Retorna inteseção
    writeFile(&intersection, file);
}