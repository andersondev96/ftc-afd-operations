#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./recognition.h"

void recognitionEntryPoint(CLI *cli, AFD *afd, int argc, char *argv[])
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

char **readWords(char *fileName, int *size_ptr)
{
    FILE *file = fopen(fileName, "r");

    if (!file)
    {
        return NULL;
    }

    int size = 0;
    int **words = NULL;
    char buffer[100];

    while (fscanf(file, "%s\n", buffer) != EOF)
    {
        char *word = copyString(buffer);
        size++;
        if (words)
        {
            words = realloc(words, sizeof(char *) * size);
        }
        else
        {
            words = malloc(sizeof(char *));
        }
        words[size - 1] = word;
    }

    *size_ptr = size;
    fclose(file);
    return words;
}

void freeWords(char **words, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(words[i]);
    }

    free(words);
}

void writeRecognitionResult(int *result, char *fileName, int size)
{
    FILE *file = fopen(fileName, "w");
    if (!file)
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d\n", result[i]);
    }
}

char *copyString(char *src)
{
    char *newString = malloc(sizeof(char) * strlen(src) + 1);
    strcpy(newString, src);
    return newString;
}