/* -*- C -*- */

%module chemesis3_base


/***************************************************
* Start C code block
***************************************************/
%{

#define CHEMESIS3_SOURCE_NEUROSPACES 1 
/* #define CHEMESIS3_SOURCE_TYPING 1 */
/* #define CHEMESIS3_SIZED_MATH_STRUCTURES 1 */
/* #define CHEMESIS3_SOURCE_NEUROSPACES 1 */

#include "chemesis3/chemesis3.h"
#include "chemesis3/addressing.h"
#include "chemesis3/mathcomponent.h"
#include "chemesis3/service.h"

#include "integrators/chemesis3/neurospaces/chemesis3.h"
%}


#define CHEMESIS3_SOURCE_NEUROSPACES 1 
/* #define CHEMESIS3_SOURCE_TYPING 1 */
/* #define CHEMESIS3_SIZED_MATH_STRUCTURES 1 */
/* #define CHEMESIS3_SOURCE_NEUROSPACES 1 */

%inline %{

int AddressingNeurospaces2Chemesis(int iNeuro);
int AddressingChemesis2Neurospaces(int iChemesis);
int PoolSize(void);
int ReactionSize(void);
int SetDiffusionPool1(struct simobj_Chemesis3 *pch3, int iDiffusionIndex, int iPoolIndex);
int SetDiffusionPool2(struct simobj_Chemesis3 *pch3, int iDiffusionIndex, int iPoolIndex);
int solver_reaction_serial_2_index(int iReactionSerial);

//--------------------------------------------------------------------------------


int solver_reaction_serial_2_index(int iReactionSerial)
{
  return 1;
}

int SetDiffusionPool1(struct simobj_Chemesis3 *pch3, int iDiffusionIndex, int iPoolIndex)
{

  struct ch3_diffusion *pDiffusion = NULL;
  struct ch3_pool *pPool = NULL;
  char pcErrorMsg[1024];

  if( !pch3 )
  {

    PyErr_SetString(PyExc_ReferenceError,"No Chemesis3 Simulation Object has been allocated");
    return 0;

  }


  if( iDiffusionIndex > pch3->iDiffusions )
  {

    snprintf(&pcErrorMsg, 1024, "No diffusion exists at index '%d'", iDiffusionIndex);

    PyErr_SetString(PyExc_IndexError, pcErrorMsg);
    return 0;
    
  }
  else
  {
  
    pDiffusion = &pch3->pdiffusion[iDiffusionIndex];

  }


  if( iPoolIndex > pch3->iPools )
  {    

    snprintf(&pcErrorMsg, 1024, "No pool exists at index '%d'", iPoolIndex);

    PyErr_SetString(PyExc_IndexError, pcErrorMsg);
    return 0;
    
  }
  else
  {
    
    pPool = &pch3->ppool[iPoolIndex];

  }

  pDiffusion->ppool1 = pPool;

  return 1;

}


//--------------------------------------------------------------------------------


int SetDiffusionPool2(struct simobj_Chemesis3 *pch3, int iDiffusionIndex, int iPoolIndex)
{

  struct ch3_diffusion *pDiffusion = NULL;
  struct ch3_pool *pPool = NULL;
  char pcErrorMsg[1024];

  if( !pch3 )
  {

    PyErr_SetString(PyExc_ReferenceError,"No Chemesis3 Simulation Object has been allocated");
    return 0;

  }


  if( iDiffusionIndex > pch3->iDiffusions )
  {

    snprintf(pcErrorMsg, 1024, "No diffusion exists at index '%d'", iDiffusionIndex);

    PyErr_SetString(PyExc_IndexError, pcErrorMsg);
    return 0;
    
  }
  else
  {
  
    pDiffusion = &pch3->pdiffusion[iDiffusionIndex];

  }


  if( iPoolIndex > pch3->iPools )
  {    

    snprintf(pcErrorMsg, 1024, "No pool exists at index '%d'", iPoolIndex);

    PyErr_SetString(PyExc_IndexError, pcErrorMsg);
    return 0;
    
  }
  else
  {
    
    pPool = &pch3->ppool[iPoolIndex];

  }

  pDiffusion->ppool2 = pPool;

  return 1;

}

//--------------------------------------------------------------------------------

int AddressingNeurospaces2Chemesis(int iNeuro)
{

  return ADDRESSING_NEUROSPACES_2_CHEMESIS3(iNeuro);

}

//--------------------------------------------------------------------------------

int AddressingChemesis2Neurospaces(int iChemesis)
{

  return ADDRESSING_CHEMESIS3_2_NEUROSPACES(iChemesis);

}

//--------------------------------------------------------------------------------

int PoolSize(void)
{
  return sizeof(struct ch3_pool);
}

//--------------------------------------------------------------------------------

int ReactionSize(void)
{
  return sizeof(struct ch3_reaction);
}

//--------------------------------------------------------------------------------

int NumItems(int *pi)
{
  if(!pi)
  {
    return 0;
  }

  return sizeof(pi) / sizeof(int);
}

//--------------------------------------------------------------------------------


%} // end inline


/***************************************************
* Imports 
***************************************************/
%include "chemesis3/addressing.h"
%include "chemesis3/chemesis3.h"
%include "chemesis3/mathcomponent.h"
%include "chemesis3/service.h"
%include "integrators/chemesis3/neurospaces/chemesis3.h"

// info on cpointer library here http://www.swig.org/Doc1.3/Library.html#Library_nn4
%include "cpointer.i"

%pointer_functions(struct ch3_pool, Chemesis3PoolPointer)


// info on the carray library here http://www.swig.org/Doc1.3/Library.html#Library_carrays
%include "carrays.i"

%array_functions(double, DoubleArray)

%array_functions(int, IntArray)

%array_functions(struct ch3_pool, Chemesis3PoolArray)

%array_functions(struct ch3_reaction, Chemesis3ReactionArray)

%array_functions(struct ch3_diffusion, Chemesis3DiffusionArray)

