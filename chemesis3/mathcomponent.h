

#ifndef CHEMESIS3_MATHCOMPONENT_H
#define CHEMESIS3_MATHCOMPONENT_H


/*s a math component starts with ... */

struct ch3_MathComponent
{

    /// type of structure

    int iType;

#ifdef CHEMESIS3_SOURCE_NEUROSPACES

    /// identification

    int iSerial;

#endif

#ifdef CHEMESIS3_SOURCE_TYPING

    /// model source type number

    /// \note source typing is used to compute aggregate currents ao
    /// \note things.

    int iModelSourceType;

#endif

#ifdef CHEMESIS3_SIZED_MATH_STRUCTURES

    /// size of this structure

    int iSize;

#endif

#ifdef CHEMESIS3_SOURCE_NEUROSPACES

    /// prototype identification

    int iPrototype;

#endif

};


#define MATH_TYPE_Pool 1013
#define MATH_TYPE_Reaction 1014
#define MATH_TYPE_Diffusion 1015


/* struct MathComponentArray */
/* { */
/*     /// number of math components */

/*     int iMathComponents; */

/*     /// math component data */

/*     struct MathComponent *pmc; */

/*     /// math component index, initialize to NULL */

/*     struct MathComponent **ppmcIndex; */

/*     /// cursor for iterations */

/*     int iCursor; */

/*     struct MathComponent *pmcCursor; */
/* }; */


/* struct MathComponentInfo */
/* { */
/*     int iType; */

/*     int iChars; */
/* }; */


/* int MathComponentArrayCallocData(struct MathComponentArray *pmca, int *iTypes); */

/* int MathComponentArrayCursorInitialize(struct MathComponentArray *pmca); */

/* int MathComponentArrayCursorNext(struct MathComponentArray *pmca); */

/* #ifdef CHEMESIS3_SOURCE_NEUROSPACES */

/* int */
/* MathComponentArrayLookupSerial */
/* (struct MathComponentArray *pmca, int iSerial); */

/* #endif */

/* int */
/* MathComponentArraySetAdvance */
/* (struct MathComponentArray *pmca, struct MathComponent *pmc); */

/* struct MathComponent * */
/* MathComponentCopyNext */
/* (struct MathComponent *pmcTarget, struct MathComponent *pmcSource); */

/* struct MathComponentInfo * MathComponentInfoLookup(int iType); */

/* struct MathComponent *MathComponentNext(struct MathComponent *pmc); */


#endif


