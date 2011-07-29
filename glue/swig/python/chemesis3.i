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
int PoolPointerAssign(struct ch3_pool *ppDst, struct ch3_pool *ppSrc);



int PoolPointerAssign(struct ch3_pool *ppDst, struct ch3_pool *ppSrc)
{

  if( !ppSrc )
  {
    return 0;
  }

  ppDst = ppSrc;
  
  return 1;

}

int AddressingNeurospaces2Chemesis(int iNeuro)
{

  return ADDRESSING_NEUROSPACES_2_CHEMESIS3(iNeuro);

}


int AddressingChemesis2Neurospaces(int iChemesis)
{

  return ADDRESSING_CHEMESIS3_2_NEUROSPACES(iChemesis);

}

int PoolSize(void)
{
  return sizeof(struct ch3_pool);
}

int ReactionSize(void)
{
  return sizeof(struct ch3_reaction);
}

int NumItems(int *pi)
{
  if(!pi)
  {
    return 0;
  }

  return sizeof(pi) / sizeof(int);
}


%} // end inline


/***************************************************
* Imports 
***************************************************/
%include "chemesis3/addressing.h"
%include "chemesis3/chemesis3.h"
%include "chemesis3/mathcomponent.h"
%include "chemesis3/service.h"


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

