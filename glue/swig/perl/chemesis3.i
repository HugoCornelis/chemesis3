/* -*- C -*- */

/* swig -perl5 -makedefault -module Chemesis3 chemesis3.i */
/* gcc -c chemesis3_wrap.c `perl -MExtUtils::Embed -e ccopts`  */
/* gcc -shared chemesis3_wrap.o -L. -lchemesis3 -o chemesis3.so */

%module SwiggableChemesis3

/* %typemap(in) struct Neurospaces * { */

/*     //- cast to _p_Neurospaces */

/*     if (SvOK($input)) */
/*     { */
/* 	$1 = SvRV($input); */
/*     } */
/* } */

/* %typemap(out) struct Neurospaces * { */

/*     //- cast to _p_Neurospaces */

/*     $1 = $input; */
/* } */

/* %typemap(ruby,in) (int size, int *ary) { */
/*    int i; */
/*    if (!rb_obj_is_kind_of($input,rb_cArray)) */
/*      rb_raise(rb_eArgError, "Expected Array of Integers"); */
/*    $1 = RARRAY($input)->len; */
/*    $2 = malloc($1*sizeof(int)); */
/*    for (i=0; i<$1; ++i) */
/*      ($2)[i] = NUM2INT(RARRAY($input)->ptr[i]); */
/* } */
/* %typemap(freearg) (int size, int *ary) { */
/*     if ($2) free($2); */
/* } */

/* %typemap(memberin) int [ANY] */
/* { */
/*     int i; */
/*     for (i = 0 ; i < $1_dim0 ; i++) */
/*     { */
/* 	$1[i] = $input[i]; */
/*     } */
/* } */

%{
#include "chemesis3/config.h"
#include "chemesis3/addressing.h"
#include "chemesis3/chemesis3.h"

//t so this should depend on the configuration
//t perhaps this can be done using regular #ifdef statements, not sure

#include "integrators/chemesis3/neurospaces/chemesis3.h"

/* #include "/usr/local/include/neurospaces/neurospaces.h" */

%}

%inline %{


/// integer array handling

//t use array generics, see carray.i

int *int_array(int size)
{
    return (int *) malloc(sizeof(int) * size);
}
void int_destroy(int *a)
{
    free(a);
}
void int_set(int *a, int i, int val)
{
    a[i] = val;
}
int int_get(int *a, int i)
{
    return a[i];
}

/// double array handling

//t use array generics, see carray.i

double *double_array(int size)
{
    return (double *) malloc(sizeof(double) * size);
}
void double_destroy(double *a)
{
    free(a);
}
void double_set(double *a, int i, double val)
{
    a[i] = val;
}
double double_get(double *a, int i)
{
    return a[i];
}

/// scheduler optimization

typedef int (*DriverMethod)(void *pvData);

void * chemesis3_get_driver_data(struct simobj_Chemesis3 *pch3)
{
    return((void *)pch3);
}


void * chemesis3_get_driver_method(struct simobj_Chemesis3 *pch3)
{
    return((void *)pch3);
}


%}

%include "chemesis3/config.h"
%include "chemesis3/addressing.h"
%include "chemesis3/chemesis3.h"

//t so this should depend on the configuration
//t perhaps this can be done using regular #ifdef statements, not sure

%include "integrators/chemesis3/neurospaces/chemesis3.h"

/* %include "/usr/local/include/neurospaces/neurospaces.h" */


