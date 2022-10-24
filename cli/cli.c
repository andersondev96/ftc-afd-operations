#include "cli.h"
#include <inttypes.h>
#include <string.h>

CliErrors *isValidInputs(int argc, char *argv[])
{
    CliErrors *error = NULL;

    if (argc < 3)
    {
        error = malloc(sizeof(CliErrors));
        error->message = INVALID_ARGUMENTS_QUANTITY;
    }

    if (strcmp(getPrefixOfCliInput(argv[1]), "--") != 0)
    {
        error = malloc(sizeof(CliErrors));
        error->message = INVALID_PREFIX_OPERATION;
    }

    return error;
}

CLI *createCLI(int argc, char *argv[])
{
    CliErrors *error = isValidInputs(argc, argv);
    CLI *cli = (CLI *)malloc(sizeof(CLI));

    if (error != NULL)
    {
        cli->error = error;
        cli->hasError = 1;
        return cli;
    }

    Operations operation = getOperation(argv[1]);

    if (operation == -1)
    {
        cli->error = malloc(sizeof(CliErrors));
        cli->error->message = INVALID_OPERATION;
        cli->hasError = 1;
        return cli;
    }

    cli->operation = operation;
    cli->hasError = 0;
    cli->inputfile = argv[2];

    return cli;
}

Operations getOperation(char *command)
{
    return getOperationByText(command);
}

Operations getOperationByText(char *command)
{
    char operationsText[][1000] = {
        "--dot",
        "--complemento",
        "--intersecao",
        "--uniao",
        "--minimization",
        "--recognize"};

    Operations operations[] = {1, 2, 3, 4, 5, 6};

    for (int i = 0; i < 6; i++)
    {
        if (strcmp(command, operationsText[i]) == 0)
        {
            return operations[i];
        }
    }

    return -1;
}

char **splitBySpace(char *line)
{
    char **result = malloc(sizeof(char) * 3);
    char *pch = strtok(line, " ");
    int i = 0;
    while (pch != NULL)
    {
        result[i] = pch;
        pch = strtok(NULL, " ");
        i++;
    }
    return result;
}

AFD *readFile(CLI *cli, char *filename)
{
    strcpy(filename, filename);

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        cli->error = malloc(sizeof(CliErrors));
        cli->error->message = FILE_NOT_FOUND;
        cli->hasError = 1;

        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;

    ReadSteps readSteps = READ_QUANT_STATES;
    AFD *afd = getEmptyAFD();

    int aux = 0;

    while ((read = getline(&line, &len, file)) != -1)
    {
        int end = 0;

        if (end == 1)
        {
            break;
        }

        switch (readSteps)
        {
        case READ_QUANT_STATES:
            afd->quant_states = atoi(line);
            readSteps = READ_STATES;
            aux = atoi(line);
            afd->states = malloc(sizeof(char *) * aux);
            break;

        case READ_STATES:
            afd->states[aux - 1] = malloc(sizeof(char) * 1000);
            strcpy(afd->states[aux - 1], strtok(line, "\n"));
            aux--;
            if (aux == 0)
            {
                readSteps = READ_QUANT_SYMBOLS;
            }
            break;

        case READ_QUANT_SYMBOLS:
            afd->quant_symbols = atoi(line);
            readSteps = READ_SYMBOLS;
            aux = atoi(line);
            afd->symbols = malloc(sizeof(char *) * aux);
            break;

        case READ_SYMBOLS:
            afd->symbols[aux - 1] = malloc(sizeof(char *) * 1000);
            strcpy(afd->symbols[aux - 1], strtok(line, "\n"));
            aux--;
            if (aux == 0)
            {
                readSteps = READ_QUANT_TRANSITIONS;
            }
            break;

        case READ_QUANT_TRANSITIONS:
            afd->quant_transitions = atoi(line);
            readSteps = READ_TRANSITIONS;
            aux = atoi(line);
            afd->transitions = malloc(sizeof(Transition) * aux);
            break;

        case READ_TRANSITIONS:
        {
            Transition *transition = getEmptyTransition();

            char *values = malloc(sizeof(char) * strlen(line));
            strcpy(values, line);

            char **sentences = splitBySpace(values);

            transition->from = strtok(sentences[0], "\n");
            transition->read = strtok(sentences[1], "\n");
            transition->to = strtok(sentences[2], "\n");

            afd->transitions[aux - 1] = *transition;

            aux--;
            if (aux == 0)
            {
                readSteps = READ_INITIAL_STATE;
            }
            break;
        }

        case READ_INITIAL_STATE:
            afd->initial_state = line;
            readSteps = READ_QUANT_FINAL_STATES;
            break;

        case READ_QUANT_FINAL_STATES:
            afd->quant_final_states = atoi(line);
            readSteps = READ_FINAL_STATES;
            aux = atoi(line);
            afd->final_states = malloc(sizeof(char *) * aux);
            break;

        case READ_FINAL_STATES:
            afd->final_states[aux - 1] = malloc(sizeof(char) * 1000);
            strcpy(afd->final_states[aux - 1], strtok(line, "\n"));
            aux--;
            if (aux == 0)
            {
                end = 1;
            }
            break;

        default:
            break;
        }
    }

    fclose(file);

    return afd;
}

void *writeFile(AFD *afd, FILE *file)
{

    fprintf(file, "%d\n", afd->quant_states);
    for (int i = 0; i < afd->quant_states; i++)
    {
        fprintf(file, "%s\n", strtok(afd->states[i], "\n"));
    }

    fprintf(file, "%d\n", afd->quant_symbols);
    for (int i = 0; i < afd->quant_symbols; i++)
    {
        fprintf(file, "%s\n", strtok(afd->symbols[i], "\n"));
    }

    fprintf(file, "%d\n", afd->quant_transitions);
    for (int i = 0; i < afd->quant_transitions; i++)
    {
        fprintf(file, "%s %s %s\n", afd->transitions[i].from, afd->transitions[i].read, afd->transitions[i].to);
    }

    fprintf(file, "%s\n", afd->initial_state);
    fprintf(file, "%d\n", afd->quant_final_states);

    for (int i = 0; i < afd->quant_final_states; i++)
    {
        fprintf(file, "%s\n", strtok(afd->final_states[i], "\n"));
    }

    fclose(file);
}