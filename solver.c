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
    //- set default result: ok

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


int Chemesis3SingleStepPools(struct simobj_Chemesis3 *pch3)
{
    //- set default result: ok

    int iResult = TRUE;

    //- loop over all pools

    int iPool;

    for (iPool = 0 ; iPool < pch3->iPools ; iPool++)
    {
	struct ch3_pool *ppool = &pch3->ppool[iPool];

	//- initialize

	double dA = 0;

	double dAConc = 0;

	double dB = 0;

	double dAMoles = 0;

	//- loop over all reactions attached to this pool

	int iReaction;

	for (int iReaction = 0 ; iReaction < ppool->iReactions ; iReaction++)
	{
	    //- retrieve the index of this reaction

	    int iIndex = ppool->piReactions[iReaction];

	    //- get forward and backward rates of this reaction

	    struct ch3_reaction *preaction = pch3->preaction[iIndex];

	    double dForwardSolved = preaction->dForwardSolved;

	    double dBackwardSolved = preaction->dBackwardSolved;

	    //- connect the pool equation with the reaction equation

	    dAConc += dForwardSolved;

	    if (ppool->dConcentration != 0)
	    {
		dB += dBackwardSolved / ppool->dConcentration;
	    }

	    //- integrate to the next time step

	    dA = dAMoles / ppool->dVolume / (AVOGADRO * ppool->dUnits) + dAConc;

	    ppool->dConcentration
		= IntegrateMethod
		  (
		      (dB < 1.0e-10
		       ? FEULER_INT
		       : EEULER_INT),
		      /* ppool */ NULL,
		      ppool->dConcentration,
		      dA,
		      dB,
		      pch3->dStep,
		      "concentration");

	    //- check for parameterized minimum concentration boundary

	    if (ppool->dConcentration < ppool->dMinimum)
	    {
		ppool->dConcentration = ppool->dMinimum;
	    }

	    //- calculate the total number of ions in the pool

	    ppool->dQuantity = ppool->dConcentration * ppool->dVolume * AVOGADRO * ppool->dUnits;

	}
    }

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


static
double IntegrateMethod
(int method, void *pv, double state, double A, double B, double dt, char *name)
{
    double D;
    double result;

    switch(method){
    case EEULER_INT:
	/*
	** the default is the exponential integration form
	*/
	D = exp(-B*dt);
	result = state*D + (A/B)*(1-D);
	break;
    case GEAR_INT:
	/*
	** Gear 2nd order
	*/
	/* Attach buffer below segment, instead of to parent (BPG 15-5-91)
	   result = Gear(segment->parent,&(segment->child),*/
	result = Gear(segment,
		      state,A,B,dt,name);
	break;
    case AB2_INT:
	/*
	** Adams-Bashforth 2 step
	*/
	/* Attach buffer below segment, instead of to parent (BPG 15-5-91)
	   result = AB2(segment->parent,&(segment->child),*/
	result = AB2(segment, state,A - state*B,dt, name);
	break;
    case AB3_INT:
	/*
	** Adams-Bashforth 3 step
	*/
	/* Attach buffer below segment, instead of to parent (BPG 15-5-91)
	   result = AB3(segment->parent,&(segment->child),*/
	result = AB3(segment, state,A - state*B,dt, name);
	break;
    case TRAPEZOIDAL_INT:
	/*
	** Trapezoidal
	*/
#define Trapezoid(y,A,B,dt) \
	(((y)*(1-(dt)*(B)/2.0)+(dt)*(A))/(1+(dt)*(B)/2.0))

	result = Trapezoid(state,A,B,dt);
	break;
	/* Why not include the 4 and 5 step methods ? (BPG 22-5-91) */
    case AB4_INT:
	/*
	** Adams-Bashforth 4 step
	*/
	/* Attach buffer below segment, instead of to parent (BPG 15-5-91)
	   result = AB4(segment->parent,&(segment->child),*/
	result = AB4(segment, state,A - state*B,dt, name);
	break;
    case AB5_INT:
	/*
	** Adams-Bashforth 5 step
	*/
	/* Attach buffer below segment, instead of to parent (BPG 15-5-91)
	   result = AB5(segment->parent,&(segment->child),*/
	result = AB5(segment, state,A - state*B,dt, name);
	break;
	/* The oldest and greatest ! (BPG 24-5-91) */
    case RK_INT:
	/*
	** Runge-Kutta 4 step
	*/
	result = Runge_Kutta(state,A,B,dt);
	break;
    case FEULER_INT:
	/*
	** Euler: a definite must
	*/
#define Euler(y,dy,dt) 		((y) + (dy)*(dt))
	result = Euler(state,A - state*B,dt);
	break;
	/* A predictor-corrector method (BPG 22-5-91) */
    case EPC_INT:
	/*
	** Euler predictor - modified Euler corrector
	(from Parnas and Segev, J.Physiol. (1979) 295:323-343)
	*/
	result = Euler_Predictor_Corrector(state,A,B,dt);
	break;
    default :
	/* 
	** default to good old Exp Euler
	*/
	D = exp(-B*dt);
	result = state*D + (A/B)*(1-D);
	break;
    }
    return(result);
}


/* Runge-Kutta 4-step method (BPG 22-5-91) 
*/
static double Runge_Kutta(double y, double A, double B, double dt)
{
    double k1, k2, k3, k4, value;

    k1 = (A - B*y) * dt;
    k2 = (A - B*(y + k1/2)) * dt;
    k3 = (A - B*(y + k2/2)) * dt;
    k4 = (A - B*(y + k3)) * dt;

    value = y + (k1 + 2*k2 + 2*k3 + k4) / 6;

    return(value);

}
