#ifndef __COMPLEMENT_H__
#define __COMPLEMENT_H__
#endif

#include "../../cli/cli.h"
#include "../../utils/messages/messages.h"
#include "../../afd/afd.h"

void complementation(AFD entry, FILE *file);

void complementationEntryPoint(CLI *cli, AFD *afd, int argc, char *argv[]);