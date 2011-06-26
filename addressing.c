

#include <string.h>


#include "chemesis3/addressing.h"


/// 
/// \arg pch3 a chemesis3.
/// \arg iSerial identification number.
/// \arg pcType name of requested variable.
/// 
/// \return double *
/// 
///	address of the aggregator, NULL for failure.
/// 
/// \brief Get the address of an aggregator.
/// 

double *
Chemesis3AddressAggregator
(struct simobj_Chemesis3 *pch3, int iSerial, char *pcType)
{
    //- set default result: not found

    double *pdResult = NULL;

    //- process as an aggregator variable

    if (strncasecmp(pcType, "aggregator", strlen("aggregator")) == 0)
    {
	//- find the requested index

	int iIndex = -1;

	int iAssigned = sscanf(pcType, "aggregator[%i]", &iIndex);

	if (iAssigned == 1)
	{
	    if (iIndex < pch3->iAggregators)
	    {
		//- set result

		pdResult = &pch3->pdAggregators[iIndex];
	    }
	    else
	    {
		Chemesis3Error
		    (pch3,
		     "Chemesis3AddressAggregator()",
		     "aggregator index of %s is out of range (internal serial %i)",
		     pcType,
		     iSerial);
	    }
	}
	else
	{
	    Chemesis3Error
		(pch3,
		 "Chemesis3AddressAggregator()",
		 "invalid aggregator %s (internal serial %i)",
		 pcType,
		 iSerial);
	}
    }

    //- return resulting address if variable was found

    return(pdResult);
}


/// 
/// \arg pch3 a chemesis3.
/// \arg iSerial serial of pool.
/// \arg pcType name of requested variable.
/// 
/// \return double *
/// 
///	pointer to the requested field, NULL for failure.
/// 
/// \brief Find the simulation sequence of a given variable.
/// 

double *
Chemesis3AddressPoolVariable
(struct simobj_Chemesis3 *pch3, int iSerial, char *pcType)
{
    //- set default result: not found

    double *pdResult = NULL;

    //- loop through all pools

    struct ch3_pool *ppool = NULL;

    int iPool;

    for (iPool = 0 ; iPool < pch3->iPools ; iPool++)
    {
	//- if serials match

	if (pch3->ppool[iPool].mc.iSerial == iSerial)
	{
	    //- set reaction to get result from

	    ppool = &pch3->ppool[iPool];
	}
    }

    //- if pool was found

    if (ppool)
    {
	//- set result for forward_rate

	if (strcasecmp(pcType, "concentration") == 0)
	{
	    pdResult = &ppool->dConcentration;
	}

	//- set result for backward_rate

	else if (strcasecmp(pcType, "quantity") == 0)
	{
	    pdResult = &ppool->dQuantity;
	}
    }

    //- return result

    return(pdResult);
}


/// 
/// \arg pch3 a chemesis3.
/// \arg iSerial serial of reaction.
/// \arg pcType name of requested variable.
/// 
/// \return double *
/// 
///	pointer to the requested field, NULL for failure.
/// 
/// \brief Find the simulation sequence of a given variable.
/// 

double *
Chemesis3AddressReactionVariable
(struct simobj_Chemesis3 *pch3, int iSerial, char *pcType)
{
    //- set default result: not found

    double *pdResult = NULL;

    //- loop through all reactions

    struct ch3_reaction *preaction = NULL;

    int iReaction;

    for (iReaction = 0 ; iReaction < pch3->iReactions ; iReaction++)
    {
	//- if serials match

	if (pch3->preaction[iReaction].mc.iSerial == iSerial)
	{
	    //- set reaction to get result from

	    preaction = &pch3->preaction[iReaction];
	}
    }

    //- if reaction was found

    if (preaction)
    {
	//- set result for forward_rate

	if (strcasecmp(pcType, "forward_rate") == 0)
	{
	    pdResult = &preaction->dForwardSolved;
	}

	//- set result for backward_rate

	else if (strcasecmp(pcType, "backward_rate") == 0)
	{
	    pdResult = &preaction->dBackwardSolved;
	}
    }

    //- return result

    return(pdResult);
}


/// 
/// \arg pch3 a chemesis3 solver.
/// \arg iSerial identification number.
/// \arg pcType name of requested variable.
/// 
/// \return double *
/// 
///	pointer to the requested field, NULL for failure.
/// 
/// \brief Find the simulation sequence of a given variable.
///
/// \details 
/// 
///	In all cases, as of the moment of writing, the pointer is a
///	pointer to a double.
/// 

double *
Chemesis3AddressVariable
(struct simobj_Chemesis3 *pch3, int iSerial, char *pcType)
#ifdef CHEMESIS3_SOURCE_NEUROSPACES
{
    //- set default result : not found

    double *pdResult = NULL;

    if (pch3->iErrorCount)
    {
	return(NULL);
    }

    //- convert serial to chemesis3 space

    iSerial = ADDRESSING_NEUROSPACES_2_CHEMESIS3(iSerial);

    //- if this is the serial of the model itself

    if (iSerial == pch3->iSerialStart)
    {
	//- address as an aggregator

	pdResult = Chemesis3AddressAggregator(pch3, iSerial, pcType);

	return(pdResult);
    }

    //- if serial not within range

    if (iSerial < pch3->iSerialStart
	|| iSerial > pch3->iSerialEnd)
    {
	//- return failure

	return(NULL);
    }

    //- convert the serial to an intermediary index

/*     int iIntermediary = Chemesis3AddressSerial2Intermediary(pch3, iSerial, pcType); */

    int iIntermediary = iSerial;

    if (iIntermediary != -1)
    {
	//- for reaction addressables

	if (strcasecmp(pcType, "forward_rate") == 0
	    || strcasecmp(pcType, "backward_rate") == 0)
	{
	    pdResult = Chemesis3AddressReactionVariable(pch3, iIntermediary, pcType);
	}
	else
	{
	    pdResult = Chemesis3AddressPoolVariable(pch3, iIntermediary, pcType);
	}
    }
    else
    {
	/// \note this cannot be, internal error

	Chemesis3Error
	    (pch3,
	     "Chemesis3AddressVariable()",
	     "trying to address something that should exist, but cannot find it (internal serial %i)",
	     iSerial);

	//- return error

	return(NULL);
    }

    //- return result

    return(pdResult);
}
#else
{
    return(NULL);
}
#endif



