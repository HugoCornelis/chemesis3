

#include <stdlib.h>

#include "../../chemesis3/addressing.h"
#include "../../chemesis3/chemesis3.h"

#include <experiment/output.h>


#define CHEMESIS3_TEST_STEPS 1000


int piReactionsSoma[] =
{
    0,
};

int piCaFlagsSoma[] =
{
    0,
};

int piCaBufFlagsSoma[] =
{
    1,
};

int piBufFlagsSoma[] =
{
    -1,
};

int piBufPoolsSoma[] =
{
    1,
};

int piBufPoolsFlagsSoma[] =
{
    0,
};


int piReactionsDendrite[] =
{
    1,
};

int piCaFlagsDendrite[] =
{
    0,
};

int piCaBufFlagsDendrite[] =
{
    1,
};

int piBufFlagsDendrite[] =
{
    -1,
};

int piBufPoolsDendrite[] =
{
    4,
};

int piBufPoolsFlagsDendrite[] =
{
    0,
};


struct ch3_pool ca[6] =
{
    //m soma

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

	sizeof(piReactionsSoma) / sizeof(int),

	piReactionsSoma,

	//m and how they are used, flags for each attached reaction

	piCaFlagsSoma,

	//m indexes of attached pools

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

	sizeof(piReactionsSoma) / sizeof(int),

	piReactionsSoma,

	//m and how they are used, flags for each attached reaction

	piCaBufFlagsSoma,

	//m indexes of attached pools

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

	piBufFlagsSoma,

	//m indexes of attached pools

	1,

	piBufPoolsSoma,

	piBufPoolsFlagsSoma,

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

    //m dendrite

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Pool,

#ifdef CHEMESIS3_SOURCE_NEUROSPACES

	    /// identification

	    ADDRESSING_NEUROSPACES_2_CHEMESIS3(6),

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

	sizeof(piReactionsDendrite) / sizeof(int),

	piReactionsDendrite,

	//m and how they are used, flags for each attached reaction

	piCaFlagsDendrite,

	//m indexes of attached pools

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

	    ADDRESSING_NEUROSPACES_2_CHEMESIS3(7),

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

	sizeof(piReactionsDendrite) / sizeof(int),

	piReactionsDendrite,

	//m and how they are used, flags for each attached reaction

	piCaBufFlagsDendrite,

	//m indexes of attached pools

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

	    ADDRESSING_NEUROSPACES_2_CHEMESIS3(8),

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

	piBufFlagsDendrite,

	//m indexes of attached pools

	1,

	piBufPoolsDendrite,

	piBufPoolsFlagsDendrite,

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


int piSubstratesSoma[] =
{
    0,
    2,
};

int piProductsSoma[] =
{
    1,
};



int piSubstratesDendrite[] =
{
    3,
    5,
};

int piProductsDendrite[] =
{
    4,
};


struct ch3_reaction rxn[] =
{
    //m soma

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

	sizeof(piSubstratesSoma) / sizeof(int),

	//m indexes of substrates

	piSubstratesSoma,

	//m number of end products

	sizeof(piProductsSoma) / sizeof(int),

	//m indexes of end product

	piProductsSoma,

	//m backward rate

	0.5,

	0.0,

	//m forward rate

	1e2,

	0.0,

    },

    //m dendrite

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

	sizeof(piSubstratesDendrite) / sizeof(int),

	//m indexes of substrates

	piSubstratesDendrite,

	//m number of end products

	sizeof(piProductsDendrite) / sizeof(int),

	//m indexes of end product

	piProductsDendrite,

	//m backward rate

	0.5,

	0.0,

	//m forward rate

	1e2,

	0.0,

    },
};


struct ch3_diffusion diff[] =
{
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

	    sizeof(struct ch3_diffusion),

#endif

	},

	//m diffusion constant

	6e-9,

	//m two attached pools

	&ca[0],

	&ca[3],

	//m geometrical definitions: first length and area

	0.0002,

	5.0265440000000004e-07,

	//m geometrical definitions: second length and area

	0.0002,

	1.2566360000000001e-07,

	//m two fluxes in opposite direction

	0.0,

	0.0,

	//m to be removed, should be transparent: units

	1e-3,   /* 1 for moles, 1e-3 for mmoles, 1e-6 for umoles */

    },

};


struct simobj_Chemesis3 ch3 =
{
    /// name of this object

    /// \note whether the name of a chemesis3 solver is a system wide
    /// id depends on the environment, chemesis3 does not (and cannot)
    /// enforce it.

    "cal2",

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

    //m minumum concentration level

    0.0,

    //m all pools

    sizeof(ca) / sizeof(ca[0]),

    ca,

    //m all reactions

    sizeof(rxn) / sizeof(rxn[0]),

    rxn,

    //m all diffusion elements

    sizeof(diff) / sizeof(diff[0]),

    diff,

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

    pog = OutputGeneratorNew("/tmp/output_cal2");

    OutputGeneratorInitiate(pog);

//d prepare output of concentration

#define CHEMESIS3_TEST_INITIATE \
    double *pdConcentration1 = Chemesis3AddressVariable(pch3, 2, "concentration"); \
    OutputGeneratorAddVariable(pog, "concentration", pdConcentration1);	\
    double *pdConcentration3 = Chemesis3AddressVariable(pch3, 4, "concentration"); \
    OutputGeneratorAddVariable(pog, "concentration", pdConcentration3);	\
    double *pdConcentration4 = Chemesis3AddressVariable(pch3, 6, "concentration"); \
    OutputGeneratorAddVariable(pog, "concentration", pdConcentration4);	\
    double *pdConcentration6 = Chemesis3AddressVariable(pch3, 8, "concentration"); \
    OutputGeneratorAddVariable(pog, "concentration", pdConcentration6);

//d generate output of concentration

#define CHEMESIS3_TEST_OUTPUT \
    OutputGeneratorAnnotatedStep(pog, sprintf(pcStep, "%g", dSimulationTime) ? pcStep : "sprintf() failed")

    //- do the simulation

    simulate(argc,argv);

    //- finish the simulation output

    OutputGeneratorFinish(pog);

    //- add the simulation output to the program output

    WriteOutput("/tmp/output_cal2");

    //- return result

    return(iResult);
}


#define main(argc,argv) simulate(argc,argv)

//t this prototype can give warning and perhaps errors.

int main(int argc, char *argv[]);


#include "main.c"


