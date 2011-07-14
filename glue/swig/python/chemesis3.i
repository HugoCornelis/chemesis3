/* -*- C -*- */

%module chemesis3_base


/***************************************************
* Start C code block
***************************************************/
%{
#include "chemesis3/addressing.h"
#include "chemesis3/chemesis3.h"
#include "chemesis3/mathcomponent.h"

%}


/***************************************************
* Imports 
***************************************************/
%include "chemesis3/addressing.h"
%include "chemesis3/chemesis3.h"
%include "chemesis3/mathcomponent.h"

 // info on cpointer library here http://www.swig.org/Doc1.3/Library.html#Library_nn4
 //%include "cpointer.i"


 // info on the carray library here http://www.swig.org/Doc1.3/Library.html#Library_carrays
%include "carrays.i"

%array_functions(double, DoubleArray)

%array_functions(int, IntArray)

%array_functions(struct ch3_pool, Chemesis3PoolArray)

%array_functions(struct ch3_reaction, Chemesis3ReactionArray)

