#ifndef CHEMESIS3_SERVICE_H
#define CHEMESIS3_SERVICE_H


struct simobj_Chemesis3;

struct Chemesis3TranslationService;

struct Chemesis3TranslationServiceData;


typedef int (*ComponentInspector)(struct simobj_Chemesis3 *pch3, struct Chemesis3TranslationService *cpts);

struct Chemesis3TranslationService
{
    /// service specific data

    struct Chemesis3TranslationServiceData *pctsd;

    /// \todo guess need to map this to the biological level as defined by
    /// \todo Neurospaces, not done yet.

    /// \todo additionally need to map this to the 'spatial and temporal
    /// \todo accuracy level'.  Not sure how to do that yet.

    /// initializes chemesis3 solver

    ComponentInspector kinetic_inspector;

/*     /// initializes mechanism intermediary */

/*     ComponentInspector mechanisms_inspector; */
};


#endif


