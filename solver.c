#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif




struct ch3_pool
{
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
    //- current simulation time

    double dTime;

    //- time step

    double dStep;

    //- all pools

    int iPools;

    struct ch3_pool *ppool;

    //- all reactions

    int iReactions;

    struct ch3_reaction *preaction;

};


int Chemesis3Initiate(struct simobj_Chemesis3 *pch3)
{
    //- set default result : ok

    int iResult = TRUE;

    //- reset the time

    pch3->dTime = 0.0;

    //- initiate pools

    int i;

    for (i = 0 ; i < pch3->iPools; i++)
    {
	pch3->ppool[i].dConcentration = pch3->ppool[i].dConcentrationInit;

	pch3->ppool[i].dQuantity
	    = (pch3->ppool[i].dConcentration
	       * pch3->ppool[i].dVolume
	       * AVOGADRO
	       * pch3->ppool[i].dUnits);

	if (pch3->ppool[i].iConserve)
	{
	    pch3->ppool[i].dQTotal
		= (pch3->ppool[i].dCTotal
		   * pch3->ppool[i].dVolume
		   * AVOGADRO
		   * pch3->ppool[i].dUnits);
	}
    }

    //- initiate reaction rates

    //- no need to do this, correct?

    //- return result

    return(iResult);
}


int Chemesis3SingleStep(struct simobj_Chemesis3 *pch3)
{
    //- set default result : ok

    int iResult = TRUE;

    //- update the simulation time

    pch3->dTime += pch3->dStep;

    //- simulate the reactions

    iResult = iResult && Chemesis3SingleStepReactions(pch3);

    //- simulate the pools

    iResult = iResult && Chemesis3SingleStepPools(pch3);

    //- return result

    return(iResult);
}


int Chemesis3SingleStepReactions(struct simobj_Chemesis3 *pch3)
{
    //- set default result: ok

    int iResult = TRUE;

    //- loop through all reactions

    int i;

    for (i = 0 ; i < pch3->iReactions ; i++)
    {
	//- reference the current reaction

	struct ch3_reaction *preaction = &pch3->preaction[i];

	//- set starting value of backward and forward rates

	preaction->dBackwardSolved = preaction->dBackwardRate;
	preaction->dForwardSolved = preaction->dForwardRate;

	//- loop over all substrates

	int iSubstrate;

	for (iSubstrate = 0; iSubstrate < preaction->iSubstrates ; iSubstrate++)
	{
	    //- incorporate the substrate concentration

	    preaction->dForwardSolved *= pch3->ppool[iSubstrate].dConcentration;
	}

	//- loop over all products

	int iProduct;

	for (iProduct = 0 ; iProduct < preaction->iProducts ; iProduct++)
	{
	    //- incorporate the product concentration

	    preaction->dBackwardSolved *= pch3->ppool[iProduct].dConcentration;
	}
    }

    //- return result

    return(iResult);
}


