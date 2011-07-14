"""!
@package chemesis3 Kinetic reaction and biochemical reaction pathways for G3.


"""

# System imports
import os
import pdb
import sys

try:

    import chemesis3_base

except ImportError, e:

    sys.exit("Could not import compiled SWIG chemesis3 library: %s" % e)

#---------------------------------------------------------------------------

def CreateIntArray(array):

    if array is None:

        return

    if isinstance(array, list):

        length = len(array)
            
        array_pointer = chemesis3_base.new_IntArray(length)
            
        for index, i in enumerate(array):
                
            chemesis3_base.IntArray_setitem(array_pointer, index, i)

    else:
            
        # this is the case when we aren't passed a list and only
        # have one item

        length = 1

        array_pointer = chemesis3_base.new_IntArray(length)

        chemesis3_base.IntArray_setitem(array_pointer, 0, array)

    return (array_pointer, length)


#---------------------------------------------------------------------------


def CreateChemesis3PoolArray(array):

    if array is None:

        return

    if isinstance(array, list):

        length = len(array)
            
        array_pointer = chemesis3_base.new_Chemesis3PoolArray(length)
            
        for index, i in enumerate(array):
                
            chemesis3_base.Chemesis3PoolArray_setitem(array_pointer, index, i)

    else:
            
        # this is the case when we aren't passed a list and only
        # have one item

        length = 1

        array_pointer = chemesis3_base.new_Chemesis3PoolArray(length)

        chemesis3_base.Chemesis3PoolArray_setitem(array_pointer, 0, array)

    return (array_pointer, length)


#---------------------------------------------------------------------------

def CreateChemesis3ReactionArray(array):

    if array is None:

        return

    if isinstance(array, list):

        length = len(array)
            
        array_pointer = chemesis3_base.new_Chemesis3ReactionArray(length)
            
        for index, i in enumerate(array):
                
            chemesis3_base.Chemesis3ReactionArray_setitem(array_pointer, index, i)

    else:
            
        # this is the case when we aren't passed a list and only
        # have one item

        length = 1

        array_pointer = chemesis3_base.new_Chemesis3ReactionArray(length)

        chemesis3_base.Chemesis3ReactionArray_setitem(array_pointer, 0, array)

    return (array_pointer, length)

#---------------------------------------------------------------------------



#************************* Begin SimObjChemesis3 **************************
class SimObjChemesis3(chemesis3_base.simobj_Chemesis3):

    def __init__(self, name="Untitled"):

        chemesis3_base.simobj_Chemesis3.__init(self)

        self.pcName = name

#---------------------------------------------------------------------------

    def SetPools(self, pools):

        if self.ppool is not None:

            chemesis3_base.delete_Chemesis3PoolArray(self.ppool)

            self.iPools = 0
            
        pool_data = CreateChemesis3PoolArray(pools)

        self.ppool = pool_data[0]

        self.iPools = pool_data[1]
        
#---------------------------------------------------------------------------

    def SetReactions(self, reactions):

        if self.preaction is not None:

            chemesis3_base.delete_Chemesis3ReactionArray(self.preaction)

            self.iReactions = 0
            
        reaction_data = CreateChemesis3ReactionArray(pools)

        self.preaction = reaction_data[0]

        self.iReactions = reaction_data[1]
    

#************************* End SimObjChemesis3 *****************************





#************************* Begin Pool **************************
class Pool(chemesis3_base.ch3_pool):
    """!
    @brief class for a chemesis 3 pool 

    """

    def __init__(self):

        chemesis3_base.ch3_pool.__init__(self)


        
#---------------------------------------------------------------------------


    def SetReactions(self, reactions):
        """!
        @brief Sets a python list into a C array
        """

        if self.piReactions is not None:

            chemesis3_base.delete_IntArray(self.piReactions)
            
        int_array = CreateIntArray(reactions)

        self.piReactions = int_array[0]

        self.iReactions = int_array[1]


#---------------------------------------------------------------------------

    def GetReaction(self, index):

        if self.piReactions is None:

            raise IndexError("no reaction at index %d" % index)
        
        r = chemesis3_base.IntArray_getitem(self.piReactions, index)

        return r

#---------------------------------------------------------------------------

    def NumReactions(self):

        return self.iReactions


#************************* Begin Pool **************************
