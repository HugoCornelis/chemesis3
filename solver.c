#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


#include "chemesis3/chemesis3.h"

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>


static
double IntegrateMethod
(int method, void *pv, double state, double A, double B, double dt, char *name);

static double Runge_Kutta(double y, double A, double B, double dt);


/// 
/// \arg pch3 a chemesis3 solver.
/// \arg dTime current time.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Call Chemesis3SingleStep() until dTime.
/// 

int Chemesis3Advance(struct simobj_Chemesis3 *pch3, double dTime)
{
    //- check for errors

    if (pch3->iErrorCount)
    {
	return(FALSE);
    }

    //- set default result : ok

    int iResult = TRUE;

    //- while not reached simulation time

    while (pch3->dTime < dTime)
    {
	//- do a single step

	iResult = iResult && Chemesis3SingleStep(pch3);

	/// \note perhaps should move the advance of the local time to this
	/// \note point ?  Would allow to remove this test ...
	/// \note I don't care for the moment.

	if (iResult == FALSE)
	{
	    return(iResult);
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pch3 a chemesis3 solver.
/// 
/// \return int
/// 
///	Model can be compiled.
/// 
/// \brief Can the model be compiled, given the current options ?
/// 

int Chemesis3CanCompile(struct simobj_Chemesis3 *pch3)
{
    //- check for errors

    if (pch3->iErrorCount)
    {
	return(FALSE);
    }

    //- set default result : ok

    int iResult = TRUE;

#define MINIMAL_TIME_STEP 1e-30

    if (pch3->dStep < MINIMAL_TIME_STEP)
    {
	Chemesis3Error
	    (pch3,
	     NULL,
	     "illegal time step (smallest is %g), cannot compile\n", MINIMAL_TIME_STEP);

	return(FALSE);
    }

    // \todo it is maybe better to diagnose this as a warning

    if (pch3->iPools == 0
	|| pch3->iReactions == 0)
    {
	Chemesis3Error
	    (pch3,
	     NULL,
	     "no pools or reactions found, cannot compile this model\n");

	return(FALSE);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pch3 a chemesis3 solver.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Analyze the model, build indices for optimization.
///
/// \details
/// 
///	Internally, Chemesis3 addresses mechanisms using their
///	compartment's schedule number.  So the minimum degree
///	algorithm must run first before the mechanisms can be
///	compiled.
/// 
/// \note 
/// 
///	This function can be used for testing internals of a chemesis3
///	solver, just be sure to provide a consistent intermediary
///	image.
/// 

int Chemesis3CompileP2(struct simobj_Chemesis3 *pch3)
{
    //- check for errors

    if (pch3->iErrorCount)
    {
	return(FALSE);
    }

    //- set default result : ok

    int iResult = TRUE;

    //- first sanity

    if (!Chemesis3CanCompile(pch3))
    {
	iResult = FALSE;
    }

/*     //- apply options to the model */

/*     iResult = iResult && Chemesis3ApplyOptions(pch3); */

    //- return result

    return(iResult);
}


/// 
/// \arg pch3 a chemesis3 solver.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Third phase of compilation.
///
/// \note 
/// 
///	This function can be used for testing internals of a chemesis3
///	solver, just be sure to provide a consistent intermediary
///	image.
/// 

int Chemesis3CompileP3(struct simobj_Chemesis3 *pch3)
{
    //- check for errors

    if (pch3->iErrorCount)
    {
	return(FALSE);
    }

    //- set default result : ok

    int iResult = TRUE;

/*     //- rearrange table values for cache line loading */

/*     iResult = iResult && Chemesis3TablesRearrange(pch3); */

/*     //- allocate memory for aggregate results */

/*     iResult = iResult && Chemesis3AggregatorsCompile(pch3); */

    //- return result

    return(iResult);
}


/// 
/// \arg pch3 a chemesis3 solver.
/// \arg pcContext context of error.
/// \arg pcError error string.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Register an error, print to stderr.
/// 

int Chemesis3Error(struct simobj_Chemesis3 *pch3, char *pcContext, char *pcError, ...)
{
    //- set default result: ok

    int iResult = 1;

    //- give diagnostics

    //- print to stderr

    fprintf(stderr, "The Genesis of this Chemesis: ");

/*     if (pcContext) */
/*     { */
/* 	fprintf */
/* 	    (stderr, */
/* 	     "%s: *** Error: ", */
/* 	     pcContext); */
/*     } */

    //v stdargs list

    va_list vaList;

    //- get start of stdargs

    va_start(vaList, pcError);

    //- give diagnostics

    vfprintf(stderr, pcError, vaList);

    fprintf(stderr, "\n");

    //- end stdargs

    va_end(vaList);

    //- negate status: this chemesis3 solver is in error

    pch3->iStatus = - pch3->iStatus;

    //- increment total error count

    pch3->iErrorCount++;

    //- return result

    return(iResult);
}


/// 
/// \return char *
/// 
///	Version identifier.
/// 
/// \brief Obtain version identifier.
/// 

char * Chemesis3GetVersion(void)
{
    // $Format: "    static char *pcVersion=\"${package}-${label}\";"$
    static char *pcVersion="chemesis3-alpha";

    return(pcVersion);
}


/// 
/// \arg pch3 a chemesis3 solver.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Fill the data arrays with initial values.
/// 

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


struct simobj_Chemesis3 * Chemesis3NewP2(char *pcName, struct simobj_Chemesis3 *pch3)
{
    //- set default result: from the given object

    struct simobj_Chemesis3 *pch3Result = pch3;

    //- return result

    return(pch3Result);
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

	for (iReaction = 0 ; iReaction < ppool->iReactions ; iReaction++)
	{
	    //- retrieve the index of this reaction

	    int iIndex = ppool->piReactions[iReaction];

	    //- get forward and backward rates of this reaction

	    struct ch3_reaction *preaction = &pch3->preaction[iIndex];

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

	    if (ppool->dConcentration < pch3->dConcentrationMinimum)
	    {
		ppool->dConcentration = pch3->dConcentrationMinimum;
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
/*     case GEAR_INT: */
/* 	/* */
/* 	** Gear 2nd order */
/* 	* */
/* 	/* Attach buffer below segment, instead of to parent (BPG 15-5-91) */
/* 	   result = Gear(segment->parent,&(segment->child),* */
/* 	result = Gear(segment, */
/* 		      state,A,B,dt,name); */
/* 	break; */
/*     case AB2_INT: */
/* 	/* */
/* 	** Adams-Bashforth 2 step */
/* 	* */
/* 	/* Attach buffer below segment, instead of to parent (BPG 15-5-91) */
/* 	   result = AB2(segment->parent,&(segment->child),* */
/* 	result = AB2(segment, state,A - state*B,dt, name); */
/* 	break; */
/*     case AB3_INT: */
/* 	/* */
/* 	** Adams-Bashforth 3 step */
/* 	* */
/* 	/* Attach buffer below segment, instead of to parent (BPG 15-5-91) */
/* 	   result = AB3(segment->parent,&(segment->child),* */
/* 	result = AB3(segment, state,A - state*B,dt, name); */
/* 	break; */
    case TRAPEZOIDAL_INT:
	/*
	** Trapezoidal
	*/
#define Trapezoid(y,A,B,dt) \
	(((y)*(1-(dt)*(B)/2.0)+(dt)*(A))/(1+(dt)*(B)/2.0))

	result = Trapezoid(state,A,B,dt);
	break;
/* 	/* Why not include the 4 and 5 step methods ? (BPG 22-5-91) * */
/*     case AB4_INT: */
/* 	/* */
/* 	** Adams-Bashforth 4 step */
/* 	* */
/* 	/* Attach buffer below segment, instead of to parent (BPG 15-5-91) */
/* 	   result = AB4(segment->parent,&(segment->child),* */
/* 	result = AB4(segment, state,A - state*B,dt, name); */
/* 	break; */
/*     case AB5_INT: */
/* 	/* */
/* 	** Adams-Bashforth 5 step */
/* 	* */
/* 	/* Attach buffer below segment, instead of to parent (BPG 15-5-91) */
/* 	   result = AB5(segment->parent,&(segment->child),* */
/* 	result = AB5(segment, state,A - state*B,dt, name); */
/* 	break; */
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
/* 	/* A predictor-corrector method (BPG 22-5-91) * */
/*     case EPC_INT: */
/* 	/* */
/* 	** Euler predictor - modified Euler corrector */
/* 	(from Parnas and Segev, J.Physiol. (1979) 295:323-343) */
/* 	* */
/* 	result = Euler_Predictor_Corrector(state,A,B,dt); */
/* 	break; */
/*     default : */
/* 	/*  */
/* 	** default to good old Exp Euler */
/* 	* */
/* 	D = exp(-B*dt); */
/* 	result = state*D + (A/B)*(1-D); */
/* 	break; */
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
