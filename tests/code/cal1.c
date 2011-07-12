

#include <stdlib.h>

#include "../../chemesis3/addressing.h"
#include "../../chemesis3/chemesis3.h"

#include <experiment/output.h>


#define CHEMESIS3_TEST_STEPS 1000


int piReactions[] =
{
    0,
};

int piSomaCaFlags[] =
{
    0,
};

int piSomaCabufFlags[] =
{
    1,
};

int piSomabufFlags[] =
{
    -1,
};

int piSomabufPools[] =
{
    1,
};

int piSomabufPoolsFlags[] =
{
    0,
};


struct ch3_pool somaCa[3] =
{
    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Pool,

#ifdef CHEMESIS3_SOURCE_NEUROSPACES

	    /// identification

	    ADDRESSING_NEUROSPACES_2_CHEMESIS3(2),

#endif

#ifdef CHEMESIS3_SOURCE_TYPING

	    /// model source type number

	    /// \note source typing is used to compute aggregate currents ao
	    /// \note things.

	    -1,

#endif

#ifdef CHEMESIS3_SIZED_MATH_STRUCTURES

	    /// size of this structure

	    sizeof(struct ch3_pool),

#endif

	},

	//m indexes of attached reactions

	sizeof(piReactions) / sizeof(int),

	piReactions,

	//m and how they are used, flags for each attached reaction

	piSomaCaFlags,

	//m indexes of attached pools

	0,

	NULL,

	NULL,

	//m indexes of attached diffusion elements

	0,

	NULL,

	NULL,

	//m initial concentration

	0.001, // 0.1e-3,

	//m current concentration

	0.0,

	//m compartment volume as calculated by the model container

	1.085733504e-08,

	//m to be removed, should be transparent: units

	1e-3,

	//m number of entities

	0.0,

	//m for conserve pool

	0,

	0.0,

	0.0,

    },
    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Pool,

#ifdef CHEMESIS3_SOURCE_NEUROSPACES

	    /// identification

	    ADDRESSING_NEUROSPACES_2_CHEMESIS3(3),

#endif

#ifdef CHEMESIS3_SOURCE_TYPING

	    /// model source type number

	    /// \note source typing is used to compute aggregate currents ao
	    /// \note things.

	    -1,

#endif

#ifdef CHEMESIS3_SIZED_MATH_STRUCTURES

	    /// size of this structure

	    sizeof(struct ch3_pool),

#endif

	},

	//m indexes of attached reactions

	sizeof(piReactions) / sizeof(int),

	piReactions,

	//m and how they are used, flags for each attached reaction

	piSomaCabufFlags,

	//m indexes of attached pools

	0,

	NULL,

	NULL,

	//m indexes of attached diffusion elements

	0,

	NULL,

	NULL,

	//m initial concentration

	0.003,

	//m current concentration

	0.0,

	//m compartment volume as calculated by the model container

	1.085733504e-08,

	//m to be removed, should be transparent: units

	1e-3,

	//m number of entities

	0.0,

	//m for conserve pool

	0,

	0.0,

	0.0,

    },
    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Pool,

#ifdef CHEMESIS3_SOURCE_NEUROSPACES

	    /// identification

	    ADDRESSING_NEUROSPACES_2_CHEMESIS3(4),

#endif

#ifdef CHEMESIS3_SOURCE_TYPING

	    /// model source type number

	    /// \note source typing is used to compute aggregate currents ao
	    /// \note things.

	    -1,

#endif

#ifdef CHEMESIS3_SIZED_MATH_STRUCTURES

	    /// size of this structure

	    sizeof(struct ch3_pool),

#endif

	},

	//m indexes of attached reactions

	0,

	NULL,

	//m and how they are used, flags for each attached reaction

	piSomabufFlags,

	//m indexes of attached pools

	1,

	piSomabufPools,

	piSomabufPoolsFlags,

	//m indexes of attached diffusion elements

	0,

	NULL,

	NULL,

	//m initial concentration

	0.153,

	//m current concentration

	0.0,

	//m compartment volume as calculated by the model container

	1.085733504e-08,

	//m to be removed, should be transparent: units

	0.0,

	//m number of entities

	0.0,

	//m for conserve pool

	1,

	0.0,

	0.153,

    },
};


int piSubstrates[] =
{
    0,
    2,
};

int piProducts[] =
{
    1,
};

struct ch3_reaction somacabufrxn =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_Reaction,

#ifdef CHEMESIS3_SOURCE_NEUROSPACES

	/// identification

	ADDRESSING_NEUROSPACES_2_CHEMESIS3(5),

#endif

#ifdef CHEMESIS3_SOURCE_TYPING

	/// model source type number

	/// \note source typing is used to compute aggregate currents ao
	/// \note things.

	-1,

#endif

#ifdef CHEMESIS3_SIZED_MATH_STRUCTURES

	/// size of this structure

	sizeof(struct ch3_reaction),

#endif

    },

    //m number of substrates

    sizeof(piSubstrates) / sizeof(int),

    //m indexes of substrates

    piSubstrates,

    //m number of end products

    sizeof(piProducts) / sizeof(int),

    //m indexes of end product

    piProducts,

    //m backward rate

    0.5,

    0.0,

    //m forward rate

    1e2,

    0.0,

};


struct simobj_Chemesis3 ch3 =
{
    /// name of this object

    /// \note whether the name of a chemesis3 solver is a system wide
    /// id depends on the environment, chemesis3 does not (and cannot)
    /// enforce it.

    "cal1",

    /// status : reflects phases of compilation.

    0,

    0,

    /// serial range covered by this solver

    1,

    1000,

    /// options

    {
	/// global options and operation mode.

	0,
    },

    //m current simulation time

    0.0,

    //m time step

    0.0,

    /// identification service : translates serials to math components.

    /// \note so to use this feature: define your translation service, and
    /// \note set it during the construction of your heccer.

    /// \note wouldn't be surprised that I need several layers of services,
    /// \note will see if that has repercussion at this low level or not.
    ///
    /// \note for the moment we have a function layer, which is fixed, and
    /// \note a data layer, which is opaque.  The function layer defines the
    /// \note real interface.

    NULL,

    /// event distribution service: given an event, distributes it over the targets

    /// \note so to use this feature: define your event distribution service, and
    /// \note set it during the construction of your heccer.

    /// \note wouldn't be surprised that I need several layers of services,
    /// \note will see if that has repercussion at this low level or not.
    ///
    /// \note for the moment we have a function layer, which is fixed, and
    /// \note a data layer, which is opaque.  The function layer defines the
    /// \note real interface.

    NULL,

    /// event reception service: receive an event, and queue till it fires

    /// \note so to use this feature: define your event reception service, and
    /// \note set it during the construction of your heccer.

    /// \note wouldn't be surprised that I need several layers of services,
    /// \note will see if that has repercussion at this low level or not.
    ///
    /// \note for the moment we have a function layer, which is fixed, and
    /// \note a data layer, which is opaque.  The function layer defines the
    /// \note real interface.

    NULL,

    //m minumum concentration level

    0.0,

    //m all pools

    3,

    somaCa,

    //m all reactions

    1,

    &somacabufrxn,

    //m all diffusion elements

    0,

    NULL,

    //m all aggregators: derived variables not directly available from a model's viewpoint

    0,

    NULL,

};


struct OutputGenerator *pog = NULL;

char pcStep[100] = "";

#include "main.h"


int main(int argc, char *argv[])
{
    //- set default result : ok

    int iResult = EXIT_SUCCESS;

    //- link spiking element to output generator

    pog = OutputGeneratorNew("/tmp/output_cal1");

    OutputGeneratorInitiate(pog);

//d prepare output of concentration

#define CHEMESIS3_TEST_INITIATE \
    double *pdConcentration1 = Chemesis3AddressVariable(pch3, 2, "concentration"); \
    OutputGeneratorAddVariable(pog, "concentration", pdConcentration1);	\
    double *pdConcentration2 = Chemesis3AddressVariable(pch3, 3, "concentration"); \
    OutputGeneratorAddVariable(pog, "concentration", pdConcentration2);	\
    double *pdConcentration3 = Chemesis3AddressVariable(pch3, 4, "concentration"); \
    OutputGeneratorAddVariable(pog, "concentration", pdConcentration3);

//d generate output of concentration

#define CHEMESIS3_TEST_OUTPUT \
    OutputGeneratorAnnotatedStep(pog, sprintf(pcStep, "%g", dSimulationTime) ? pcStep : "sprintf() failed")

    //- do the simulation

    simulate(argc,argv);

    //- finish the simulation output

    OutputGeneratorFinish(pog);

    //- add the simulation output to the program output

    WriteOutput("/tmp/output_cal1");

    //- return result

    return(iResult);
}


#define main(argc,argv) simulate(argc,argv)

//t this prototype can give warning and perhaps errors.

int main(int argc, char *argv[]);


#include "main.c"


