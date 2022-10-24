#ifndef __VISUALIZATION_H__
#define __VISUALIZATION_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../cli/cli.h"
#include "../../utils/messages/messages.h"
#include "../../afd/afd.h"

void visualizationEntryPoint(CLI *cli, AFD *afd, int argc, char *argv[]);
void visualization(AFD *afd, FILE *file);

#endif