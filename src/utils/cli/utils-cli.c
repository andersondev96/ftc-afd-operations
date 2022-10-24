#include "utils-cli.h"

char *getPrefixOfCliInput(char *input)
{

    char *prefix = malloc(sizeof(char) * 2);
    strncpy(prefix, input, sizeof(char) * 2);
    return prefix;
}
