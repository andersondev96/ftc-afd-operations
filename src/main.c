#include <stdlib.h>
#include <stdio.h>
#include "./cli/cli.h"
#include "./afd/afd.h"

#include "./operations/complement/complement.h"
#include "./operations/intersection/intersection.h"
#include "./operations/product/product.h"
#include "./operations/union/union.h"
#include "./operations/visualization/visualization.h"
#include "./operations/minimization/minimization.h"
#include "./operations/recognition/recognition.h"

void getCorrectOperation(CLI *cli, int argc, char *argv[])
{

    switch (cli->operation)
    {
    case VISUALIZATION:
        visualizationEntryPoint(cli, readFile(cli, cli->inputfile), argc, argv);
        break;
    case COMPLEMENT:
        complementationEntryPoint(cli, readFile(cli, cli->inputfile), argc, argv);
        break;
    case INTERSECTION:
        intersectionEntryPoint(cli, readFile(cli, argv[2]), readFile(cli, argv[3]), argc, argv);
        break;
    case UNION:
        unionEntryPoint(cli, readFile(cli, argv[2]), readFile(cli, argv[3]), argc, argv);
        break;
    case MINIMIZATION:
        minimizationEntryPoint(cli, readFile(cli, cli->inputfile), argc, argv);
        break;
    case RECOGNIZE:
        recognitionEntryPoint(cli, readFile(cli, cli->inputfile), argc, argv);
        break;
    default:
        printf("Invalid operation, please try again!");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    CLI *cli = createCLI(argc, argv);

    getCorrectOperation(cli, argc, argv);

    return 0;
}