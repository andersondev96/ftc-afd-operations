#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./visualization.h"

void visualizationEntryPoint(CLI *cli, AFD *afd, int argc, char *argv[])
{

    if (argc != 5)
    {
        printf("Quantidade de argumentos inválida, tente novamente!\n");
        return;
    }

    if (argv[2] == NULL || argv[4] == NULL)
    {
        printf("Por favor, informe um arquivo!\n");
        return;
    }

    if (strcmp("--output", argv[3]) != 0)
    {
        printf("Por favor, informe um arquivo para saída!\n");
        return;
    }

    cli->secondfile = argv[4];

    FILE *file = fopen(cli->secondfile, "a");

    if (file == NULL)
    {
        printf("Por favor, informe um arquivo!\n");
        return;
    }

    visualization(afd, file);
}

void visualization(AFD *afd, FILE *file)
{
    char *final = "";

    for (int i = 0; i < afd->quant_final_states; i++)
    {
        char *aux = malloc((sizeof(char) * strlen(final) + 1) + (sizeof(char) * strlen(afd->final_states[i]) + 1));
        strcpy(aux, final);
        final = malloc((sizeof(char) * strlen(final) + 1) + (sizeof(char) * strlen(afd->final_states[i]) + 1));
        strcat(aux, afd->final_states[i]);
        strcat(aux, " ");
        strcpy(final, aux);
    }

    fprintf(file, "digraph finite_state_machine {\n");
    fprintf(file, "\trankdir=LR;\n");
    fprintf(file, "\tnode [shape = doublecircle]; %s;\n", final);
    fprintf(file, "\tnode [shape = circle];\n");

    for (int i = 0; i < afd->quant_transitions; i++)
    {
        fprintf(file, "\t%s -> %s [ label = \"%s\" ];\n", afd->transitions[i].from, afd->transitions[i].to, afd->transitions[i].read);
    }

    fprintf(file, "}\n");
    fclose(file);
}