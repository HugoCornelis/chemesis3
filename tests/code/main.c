

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "main.h"


//v accessible from the outside if needed

struct simobj_Chemesis3 *pch3 = NULL;


//o To use this file :
//o
//o set the variable 'inter' to an intermediary representation,
//o #define CHEMESIS3_TEST_STEPS 1
//o #define CHEMESIS3_TEST_TESTED_THINGS to a dump selection,
//o and so on for the defines below, when not set they get a
//o sensible default value.
//o #include this file, compile, run and parse the output.
//o
//o Chemesis3 construction can also be done using the
//o CHEMESIS3_TEST_CONSTRUCT macro, in which case the global variable
//o pch3 must be preallocated.
//o
//o Tests with multiple chemesis3s must not use this file.
//o

#ifndef CHEMESIS3_TEST_NAME
#define CHEMESIS3_TEST_NAME ("unnamed test")
#endif

#ifndef CHEMESIS3_TEST_CONSTRUCT
#define CHEMESIS3_TEST_CONSTRUCT \
    memcpy(pch3, &ch3, sizeof(ch3));	\
    pch3->iStatus = CHEMESIS3_STATUS_PHASE_2
#endif

#ifndef CHEMESIS3_TEST_INITIATE
#define CHEMESIS3_TEST_INITIATE ((void)1)
#endif

#ifndef CHEMESIS3_TEST_INTERVAL_DEFAULT_START
#define CHEMESIS3_TEST_INTERVAL_DEFAULT_START (-0.1)
#endif

#ifndef CHEMESIS3_TEST_INTERVAL_DEFAULT_END
#define CHEMESIS3_TEST_INTERVAL_DEFAULT_END (0.05)
#endif

#ifndef CHEMESIS3_TEST_INTERVAL_DEFAULT_ENTRIES
#define CHEMESIS3_TEST_INTERVAL_DEFAULT_ENTRIES 3000
#endif

#ifndef CHEMESIS3_TEST_INTERPOL_INTERVAL_DEFAULT_ENTRIES
#define CHEMESIS3_TEST_INTERPOL_INTERVAL_DEFAULT_ENTRIES 149
#endif

#ifndef CHEMESIS3_TEST_OPTIONS
#define CHEMESIS3_TEST_OPTIONS 0
#endif

#ifndef CHEMESIS3_TEST_OUTPUT
#define CHEMESIS3_TEST_OUTPUT ((void)1)
#endif

#ifndef CHEMESIS3_TEST_REPORTING_GRANULARITY
#define CHEMESIS3_TEST_REPORTING_GRANULARITY 1
#endif

#ifndef CHEMESIS3_TEST_SCHEDULE
#define CHEMESIS3_TEST_SCHEDULE ((void)1)
#endif

#ifndef CHEMESIS3_TEST_STEPS
#define CHEMESIS3_TEST_STEPS 10
#endif

#ifndef CHEMESIS3_TEST_TESTED_THINGS
#define CHEMESIS3_TEST_TESTED_THINGS (CHEMESIS3_DUMP_ALL)
#endif


//! no chemesis3 instance allowed to run with a clock smaller than this

#ifndef CHEMESIS3_TEST_TIME_GRANULARITY
#define CHEMESIS3_TEST_TIME_GRANULARITY (1e-9)
#endif


//! default chemesis3 time step, must be bigger than the CHEMESIS3_TEST_TIME_GRANULARITY

#ifndef CHEMESIS3_TEST_TIME_STEP
#define CHEMESIS3_TEST_TIME_STEP (2e-5)
#endif


int WriteOutput(char *pcFilename)
{
    //- set default result : ok

    int iResult = 1;

    //- copy the file content to stdout

    FILE *pfile = fopen(pcFilename, "r");

    char pc[10000];

    size_t st = fread(pc, sizeof(char), sizeof(pc), pfile);

    while (st == 10000)
    {
	fwrite(pc, sizeof(char), st, stdout);

	st = fread(pc, sizeof(char), sizeof(pc), pfile);
    }

    fwrite(pc, sizeof(char), st, stdout);

    //- return result

    return(iResult);
}


int tests_dump(struct simobj_Chemesis3 *pch3, FILE *pfile, int iTested, char *pcMessage, int i)
{
    //! funny : the first '---' in the output are taken as an option
    //! by Expect.pm, which complicates testing a bit.  So just
    //! removed.

    static int iFirst = 1;

    if (iFirst)
    {
	iFirst = 0;
    }
    else
    {
/* 	CHEMESIS3_TEST_TESTED_THINGS && fprintf(pfile, "-------\n"); */
    }

/*     CHEMESIS3_TEST_TESTED_THINGS && fprintf(pfile, pcMessage, i); */

/*     CHEMESIS3_TEST_TESTED_THINGS && Chemesis3Dump(pch3, pfile, iTested); */

    return 1;
}


int main(int argc, char *argv[])
{
    //t use argv for chemesis3 options

    //- set default result : ok

    int iResult = EXIT_SUCCESS;

    //- instantiate a chemesis3 with an initialized intermediary

    //! note: test definition is allowed to allocate the chemesis3, with services.

    if (!pch3)
    {
	pch3 = Chemesis3NewP2(CHEMESIS3_TEST_NAME, &ch3);
    }
    else
    {
	CHEMESIS3_TEST_CONSTRUCT;
    }

    //t need sensible API to set options I guess.

    pch3->dStep = CHEMESIS3_TEST_TIME_STEP;

/*     pch3->ho.dIntervalStart = CHEMESIS3_TEST_INTERVAL_DEFAULT_START; */

/*     pch3->ho.dIntervalEnd = CHEMESIS3_TEST_INTERVAL_DEFAULT_END; */

    //t should set test defaults for basal activator tables.

/*     pch3->ho.dBasalActivatorStart = CHEMESIS3_TEST_INTERVAL_DEFAULT_START; */

/*     pch3->ho.dBasalActivatorEnd = CHEMESIS3_TEST_INTERVAL_DEFAULT_END; */

/*     pch3->ho.iIntervalEntries = CHEMESIS3_TEST_INTERVAL_DEFAULT_ENTRIES; */

/*     pch3->ho.iSmallTableSize = CHEMESIS3_TEST_INTERPOL_INTERVAL_DEFAULT_ENTRIES; */

/*     pch3->ho.iOptions = CHEMESIS3_TEST_OPTIONS; */

    //- build indices for optimization

    Chemesis3CompileP2(pch3);

    //- compile to byte code

    Chemesis3CompileP3(pch3);

    //- initiate values

    Chemesis3Initiate(pch3);

    //- initialize test specific things

    CHEMESIS3_TEST_INITIATE;

    //- initial dump

/*     tests_dump(pch3, stdout, CHEMESIS3_TEST_TESTED_THINGS, "Initiated\n", -1); */

    //! funny : the first '---' in the output are taken as an option
    //! by Expect.pm, which complicates testing a bit.  So just
    //! removed.

    //v final report needed ?

    int iFinalReport = 0;

    //- a couple of times

    int i;

    for (i = 0; i < CHEMESIS3_TEST_STEPS ; i++)
    {
	//- update the current simulation time.

	double dSimulationTime = i * CHEMESIS3_TEST_TIME_STEP + CHEMESIS3_TEST_TIME_GRANULARITY;

	//- step

	Chemesis3Advance(pch3, dSimulationTime);

	//- schedule other objects

	CHEMESIS3_TEST_SCHEDULE;

	//- generate user specified output

	CHEMESIS3_TEST_OUTPUT;

	//- dump

	if (i % CHEMESIS3_TEST_REPORTING_GRANULARITY == 0)
	{
/* 	    tests_dump(pch3, stdout, CHEMESIS3_TEST_TESTED_THINGS, "Iteration %i\n", i); */
	}
	else
	{
	    iFinalReport = 1;
	}
    }

    //- add a final report if necessary

    if (iFinalReport)
    {
/* 	tests_dump(pch3, stdout, CHEMESIS3_TEST_TESTED_THINGS, "Final Iteration\n", i); */
    }

    //- return result

    return(iResult);
}


