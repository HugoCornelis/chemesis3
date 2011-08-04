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


import __cbi__

#************************* Chemesis3 constants **************************
#
# Moved these here so that these constants can be accessible from the top level
# import of the heccer module.
#
AVOGADRO = chemesis3_base.AVOGADRO
RK_INT = chemesis3_base.RK_INT
TRAPEZOIDAL_INT = chemesis3_base.TRAPEZOIDAL_INT
GEAR_INT = chemesis3_base.GEAR_INT
EPC_INT = chemesis3_base.EPC_INT
FEULER_INT = chemesis3_base.FEULER_INT
EEULER_INT = chemesis3_base.EEULER_INT
AB2_INT = chemesis3_base.AB2_INT
AB3_INT = chemesis3_base.AB3_INT
AB4_INT = chemesis3_base.AB4_INT
AB5_INT = chemesis3_base.AB5_INT
BEULER_INT = chemesis3_base.BEULER_INT
CRANK_INT = chemesis3_base.CRANK_INT

CHEMESIS3_STATUS_PHASE_0 = chemesis3_base.CHEMESIS3_STATUS_PHASE_0
CHEMESIS3_STATUS_PHASE_1 = chemesis3_base.CHEMESIS3_STATUS_PHASE_1
CHEMESIS3_STATUS_PHASE_2 = chemesis3_base.CHEMESIS3_STATUS_PHASE_2
CHEMESIS3_STATUS_PHASE_3 = chemesis3_base.CHEMESIS3_STATUS_PHASE_3
CHEMESIS3_STATUS_PHASE_4 = chemesis3_base.CHEMESIS3_STATUS_PHASE_4
CHEMESIS3_STATUS_PHASE_5 = chemesis3_base.CHEMESIS3_STATUS_PHASE_5
#********************* End Constants **************************




#************************* Begin Chemesis3 **************************
class Chemesis3:



    def __init__(self, name="Untitled Chemesis3"):

        pass


#---------------------------------------------------------------------------


#**************************** End Chemesis3 **************************
