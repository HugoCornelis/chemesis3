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

#---------------------------------------------------------------------------

    def SetDiffusions(self, diffusions):

        if self.pdiffusions is not None:

            chemesis3_base.delete_Chemesis3DiffusionsArray(self.pdiffusions)

            self.iDiffusions = 0
            
        diffusions_data = CreateChemesis3DiffusionsArray(diffusions)

        self.pdiffusions = diffusions_data[0]

        self.iDiffusions = diffusions_data[1]

#************************* End SimObjChemesis3 *****************************





#************************* Begin Pool **************************
class Pool(chemesis3_base.ch3_pool):
    """!
    @brief class for a chemesis 3 pool 

    """

    def __init__(self):

        chemesis3_base.ch3_pool.__init__(self)

        self.mc.iType = chemesis3_base.MATH_TYPE_Pool

#---------------------------------------------------------------------------

    def SetSerial(self, serial):

        self.mc.iSerial = chemesis3_base.AddressingNeurospaces2Chemesis(serial)

#---------------------------------------------------------------------------

    def SetReactionFlags(self, reactions):
        """!
        @brief Sets a python list into a C array
        """

        if self.piReactionFlags is not None:

            chemesis3_base.delete_IntArray(self.piReactionFlags)
            
        int_array = CreateIntArray(reactions)

        self.piReactionFlags = int_array[0]
        
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

#---------------------------------------------------------------------------

    def SetDiffusionsFlags(self, diffusions):
        """!
        @brief Sets a python list into a C array
        """

        if self.piDiffusionsFlags is not None:

            chemesis3_base.delete_IntArray(self.piDiffusionsFlags)
            
        int_array = CreateIntArray(diffusions)

        self.piDiffusionsFlags = int_array[0]

#---------------------------------------------------------------------------

    def SetDiffusions(self, diffusions):
        """!
        @brief Sets a python list into a C array
        """

        if self.piDiffusions is not None:

            chemesis3_base.delete_IntArray(self.piDiffusions)
            
        int_array = CreateIntArray(reactions)

        self.piDiffusions = int_array[0]

        self.iDiffusions = int_array[1]


#---------------------------------------------------------------------------

    def GetDiffusion(self, index):

        if self.piDiffusion is None:

            raise IndexError("no diffusion at index %d" % index)
        
        r = chemesis3_base.IntArray_getitem(self.piDiffusions, index)

        return r

#---------------------------------------------------------------------------

    def NumDiffusions(self):

        return self.iDiffusions


#---------------------------------------------------------------------------

    def SetPoolsFlags(self, pools):
        """!
        @brief Sets a python list into a C array
        """

        if self.piPoolsFlags is not None:

            chemesis3_base.delete_IntArray(self.piPoolsFlags)
            
        int_array = CreateIntArray(pools)

        self.piPoolsFlags = int_array[0]

#---------------------------------------------------------------------------

    def SetPools(self, pools):
        """!
        @brief Sets a python list into a C array
        """

        if self.piPools is not None:

            chemesis3_base.delete_IntArray(self.piPools)
            
        int_array = CreateIntArray(pools)

        self.piPools = int_array[0]

        self.iPools = int_array[1]


#---------------------------------------------------------------------------

    def GetPool(self, index):

        if self.piDiffusion is None:

            raise IndexError("no diffusion at index %d" % index)
        
        r = chemesis3_base.IntArray_getitem(self.piDiffusions, index)

        return r

#---------------------------------------------------------------------------

    def NumPools(self):

        return self.iPools


#************************* Begin Pool **************************




#************************* Begin Reaction **************************
class Reaction(chemesis3_base.ch3_reaction):
    """!
    @brief class for a chemesis 3 reaction 

    """

    def __init__(self):

        chemesis3_base.ch3_reaction.__init__(self)

        self.mc.iType = chemesis3_base.MATH_TYPE_Reaction

#---------------------------------------------------------------------------

    def SetSerial(self, serial):

        self.mc.iSerial = chemesis3_base.AddressingNeurospaces2Chemesis(serial)
        
#---------------------------------------------------------------------------

    def SetSubstrates(self, substrates):
        """!
        @brief Sets a python list into a C array
        """

        if self.piSubstrates is not None:

            chemesis3_base.delete_IntArray(self.piSubstrates)
            
        int_array = CreateIntArray(substrates)

        self.piSubstrates = int_array[0]

        self.iSubstrates = int_array[1]

#---------------------------------------------------------------------------

    def SetProducts(self, products):
        """!
        @brief Sets a python list into a C array
        """

        if self.piProducts is not None:

            chemesis3_base.delete_IntArray(self.piProducts)
            
        int_array = CreateIntArray(products)

        self.piProducts = int_array[0]

        self.iProducts = int_array[1]


#************************* Begin Reaction **************************




#************************* Begin Diffusion **************************
class Diffusion(chemesis3_base.ch3_reaction):
    """!
    @brief class for a chemesis 3 reaction 

    """

    def __init__(self):

        chemesis3_base.ch3_reaction.__init__(self)

#---------------------------------------------------------------------------

    def SetPool1(self, pool):
        """!
        @brief Sets pool 1
        """

        if pool is None:

            return False

        chemesis_base.Chemesis3Pointer_assign(self.ppool1, pool)

        return True
    
#---------------------------------------------------------------------------

    def SetPool2(self, pool):
        """!
        @brief Sets pool 2
        """

        if pool is None:

            return False

        chemesis_base.Chemesis3Pointer_assign(self.ppool2, pool)

        return True

#************************* Begin Diffusion **************************