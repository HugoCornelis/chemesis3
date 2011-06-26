
#include <stdlib.h>

#include "../../chemesis3/chemesis3.h"


static char *pcVersionTime="(07/02/21) Wednesday, February 21, 2007 12:29:15 hugo";

int main(int argc, char *argv[])
{
    //- obtain version information, report it

    char *pcVersion = Chemesis3GetVersion();

    printf("%s\n", pcVersion);

    exit(EXIT_SUCCESS);
}


// Local variables:
// eval: (add-hook 'write-file-hooks 'time-stamp)
// time-stamp-start: "pcVersionTime="
// time-stamp-format: "\"(%02y/%02m/%02d) %a, %b %d, %y %02H:%02M:%02S %u\";"
// time-stamp-end: "$"
// End:
