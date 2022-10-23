#include <stdio.h>
#include "../../afd/afd.h"
#include "../../cli/cli.h"
#include "../../utils/messages/messages.h"

void afdUnion(AFD afd1, AFD afd2, FILE *file);
void unionEntryPoint(CLI *cli, AFD *afd1, AFD *afd2, int argc, char *argv[]);
