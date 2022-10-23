#include <stdio.h>
#include "../../afd/afd.h"
#include "../../cli/cli.h"
#include "../../utils/messages/messages.h"
#include "../../afd/afd.h"

void addIntersection(AFD afd1, AFD afd2, FILE *file);
void intersectionEntryPoint(CLI *cli, AFD *afd1, AFD *afd2, int argc, char *argv[]);