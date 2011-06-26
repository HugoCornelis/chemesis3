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


struct ch3_pool
{
    //m indexes of attached reactions

    int iReactions;

    int *piReactions;

    //m initial concentration

    double dConcentrationInit;

    //m current concentration

    double dConcentration;

    //m compartment volume as calculated by the model container

    double dVolume;

    //m to be removed, should be transparent

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


struct simobj_Chemesis3
{
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


int Chemesis3Initiate(struct simobj_Chemesis3 *pch3);

int Chemesis3SingleStep(struct simobj_Chemesis3 *pch3);

int Chemesis3SingleStepPools(struct simobj_Chemesis3 *pch3);

int Chemesis3SingleStepReactions(struct simobj_Chemesis3 *pch3);


#endif


