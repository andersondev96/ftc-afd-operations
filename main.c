#include <stdlib.h>
#include <stdio.h>
#include "./cli/cli.h";
#include "./cli/cli.c";

int main(int argc, char **argv[])
{
    CLI *cli = createCLI(argc, argv);
    if (cli->error != NULL)
    {
        printf("\e[1;31mERROR:\e[0;37m %s", cli->error->message);
        return EXIT_FAILURE;
    }

    return 0;
}