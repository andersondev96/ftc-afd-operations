#include <stdio.h>
#include "../../afd/afd.h"
#include "../../cli/cli.h"

void minimizationEntryPoint(CLI *cli, AFD *afd, int argc, char *argv[]);
int isContained(int **values, int value, int size);
int getEquivalenceGroup(int **groups, int groupsSize, int *sizes, int value);
char mergeStates(AFD *afd, int *states, int size);
AFD *copyAFDWithAccessibleStates(AFD *afd);
AFD *minimization(AFD *initialAFD);