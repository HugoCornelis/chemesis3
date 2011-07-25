/* -*- C -*- */

%module chemesis3_base


/***************************************************
* Start C code block
***************************************************/
%{
#define CHEMESIS3_SOURCE_NEUROSPACES 1

#include "chemesis3/chemesis3.h"
#include "chemesis3/addressing.h"
#include "chemesis3/mathcomponent.h"
#include "chemesis3/service.h"
%}


%inline %{

int AddressingNeurospaces2Chemesis(int iNeuro);
int AddressingChemesis2Neurospaces(int iChemesis);
int PoolSize(void);
int ReactionSize(void);


int AddressingNeurospaces2Chemesis(int iNeuro)
{

  return ((iNeuro) << NEUROSPACES_2_CHEMESIS3_MAX_FUNCTIONS);

}


int AddressingChemesis2Neurospaces(int iChemesis)
{

  return ((iChemesis) >> NEUROSPACES_2_CHEMESIS3_MAX_FUNCTIONS);

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

