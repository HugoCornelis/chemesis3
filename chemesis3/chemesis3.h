//
// Chemesis3: Kinetic reaction and biochemical reaction pathways for G-3.
//


#ifndef CHEMESIS3_CHEMESIS3_H
#define CHEMESIS3_CHEMESIS3_H

#ifndef AVOGADRO
#define AVOGADRO 6.023e23         /* units are molecules per mole */
#endif


/*
** pre-defined integration methods
*/
#define RK_INT			-102
#define TRAPEZOIDAL_INT		-101
#define GEAR_INT		-100
#define EPC_INT			-2
#define FEULER_INT		-1
#define EEULER_INT		0
#define AB2_INT			2
#define AB3_INT			3
#define AB4_INT			4
#define AB5_INT			5
#define BEULER_INT		10
#define CRANK_INT		11


#include "mathcomponent.h"


struct ch3_pool
{
    /// administrative overhead

    struct ch3_MathComponent mc;

    //m indexes of attached reactions

    int iReactions;

    int *piReactions;

    //m initial concentration

    double dConcentrationInit;

    //m current concentration

    double dConcentration;

    //m compartment volume as calculated by the model container

    double dVolume;

    //m to be removed, should be transparent: units

    double dUnits;

    //m number of entities

    double dQuantity;

    //m for conserve pool

    int iConserve;

    double dQTotal;

    double dCTotal;

};


struct ch3_reaction
{
    /// administrative overhead

    struct ch3_MathComponent mc;

    //m number of substrates

    int iSubstrates;

    //m indexes of substrates

    int *piSubstrates;

    //m number of end products

    int iProducts;

    //m indexes of end product

    int *piProducts;

    //m backward rate

    double dBackwardRate;

    double dBackwardSolved;

    //m forward rate

    double dForwardRate;

    double dForwardSolved;

};


/// \struct global options

struct Chemesis3Options
{
    /// global options and operation mode.

    int iOptions;
};


struct simobj_Chemesis3
{
    /// name of this object

    /// \note whether the name of a chemesis3 solver is a system wide
    /// id depends on the environment, chemesis3 does not (and cannot)
    /// enforce it.

    char *pcName;

    /// status : reflects phases of compilation.

    int iStatus;

    int iErrorCount;

    /// options

    struct Chemesis3Options c3o;

    //m current simulation time

    double dTime;

    //m time step

    double dStep;

    //m minumum concentration level

    double dConcentrationMinimum;

    //m all pools

    int iPools;

    struct ch3_pool *ppool;

    //m all reactions

    int iReactions;

    struct ch3_reaction *preaction;

};


/// \def brandnew allocated, nothing done

#define CHEMESIS3_STATUS_PHASE_0		0

/// \def correctly initialized

#define CHEMESIS3_STATUS_PHASE_1		10

/// \def intermediary has been built

#define CHEMESIS3_STATUS_PHASE_2		20

/// \def byte has been compiled

#define CHEMESIS3_STATUS_PHASE_3		30

/// \def initial values have been put in place

#define CHEMESIS3_STATUS_PHASE_4		40

/// \def simulation has progressed

#define CHEMESIS3_STATUS_PHASE_5		50


int Chemesis3Advance(struct simobj_Chemesis3 *pch3, double dTime);

int Chemesis3CanCompile(struct simobj_Chemesis3 *pch3);

int Chemesis3CompileP2(struct simobj_Chemesis3 *pch3);

int Chemesis3CompileP3(struct simobj_Chemesis3 *pch3);

int Chemesis3Error(struct simobj_Chemesis3 *pch3, char *pcContext, char *pcError, ...);

char * Chemesis3GetVersion(void);

int Chemesis3Initiate(struct simobj_Chemesis3 *pch3);

struct simobj_Chemesis3 * Chemesis3NewP2(char *pcName, struct simobj_Chemesis3 *pch3);

int Chemesis3SingleStep(struct simobj_Chemesis3 *pch3);

int Chemesis3SingleStepPools(struct simobj_Chemesis3 *pch3);

int Chemesis3SingleStepReactions(struct simobj_Chemesis3 *pch3);


#ifdef CHEMESIS3_SOURCE_NEUROSPACES

/// \def number of function allowed per symbol as a shift operand

#define NEUROSPACES_2_CHEMESIS3_MAX_FUNCTIONS 2

#define ADDRESSING_NEUROSPACES_2_CHEMESIS3(iNeuro) ((iNeuro) << NEUROSPACES_2_CHEMESIS3_MAX_FUNCTIONS)

#define ADDRESSING_CHEMESIS3_2_NEUROSPACES(iChemesis3) ((iChemesis3) >> NEUROSPACES_2_CHEMESIS3_MAX_FUNCTIONS)

/// \todo should add defines for assigning function IDs.
/// \todo note that this would be solved automatically if the
/// \todo neurospaces model_container would do full traversals.


double *
Chemesis3AddressAggregator
(struct simobj_Chemesis3 *pch3, int iSerial, char *pcType);

char *
Chemesis3AddressableSet
(struct simobj_Chemesis3 *pch3, int iSerial, char *pcType, double dValue);

double *
Chemesis3AddressCompartmentVariable
(struct simobj_Chemesis3 *pch3, int iIntermediary, char *pcField);

double *
Chemesis3AddressMechanismVariable
(struct simobj_Chemesis3 *pch3, int iIndex, char *pcField);

int
Chemesis3AddressTableIndex
(struct simobj_Chemesis3 *pch3, int iSerial, char *pcField);

double *
Chemesis3AddressVariable
(struct simobj_Chemesis3 *pch3, int iSerial, char *pcType);

#else

double *
Chemesis3AddressVariable
(struct simobj_Chemesis3 *pch3, int iSerial, char *pcType);

#endif


#endif


