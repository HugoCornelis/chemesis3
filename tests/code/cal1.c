

#include <stdlib.h>

#include "../../chemesis3/chemesis3.h"

#include <experiment/output.h>


struct ch3_pool somaCa =
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

    //m initial concentration

    0.0,

    //m current concentration

    0.0,

    //m compartment volume as calculated by the model container

    0.0,

    //m to be removed, should be transparent

    1.0,

    //m number of entities

    0.0,

    //m for conserve pool

    0,

    0.0,

    0.0,

};


struct ch3_pool somaCabuf =
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

    //m initial concentration

    0.0,

    //m current concentration

    0.0,

    //m compartment volume as calculated by the model container

    0.0,

    //m to be removed, should be transparent

    1.0,

    //m number of entities

    0.0,

    //m for conserve pool

    0,

    0.0,

    0.0,

};


struct ch3_pool somabuf =
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

    //m initial concentration

    0.0,

    //m current concentration

    0.0,

    //m compartment volume as calculated by the model container

    0.0,

    //m to be removed, should be transparent

    1.0,

    //m number of entities

    0.0,

    //m for conserve pool

    0,

    0.0,

    0.0,

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

    0,

    //m indexes of substrates

    NULL,

    //m number of end products

    0,

    //m indexes of end product

    NULL,

    //m backward rate

    0.0,

    0.0,

    //m forward rate

    0.0,

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

    0,

    NULL,

    //m all reactions

    0,

    NULL,

};



#include "main.c"


