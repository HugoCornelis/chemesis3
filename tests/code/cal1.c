

#include <stdlib.h>

#include "../../chemesis3/chemesis3.h"

#include <experiment/output.h>


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
    0
};

int piSomabufPoolsFlags[] =
{
    0
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

	piSomaCaFlags,

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

	sizeof(piReactions) / sizeof(int),

	piReactions,

	//m and how they are used, flags for each attached reaction

	piSomaCabufFlags,

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

	0,

	NULL,

	//m and how they are used, flags for each attached reaction

	piSomabufFlags,

	//m indexes of attached pools

	1,

	piSomabufPools,

	piSomabufPoolsFlags,

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

	0.0,

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

    3,

    somaCa,

    //m all reactions

    1,

    &somacabufrxn,

};



#include "main.c"

