

#include <stdio.h>
#include <stdlib.h>

#include <neurospaces/pidinstack.h>
#include <neurospaces/treespacetraversal.h>

#include "chemesis3/addressing.h"
#include "chemesis3/neurospaces/chemesis3.h"
#include "chemesis3/service.h"


struct kinetics_info
{
    //m the solver to initialize

    struct simobj_Chemesis3 *pch3;

    //m number of pools found

    int iPools;

    //m number of reactions found

    int iReactions;

    //m number of diffusions found

    int iDiffusions;

};


static
int
solver_counter(struct TreespaceTraversal *ptstr, void *pvUserdata);

static int solver_link(struct simobj_Chemesis3 *pch3);

static
int
solver_processor(struct TreespaceTraversal *ptstr, void *pvUserdata);

static int chemesis3_setup_kinetics(struct simobj_Chemesis3 *pch3, struct Chemesis3TranslationService *pts);



static
int
solver_counter(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get pointer to solver

    struct kinetics_info *pki = (struct kinetics_info *)pvUserdata;

    struct simobj_Chemesis3 *pch3 = pki->pch3;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = (struct symtab_HSolveListElement *)TstrGetActual(ptstr);

    //- count pools

    if (instanceof_pool(phsle))
    {
	pki->iPools++;
    }

    //- count reactions

    if (instanceof_reaction(phsle))
    {
	pki->iReactions++;
    }

    //- count diffusions

    if (instanceof_diffusions(phsle))
    {
	pki->iDiffusions++;
    }

    //- return result

    return(iResult);
}


static int solver_link(struct simobj_Chemesis3 *pch3)
{
    //- set default result : ok

    int iResult = TRUE;

    //- loop over all pools

    int iPool;

    for (iPool = 0 ; iPool < pch3->iPools ; iPool++)
    {
	struct ch3_pool *ppool = &pch3->ppool[iPool];

	//- loop over all reactions attached to this pool

	int iReaction;

	for (iReaction = 0 ; iReaction < ppool->iReactions ; iReaction++)
	{
	    //- retrieve the index of this reaction

	    int iIndex = ppool->piReactions[iReaction];

	    struct ch3_reaction *preactionAttached = &pch3->preaction[iIndex];

	}

	//- loop over all pools attached to this pool

	int iPoolAttached;

	for (iPoolAttached = 0 ; iPoolAttached < ppool->iPools ; iPoolAttached++)
	{
	    //- access the attacted pool

	    int iIndex = ppool->piPools[iPoolAttached];

	    struct ch3_pool *ppoolAttached = &pch3->ppool[iIndex];

	}

	//- loop over all diffusion connections attached to this pool

	int iDiffusionAttached;

	for (iDiffusionAttached = 0 ; iDiffusionAttached < ppool->iDiffusions ; iDiffusionAttached++)
	{
	    //- access the attached diffusion connection

	    int iIndex = ppool->piDiffusions[iDiffusionAttached];

	    struct ch3_diffusion *pdiffusionAttached = &pch3->pdiffusion[iIndex];

	}

    }

    //- return result

    return(iResult);
}


static
int
solver_processor(struct TreespaceTraversal *ptstr, void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get pointer to solver

    struct kinetics_info *pki = (struct kinetics_info *)pvUserdata;

    struct simobj_Chemesis3 *pch3 = pki->pch3;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = (struct symtab_HSolveListElement *)TstrGetActual(ptstr);

    //- if a pool

    if (instanceof_pool(phsle))
    {
	//- register current symbol

	int iPool = pch3->iPools;

	//- register type

	pch3->ppool[iPool].mc.iType = MATH_TYPE_Pool;

	//- register identification

	/// \note note: assumes pp define CHEMESIS3_SOURCE_NEUROSPACES

	int iSerial = PidinStackToSerial(ptstr->ppist);

	iSerial = ADDRESSING_NEUROSPACES_2_CHEMESIS3(iSerial);

	pch3->ppool[iPool].mc.iSerial = iSerial;

#ifdef CHEMESIS3_SOURCE_TYPING

	double dModelSourceType
	    = SymbolParameterResolveValue(phsle, ptstr->ppist, "MODEL_SOURCE_TYPE");

	if (dModelSourceType != DBL_MAX)
	{
	    pch3->ppool[iPool].mc.iModelSourceType = dModelSourceType;
	}
	else
	{
	    pch3->ppool[iPool].mc.iModelSourceType = -1;
	}

#endif

	//- register parameters

	/// \todo check for error returns, abort traversal if necessary

	double dDia
	    = SymbolParameterResolveValue(phsle, ptstr->ppist, "DIA");

	if (dDia == DBL_MAX)
	{
	    iResult = TSTR_PROCESSOR_ABORT;
	}

	double dLength
	    = SymbolParameterResolveValue(phsle, ptstr->ppist, "LENGTH");

	if (dLength == DBL_MAX)
	{
	    iResult = TSTR_PROCESSOR_ABORT;
	}

	double dConcentrationInit
	    = SymbolParameterResolveValue(phsle, ptstr->ppist, "concen_init");

	if (dConcentrationInit == DBL_MAX)
	{
	    iResult = TSTR_PROCESSOR_ABORT;
	}

	#define PI 3.14159

	pch3->ppool[iPool].dVolume = PI * dDia * dDia * dLength;
	pch3->ppool[iPool].dConcentrationInit = dConcentrationInit;

#ifdef USE_ENABLE_LINEAR_MODE

	double dLength
	    = SymbolParameterResolveValue(phsle, ptstr->ppist, "LENGTH");

	if (dLength == DBL_MAX)
	{
	    pch3->ho.iCorrections |= CHEMESIS3_CORRECTION_ENABLE_LINEAR_MODE_DISABLED;
	}

	double dDia
	    = SymbolParameterResolveValue(phsle, ptstr->ppist, "DIA");

	if (dDia == DBL_MAX)
	{
	    pch3->ho.iCorrections |= CHEMESIS3_CORRECTION_ENABLE_LINEAR_MODE_DISABLED;
	}

	pch3->ppool[iPool].dDia = dDia;
	pch3->ppool[iPool].dLength = dLength;

#endif

	//- register serial of parent

	{
	    struct symtab_Parameters *pparParent
		= SymbolFindParameter(phsle, ptstr->ppist, "PARENT");

	    if (pparParent)
	    {
		/// \todo I can just subtract the cell's segment ID ?

		struct PidinStack *ppistParent
		    = ParameterResolveToPidinStack(pparParent, ptstr->ppist);

		if (ppistParent)
		{
		    PidinStackLookupTopSymbol(ppistParent);

		    int iParent = PidinStackToSerial(ppistParent);

		    /// \todo check for error

		    if (iParent != INT_MAX)
		    {
			iParent = ADDRESSING_NEUROSPACES_2_CHEMESIS3(iParent);

/* 			pch3->ppool[iPool].iParent = iParent; */
		    }
		    else
		    {
			/// \note parent does not exist

			iResult = TSTR_PROCESSOR_ABORT;
		    }
		}
		else
		{
		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }
	    else
	    {
/* 		pch3->ppool[iPool].iParent = -1; */
	    }
	}

	if (iResult == TSTR_PROCESSOR_ABORT)
	{
	    char pc[1000];

	    PidinStackString(ptstr->ppist, pc, sizeof(pc));

	    Chemesis3Error
		(pch3,
		 NULL,
		 "pool array translation failed at pool %s (pool %i, serial %i)\n",
		 pc,
		 pch3->iPools,
		 pch3->ppool[iPool].mc.iSerial);
	}

	//- increment number of solved pools

	pch3->iPools++;

    }

    //- return result

    return(iResult);
}


static int chemesis3_setup_kinetics(struct simobj_Chemesis3 *pch3, struct Chemesis3TranslationService *pcts)
{
    //- set default result : ok

    int iResult = TRUE;

    //- allocate pidin stack pointing to root

    struct PidinStack *ppistRoot = pcts->pctsd->ppistRoot;

    struct symtab_HSolveListElement *phsleRoot = pcts->pctsd->phsleRoot;

    //- get model context to solve

    struct PidinStack *ppistModel
	= SymbolPrincipalSerial2Context(phsleRoot, ppistRoot, pcts->pctsd->iModel);

    if (ppistModel)
    {
	struct kinetics_info ki =
	{
	    //m the solver to initialize

	    pch3,

	    //m number of pools found

	    0,

	    //m number of reactions found

	    0,

	    //m number of diffusions found

	    0,

	};

	//- lookup symbol

	struct symtab_HSolveListElement *phsleModel
	    = PidinStackLookupTopSymbol(ppistModel);

	//- loop over all symbols, count kinetic related ones

	struct TreespaceTraversal *ptstr
	    = TstrNew
	      (ppistModel,
	       NULL,
	       NULL,
	       solver_counter,
	       (void *)&ki,
	       NULL,
	       NULL);

	int iSuccess = TstrGo(ptstr, phsleModel);

	TstrDelete(ptstr);

	if (iSuccess)
	{
	    if (ki.iPools != 0)
	    {
		//- allocate data structures

		pch3->ppool = (struct ch3_pool *)calloc(ki.iPools, sizeof(struct ch3_pool));

		pch3->preaction = (struct ch3_reaction *)calloc(ki.iReactions, sizeof(struct ch3_reaction));

		pch3->pdiffusion = (struct ch3_diffusion *)calloc(ki.iDiffusions, sizeof(struct ch3_diffusion));

		if (pch3->ppool
		    && pch3->preaction
		    && pch3->pdiffusion)
		{
		}
		else
		{
		    char pc[1000];

		    PidinStackString(ppistModel, pc, sizeof(pc));

		    Chemesis3Error
			(pch3,
			 NULL,
			 "memory failure when compiling %s\n",
			 pc);

		    return(FALSE);
		}
	    }
	    else
	    {
		char pc[1000];

		PidinStackString(ppistModel, pc, sizeof(pc));

		Chemesis3Error
		    (pch3,
		     NULL,
		     "no pools with ion concentrations found inside %s\n",
		     pc);

		return(FALSE);
	    }
	}
	else
	{
	    char pc[1000];

	    PidinStackString(ppistModel, pc, sizeof(pc));

	    Chemesis3Error
		(pch3,
		 NULL,
		 "unable to traverse %s\n",
		 pc);

	    return(FALSE);
	}

	//- link the segments together using the parent link

	iResult = iResult && solver_link(pch3);
    }
    else
    {
	iResult = FALSE;
    }

    //- return result

    return(iResult);
}


int Chemesis3NeurospacesKinetics2Chemesis3(struct Chemesis3TranslationService *pcts)
{
    //- set the service function pointer to chemesis3_setup_kinetics()

    pcts->kinetic_inspector = chemesis3_setup_kinetics;

    //- return result

    return(1);
}


