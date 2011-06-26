

#ifndef CHEMESIS3_ADDRESSING_H
#define CHEMESIS3_ADDRESSING_H


#include <stdio.h>


#include "chemesis3.h"


#ifdef CHEMESIS3_SOURCE_NEUROSPACES

/// \def number of function allowed per symbol as a shift operand

#define NEUROSPACES_2_CHEMESIS3_MAX_FUNCTIONS 2

#define ADDRESSING_NEUROSPACES_2_CHEMESIS3(iNeuro) ((iNeuro) << NEUROSPACES_2_CHEMESIS3_MAX_FUNCTIONS)

#define ADDRESSING_CHEMESIS3_2_NEUROSPACES(iChemesis3) ((iChemesis3) >> NEUROSPACES_2_CHEMESIS3_MAX_FUNCTIONS)

/// \todo should add defines for assigning function IDs.
/// \todo note that this would be solved automatically if the
/// \todo neurospaces model_container would do full traversals.


double *
Chemesis3AddressAggregator
(struct simobj_Chemesis3 *pch3, int iSerial, char *pcType);

char *
Chemesis3AddressableSet
(struct simobj_Chemesis3 *pch3, int iSerial, char *pcType, double dValue);

double *
Chemesis3AddressPoolVariable
(struct simobj_Chemesis3 *pch3, int iIndex, char *pcField);

double *
Chemesis3AddressReactionVariable
(struct simobj_Chemesis3 *pch3, int iIntermediary, char *pcField);

double *
Chemesis3AddressVariable
(struct simobj_Chemesis3 *pch3, int iSerial, char *pcType);

#else

double *
Chemesis3AddressVariable
(struct simobj_Chemesis3 *pch3, int iSerial, char *pcType);

#endif


#endif


