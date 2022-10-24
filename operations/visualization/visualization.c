#include "visualization.h"

void visualizationEntryPoint(CLI *cli, AFD *afd, int argc, const *argv[])
{
    CliErrors *error = NULL;

    if (argc != 5)
    {
        error = malloc(sizeof(CliErrors));
        error->message = INVALID_ARGUMENTS_QUANTITY;
        cli->error = error;
        cli->hasError = 1;
    }

    if (argv[2] == NULL || argv[4] == NULL)
    {
        error = malloc(sizeof(CliErrors));
        error->message = NOT_PROVIDER_A_FILE;
    }

    if (strcmp("--output", argv[3]) != 0)
    {
        error = malloc(sizeof(CliErrors));
        error->message = NOT_PROVIDER_A_OUTPUT_FILE_FLAG;
    }

    if (error != NULL)
    {
        cli->error = error;
        cli->hasError = 1;
        return;
    }

    cli->secondfile = argv[4];

    FILE *file = fopen(cli->secondfile, "a");

    if (file == NULL)
    {
        error = malloc(sizeof(CliErrors));
        error->message = NOT_PROVIDER_A_FILE;
        cli->error = error;
        cli->hasError = 1;
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

    fprintf(file, "tigraph finite_state_machine {\n");
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