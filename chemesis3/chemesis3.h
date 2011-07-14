//
// Chemesis3: Kinetic reaction and biochemical reaction pathways for G-3.
//


#ifndef CHEMESIS3_CHEMESIS3_H
#define CHEMESIS3_CHEMESIS3_H


#include <heccer/des.h>


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

    //m and how they are used, flags for each attached reaction

    int *piReactionFlags;

    //m indexes of attached pools

    int iPools;

    int *piPools;

    int *piPoolsFlags;

    //m indexes of attached diffusion elements

    int iDiffusions;

    int *piDiffusions;

    int *piDiffusionsFlags;

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


struct ch3_diffusion
{
    /// administrative overhead

    struct ch3_MathComponent mc;

    //m diffusion constant

    double dDiffusionConstant;

    //m two attached pools

    struct ch3_pool *ppool1;

    struct ch3_pool *ppool2;

    //m geometrical definitions: first length and area

    double dLength1;

    double dArea1;

    //m geometrical definitions: second length and area

    double dLength2;

    double dArea2;

    //m two fluxes in opposite direction

    double dFlux1;

    double dFlux2;

    //m to be removed, should be transparent: units

    double dUnits;   /* 1 for moles, 1e-3 for mmoles, 1e-6 for umoles */

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

    /// serial range covered by this solver

    int iSerialStart;

    int iSerialEnd;

    /// options

    struct Chemesis3Options c3o;

    //m current simulation time

    double dTime;

    //m time step

    double dStep;

    /// identification service : translates serials to math components.

    /// \note so to use this feature: define your translation service, and
    /// \note set it during the construction of your heccer.

    /// \note wouldn't be surprised that I need several layers of services,
    /// \note will see if that has repercussion at this low level or not.
    ///
    /// \note for the moment we have a function layer, which is fixed, and
    /// \note a data layer, which is opaque.  The function layer defines the
    /// \note real interface.

    struct Chemesis3TranslationService *pcts;

    /// event distribution service: given an event, distributes it over the targets

    /// \note so to use this feature: define your event distribution service, and
    /// \note set it during the construction of your heccer.

    /// \note wouldn't be surprised that I need several layers of services,
    /// \note will see if that has repercussion at this low level or not.
    ///
    /// \note for the moment we have a function layer, which is fixed, and
    /// \note a data layer, which is opaque.  The function layer defines the
    /// \note real interface.

    struct EventDistributor *ped;

    /// event reception service: receive an event, and queue till it fires

    /// \note so to use this feature: define your event reception service, and
    /// \note set it during the construction of your heccer.

    /// \note wouldn't be surprised that I need several layers of services,
    /// \note will see if that has repercussion at this low level or not.
    ///
    /// \note for the moment we have a function layer, which is fixed, and
    /// \note a data layer, which is opaque.  The function layer defines the
    /// \note real interface.

    struct EventQueuer *peq;

    //m minimum concentration level

    double dConcentrationMinimum;

    //m all pools

    int iPools;

    struct ch3_pool *ppool;

    //m all reactions

    int iReactions;

    struct ch3_reaction *preaction;

    //m all diffusion elements

    int iDiffusions;

    struct ch3_diffusion *pdiffusion;

    //m all aggregators: derived variables not directly available from a model's viewpoint

    int iAggregators;

    double *pdAggregators;
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

int Chemesis3SingleStepDiffusions(struct simobj_Chemesis3 *pch3);

int Chemesis3SingleStepPools(struct simobj_Chemesis3 *pch3);

int Chemesis3SingleStepReactions(struct simobj_Chemesis3 *pch3);


#endif


