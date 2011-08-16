#! /usr/bin/env python
"""
a test for cal1 use in python
with a model container.
"""
import os
import pdb
import sys

from test_library import add_package_path

# have to go a level deeper since muliple imports would
# register the neurospaces module.
add_package_path("model-container", subdir="neurospaces")
add_package_path("chemesis3", subdir="neurospaces")
add_package_path("experiment", subdir="neurospaces")

#---------------------------------------------------------------------------

from model_container import ModelContainer

my_model = ModelContainer()

my_model.Read("chemesis/cal1.ndf")

#---------------------------------------------------------------------------

from chemesis3 import Chemesis3

chem3 = Chemesis3(name="cal1", model=my_model)

chem3.Initiate()

chem3.SetTimeStep(0.0002)

chem3.Compile()

#---------------------------------------------------------------------------

from experiment.output import Output

og = Output("/tmp/output_cal1")

concentration1 = chem3.GetAddress("/cal1/somaCa", "concentration")
og.AddOutput("concentration", concentration1)

concentration2 = chem3.GetAddress("/cal1/somaCabuf", "concentration")
og.AddOutput("concentration", concentration2)

concentration3 = chem3.GetAddress("/cal1/somabuf", "concentration")
og.AddOutput("concentration", concentration3)


simulation_time = 0.0

time_step = 0.0002

for i in range(0,1000):

    simulation_time = i * time_step
    
    chem3.Step()
    
    og.Step(simulation_time)


chem3.Finish()
og.Finish()

print "Done!"

