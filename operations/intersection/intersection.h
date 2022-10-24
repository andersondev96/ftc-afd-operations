#include <stdio.h>
#include "../../afd/afd.h"
#include "../../cli/cli.h"
#include "../../afd/afd.h"

void afdIntersection(AFD afd1, AFD afd2, FILE *file);
void intersectionEntryPoint(CLI *cli, AFD *afd1, AFD *afd2, int argc, char *argv[]);