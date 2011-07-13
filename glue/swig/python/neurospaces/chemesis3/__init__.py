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


#************************* Begin Heccer **************************
class Chemesis3:



    def __init__(self, name="Untitled Chemesis3"):

        pass


#**************************** End Heccer **************************
