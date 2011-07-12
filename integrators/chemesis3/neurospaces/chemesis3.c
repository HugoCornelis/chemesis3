

#include <heccer/des.h>

#include <neurospaces/importedfile.h>
#include <neurospaces/parsersupport.h>
#include <neurospaces/pidinstack.h>

#ifdef Chemesis3Connect_with_ppq

#include <neurospaces/projectionquery.h>
#include <neurospaces/solverinfo.h>

#endif


#include "chemesis3/addressing.h"
#include "chemesis3/chemesis3.h"
#include "chemesis3/service.h"
#include "chemesis3/neurospaces/chemesis3.h"


/// 
/// \arg pch3 a chemesis3.
/// \arg ped the event distributor to be used.
/// \arg ppq global projection query.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Connect this chemesis3 to its assigned event distributor.
///
/// \details
/// 
///	 Likely to use indices, initialized with Chemesis3CompileP2().
/// 

int Chemesis3ConnectDistributor(struct simobj_Chemesis3 *pch3, struct EventDistributor *ped, struct SolverRegistry *psr, struct ProjectionQuery *ppq)
{
    //- check for errors

    if (pch3->iErrorCount)
    {
	fprintf(stderr, "*** Error: Chemesis3ConnectDistributor() cannot a chemesis3 with %i errors\n", pch3->iErrorCount);

	return(0);
    }

    //- set default result : ok

    int iResult = 1;

    //- connect this chemesis3 spikegens to the event distributor.

    if (ped)
    {
	if (pch3->ped && pch3->ped != ped)
	{
	    fprintf(stderr, "*** Error: Chemesis3ConnectDistributor() cannot have multiple event distributors per chemesis3\n");
	}
	else
	{
	    pch3->ped = ped;

	    int iRanged = EventDistributorSetSerialRange(ped, pch3->iSerialStart, pch3->iSerialEnd);

	    if (!iRanged)
	    {
		fprintf(stderr, "*** Error: Chemesis3ConnectDistributor() cannot register the serial identifier range in its event distributor\n");
	    }
	}
    }

#ifdef Chemesis3Connect_with_ppq

    // \todo use projection query to loop through all event receivers
    // and, given their serials, fill in the iDiscreteTarget values,
    // using EventQueuerSerial2ConnectionIndex().  The event queuer to
    // be used is given by the CPU core number.

    //- if we got a projection query

    if (ppq)
    {
	//- loop over all connections

	int iConnections = ProjectionQueryCountConnections(ppq);

	//- loop over all event receivers

	int iLastPost = -1;

	//- receiver count

	int iReceiver = -1;

	int i;

	for (i = 0 ; i < iConnections ; i++)
	{
	    struct CachedConnection *pcconn = OrderedConnectionCacheGetEntry(ppq->poccPost, i);

	    //- when we are dealing with a new pre-synaptic source

	    if (iLastPost != pcconn->iPost)
	    {
		//- increment receiver count

		iReceiver++;

		//- register this pre-synaptic serial

		iLastPost = pcconn->iPost;

		//- if this is the correct chemesis3

		struct SolverInfo *psi = SolverRegistryGetForAbsoluteSerial(psr, pcconn->iPost);

		void *pvSolver = psi->pvSolver;

		if (pvSolver == (void *)pch3)
		{
		    //- get chemesis3 variable of iDiscreteTarget in mops, post-synaptic targets in the event queuer matrix

		    double *pdDiscreteTarget = Chemesis3AddressVariable(pch3, iLastPost, "postsyn_targets");

		    if (pdDiscreteTarget)
		    {
			int *piDiscreteTarget = (int *)pdDiscreteTarget;

			//- fill in target index: is receiver count

			*piDiscreteTarget = iReceiver;
		    }
		    else
		    {
			Chemesis3Error
			    (pch3,
			     NULL,
			     "Cannot find synchan target field for synchan with serial %i",
			     iLastPost);
		    }
		}
		else
		{
		    Chemesis3Error
			(pch3,
			 NULL,
			 "Requested this chemesis3 to obtain information about a field solved by another chemesis3 (%s)",
			 psi->pcSolver);
		}
	    }
	}
    }

#endif

    //- return result

    return(iResult);
}


/// 
/// \arg pch3 a chemesis3.
/// \arg peq the event queuer to be used.
/// \arg ppq global projection query.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Connect this chemesis3 to its assigned event distributor.
///
/// \details
/// 
///	 Likely to use indices, initialized with Chemesis3CompileP2().
/// 

int Chemesis3ConnectQueuer(struct simobj_Chemesis3 *pch3, struct EventQueuer *peq, struct SolverRegistry *psr, struct ProjectionQuery *ppq)
{
    //- check for errors

    if (pch3->iErrorCount)
    {
	fprintf(stderr, "*** Error: Chemesis3ConnectQueuer() cannot a chemesis3 with %i errors\n", pch3->iErrorCount);

	return(0);
    }

    //- set default result : ok

    int iResult = 1;

    //- connect this chemesis3 synapses to the event queuer.

    // \todo this will not work when we have one queuer per cpu core.

    if (peq)
    {
	if (pch3->peq && pch3->peq != peq)
	{
	    fprintf(stderr, "*** Error: Chemesis3Connect() cannot have multiple event queuers per chemesis3\n");
	}
	else
	{
	    pch3->peq = peq;
	}
    }

#ifdef Chemesis3Connect_with_ppq

    // \todo use projection query to loop through all event receivers
    // and, given their serials, fill in the iDiscreteTarget values,
    // using EventQueuerSerial2ConnectionIndex().  The event queuer to
    // be used is given by the CPU core number.

    //- if we got a projection query

    if (ppq)
    {
	//- loop over all connections

	int iConnections = ProjectionQueryCountConnections(ppq);

	//- loop over all event receivers

	int iLastPost = -1;

	//- receiver count

	int iReceiver = -1;

	int i;

	for (i = 0 ; i < iConnections ; i++)
	{
	    struct CachedConnection *pcconn = OrderedConnectionCacheGetEntry(ppq->poccPost, i);

	    //- when we are dealing with a new pre-synaptic source

	    if (iLastPost != pcconn->iPost)
	    {
		//- increment receiver count

		iReceiver++;

		//- register this pre-synaptic serial

		iLastPost = pcconn->iPost;

		//- if this is the correct chemesis3

		struct SolverInfo *psi = SolverRegistryGetForAbsoluteSerial(psr, pcconn->iPost);

		void *pvSolver = psi->pvSolver;

		if (pvSolver == (void *)pch3)
		{
		    //- get chemesis3 variable of iDiscreteTarget in mops, post-synaptic targets in the event queuer matrix

		    double *pdDiscreteTarget = Chemesis3AddressVariable(pch3, iLastPost, "postsyn_targets");

		    if (pdDiscreteTarget)
		    {
			int *piDiscreteTarget = (int *)pdDiscreteTarget;

			//- fill in target index: is receiver count

			*piDiscreteTarget = iReceiver;
		    }
		    else
		    {
			Chemesis3Error
			    (pch3,
			     NULL,
			     "Cannot find synchan target field for synchan with serial %i",
			     iLastPost);
		    }
		}
		else
		{
		    Chemesis3Error
			(pch3,
			 NULL,
			 "Requested this chemesis3 to obtain information about a field solved by another chemesis3 (%s)",
			 psi->pcSolver);
		}
	    }
	}
    }

#endif

    //- return result

    return(iResult);
}


/// 
/// \arg pch3 a chemesis3.
/// \arg pvNeurospaces model-container.
/// \arg pcModel model identifier in the model-container.
/// \arg pvEventDistributor event distributor of this chemesis3.
/// \arg pvEventQueuer event queuer of this chemesis3.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Connect this chemesis3 to its assigned event distributor.
///
/// \details
/// 
///	 Likely to use indices, initialized with Chemesis3CompileP2().
/// 

int Chemesis3Construct(struct simobj_Chemesis3 *pch3, void *pvNeurospaces, char *pcModel, void *pvEventDistributor, void *pvEventQueuer)
{
    //- the event_distributor is an event_distributor

    struct EventDistributor *ped = (struct EventDistributor *)pvEventDistributor;

    pch3->ped = ped;

    //- the event_distributor is an event_distributor

    struct EventQueuer *peq = (struct EventQueuer *)pvEventQueuer;

    pch3->peq = peq;

    //- the modeling service is neurospaces

    struct Neurospaces *pneuro = (struct Neurospaces *)pvNeurospaces;

    //- set default result : ok

    int iResult = 1;

    //- register the modelname in the chemesis3

    pch3->pcName = strdup(pcModel);

    //- lookup the model

    struct PidinStack *ppistModel = PidinStackParse(pcModel);

    if (!ppistModel)
    {
	fprintf(stderr, "Chemesis3Construct: cannot parse model name %s\n", pcModel);

	return(FALSE);
    }

    //- allocate the translation service structures

    struct Chemesis3TranslationServiceData *pctsd
	= (struct Chemesis3TranslationServiceData *)calloc(1, sizeof(struct Chemesis3TranslationServiceData));

    struct Chemesis3TranslationService *pcts
	= (struct Chemesis3TranslationService *)calloc(1, sizeof(struct Chemesis3TranslationService));

    pcts->pctsd = pctsd;

    pcts->pctsd->pneuro = pneuro;

    //- allocate pidin stack pointing to root

    struct PidinStack *ppistRoot = PidinStackCalloc();

    if (!ppistRoot)
    {
	fprintf(stderr, "Chemesis3Construct: cannot allocate a root context for %s\n", pcModel);

	return(FALSE);
    }

    PidinStackSetRooted(ppistRoot);

    /// \note gosh, I had to do the same hack when integrating neurospaces
    /// \note with genesis2/hsolve.

    struct ParserContext *pacRoot = pneuro->pacRootContext;

    struct ImportedFile *pifRoot
	= ParserContextGetImportedFile(pacRoot);

    /// \note depending on how the linking is done, there can be multiple
    /// \note instances of neurospaces around.  The following is a hack to
    /// \note enforce the singleton (a bit)

/*     fprintf(stdout, "Chemesis3Construct(): root import is %p\n", ImportedFileGetRootImport()); */

    ImportedFileSetRootImport(pifRoot);

/*     fprintf(stdout, "Chemesis3Construct(): root import is %p\n", ImportedFileGetRootImport()); */

    //- update caches

    struct symtab_HSolveListElement *phsleRoot
	= PidinStackLookupTopSymbol(ppistRoot);

    pctsd->ppistRoot = ppistRoot;

    pctsd->phsleRoot = phsleRoot;

    //- set model

    struct symtab_HSolveListElement *phsleModel
	= PidinStackLookupTopSymbol(ppistModel);

    pctsd->iModel = PidinStackToSerial(ppistModel);

    if (pctsd->iModel == INT_MAX)
    {
	/// \note don't care about memory leak right now, consider this
	/// \note right now as a fatal crash

	fprintf(stderr, "Chemesis3Construct: cannot find model %s\n", pcModel);

	return(FALSE);
    }

    if (!Chemesis3NeurospacesSegments2Compartments(pcts))
    {
	/// \note don't care about memory leak right now, consider this
	/// \note right now as a fatal crash

	fprintf(stderr, "Chemesis3Construct: compartment initialization failed for %s\n", pcModel);

	return(FALSE);
    }

    if (!Chemesis3NeurospacesMechanisms2MathComponents(pcts))
    {
	/// \note don't care about memory leak right now, consider this
	/// \note right now as a fatal crash

	fprintf(stderr, "Chemesis3Construct: mechanism initialization failed for %s\n", pcModel);

	return(FALSE);
    }

    //- set service structures

    pch3->pcts = pcts;

    //- initialize the range of the intermediary, for the addressing
    //- function

    /// \note note: closed interval, would probably be better to use a halve
    /// \note open interval.

    /// \todo Chemesis3Construct() should not touch inter.
    /// \todo move or copy the field iSerialStart to pctsd

    pch3->iSerialStart = ADDRESSING_NEUROSPACES_2_CHEMESIS3(pctsd->iModel);

    pch3->iSerialEnd = ADDRESSING_NEUROSPACES_2_CHEMESIS3(pctsd->iModel + SymbolGetPrincipalNumOfSuccessors(phsleModel));

    //- free allocated data

    PidinStackFree(ppistModel);

    //- return result

    return(iResult);
}


