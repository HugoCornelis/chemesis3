#! /usr/bin/env python
"""

"""
import os
import sys
import pdb


STEPS = 1000
TIME_STEP = 0.002
TIME_GRANULARITY = 1e-9


from test_library import add_package_path

add_package_path("chemesis3")
add_package_path("model-container", subdir="neurospaces")


#---------------------------------------------------------------------------

from model_container import ModelContainer

my_model = ModelContainer()

my_model.Read("chemesis/cal1.ndf")

#---------------------------------------------------------------------------

from neurospaces.chemesis3.components import SimObjChemesis3
from neurospaces.chemesis3 import CHEMESIS3_STATUS_PHASE_2

ch3 = SimObjChemesis3('cal1')

# set the time step
ch3.dStep = TIME_STEP

import neurospaces.chemesis3.chemesis3_base as chemesis3_base


chemesis3_base.Chemesis3Construct(ch3,
                                  my_model.GetCore(),
                                  'cal1',
                                  None,
                                  None)

chemesis3_base.Chemesis3CompileP1(ch3)

chemesis3_base.Chemesis3Initiate(ch3)

# we need an output object so we import from the experiment path

add_package_path("experiment", subdir='neurospaces')

from experiment.output import Output

og = Output("/tmp/output_cal1")

#og.SetFormat(' %.9f')


concentration1 = chemesis3_base.Chemesis3AddressVariable(ch3, 2, "concentration")
concentration2 = chemesis3_base.Chemesis3AddressVariable(ch3, 3, "concentration")
concentration3 = chemesis3_base.Chemesis3AddressVariable(ch3, 4, "concentration")

og.AddOutput("concentration1", concentration1)
og.AddOutput("concentration2", concentration2)
og.AddOutput("concentration3", concentration3)

simulation_time = 0.0


for i in range(0,STEPS):

    simulation_time = i * TIME_STEP + TIME_GRANULARITY
    
    chemesis3_base.Chemesis3Advance(ch3, simulation_time)

    og.Step(simulation_time)

og.Finish()
print "Done!"

