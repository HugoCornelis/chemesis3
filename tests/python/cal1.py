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

from neurospaces.chemesis3.components import Pool

soma_ca = [Pool(),
           Pool(),
           Pool(),
           ]

soma_ca[0].SetSerial(2)

soma_ca[0].SetReactionFlags([0])
soma_ca[0].SetReactions([0])

soma_ca[0].dConcentrationInit = 0.001
soma_ca[0].dConcentration = 0.0

soma_ca[0].dVolume = 1.085733504e-08
soma_ca[0].dUnits = 1e-3

soma_ca[0].dQuantity = 0.0

soma_ca[0].iConserve = 0

soma_ca[0].dQuantityTotal = 0.0

soma_ca[0].dConcentrationTotal = 0.0



soma_ca[1].SetSerial(3)

soma_ca[1].SetReactionFlags([1])
soma_ca[1].SetReactions([0])

soma_ca[1].dConcentrationInit = 0.003
soma_ca[1].dConcentration = 0.0

soma_ca[1].dVolume = 1.085733504e-08
soma_ca[1].dUnits = 1e-3

soma_ca[1].dQuantity = 0.0

soma_ca[1].iConserve = 0

soma_ca[1].dQuantityTotal = 0.0

soma_ca[1].dConcentrationTotal = 0.0



soma_ca[2].SetSerial(4)

soma_ca[2].SetReactionFlags([-1])


soma_ca[2].SetPools([1])
soma_ca[2].SetPoolsFlags([0])


soma_ca[2].dConcentrationInit = 0.153
soma_ca[2].dConcentration = 0.0

soma_ca[2].dVolume = 1.085733504e-08
soma_ca[2].dUnits = 0.0

soma_ca[2].dQuantity = 0.0

soma_ca[2].iConserve = 1

soma_ca[2].dQuantityTotal = 0.0

soma_ca[2].dConcentrationTotal = 0.153


from neurospaces.chemesis3.components import Reaction

somacabufrxn = Reaction()

somacabufrxn.SetSerial(5)

somacabufrxn.SetProducts([1])

somacabufrxn.SetSubstrates([0, 2])

somacabufrxn.dBackwardRate = 0.5
somacabufrxn.dBackwardSolved = 0.0

somacabufrxn.dForwardRate = 1e2
somacabufrxn.dForwardSolved = 0.0


from neurospaces.chemesis3.components import SimObjChemesis3

ch3 = SimObjChemesis3('cal1')

ch3.SetPools(soma_ca)

ch3.SetReactions(somacabufrxn)

# set the time step
ch3.dStep = TIME_STEP

import neurospaces.chemesis3.chemesis3_base as chemesis3_base

chemesis3_base.Chemesis3Initiate(ch3)


# we need an output object so we import from the experiment path

add_package_path("experiment", subdir='neurospaces')

from experiment.output import Output

og = Output("/tmp/output_cal1")

#og.SetFormat(' %.9f')


concentration1 = chemesis3_base.Chemesis3AddressVariable(ch3, 2, "concentration")
concentration2 = chemesis3_base.Chemesis3AddressVariable(ch3, 3, "concentration")
concentration3 = chemesis3_base.Chemesis3AddressVariable(ch3, 4, "concentration")

og.AddOutput("concentration", concentration1)
og.AddOutput("concentration", concentration2)
og.AddOutput("concentration", concentration3)

simulation_time = 0.0


for i in range(0,STEPS):

    simulation_time = i * TIME_STEP + TIME_GRANULARITY

    chemesis3_base.Chemesis3Advance(ch3, simulation_time)

    og.Step(simulation_time)


og.Finish()
print "Done!"

