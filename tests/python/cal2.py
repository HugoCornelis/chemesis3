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

ca = [Pool(),
      Pool(),
      Pool(),
      Pool(),
      Pool(),
      Pool(),
      ]

ca[0].SetSerial(2)
ca[0].SetReactions([0])
ca[0].SetReactionFlags([0])
ca[0].SetDiffusions([0])
ca[0].SetDiffusionsFlags([1])
ca[0].dConcentrationInit = 4e-3
ca[0].dConcentration = 0.0
ca[0].dVolume = 1.0053088e-10
ca[0].dUnits = 1e-3
ca[0].dQuantity = 0.0
ca[0].iConserve = 0
ca[0].dQuantityTotal = 0.0
ca[0].dConcentrationTotal = 0.0

ca[1].SetSerial(3)
ca[1].SetReactions([0])
ca[1].SetReactionFlags([1])
ca[1].dConcentrationInit = 0.003
ca[1].dConcentration = 0.0
ca[1].dVolume = 1.0053088e-10
ca[1].dUnits = 1e-3
ca[1].dQuantity = 0.0
ca[1].iConserve = 0
ca[1].dQuantityTotal = 0.0
ca[1].dConcentrationTotal = 0.0

ca[2].SetSerial(4)
ca[2].SetReactionFlags([-1])
ca[2].SetPools([1])
ca[2].SetPoolsFlags([0])
ca[2].dConcentrationInit = 0.0
ca[2].dConcentration = 0.0
ca[2].dVolume = 1.0053088e-10
ca[2].dUnits = 0.0
ca[2].dQuantity = 0.0
ca[2].iConserve = 1
ca[2].dQuantityTotal = 0.0
ca[2].dConcentrationTotal = 0.153

ca[3].SetSerial(6)
ca[3].SetReactions([1])
ca[3].SetReactionFlags([0])
ca[3].SetDiffusions([0])
ca[3].SetDiffusionsFlags([-1])
ca[3].dConcentrationInit = 0.0001
ca[3].dConcentration = 0.0
ca[3].dVolume = 2.5132720000000001e-11
ca[3].dUnits = 1e-3
ca[3].dQuantity = 0.0
ca[3].iConserve = 0
ca[3].dQuantityTotal = 0.0
ca[3].dConcentrationTotal = 0.0

ca[4].SetSerial(7)
ca[4].SetReactions([1])
ca[4].SetReactionFlags([1])
ca[4].dConcentrationInit = 0.003
ca[4].dConcentration = 0.0
ca[4].dVolume = 2.5132720000000001e-11
ca[4].dUnits = 1e-3
ca[4].dQuantity = 0.0
ca[4].iConserve = 0
ca[4].dQuantityTotal = 0.0
ca[4].dConcentrationTotal = 0.0

ca[5].SetSerial(8)
ca[5].SetReactionFlags([-1])
ca[5].SetPools([4])
ca[5].SetPoolsFlags([0])
ca[5].dConcentrationInit = 0.0
ca[5].dConcentration = 0.0
ca[5].dVolume = 2.5132720000000001e-11
ca[5].dUnits = 0.0
ca[5].dQuantity = 0.0
ca[5].iConserve = 1
ca[5].dQuantityTotal = 0.0
ca[5].dConcentrationTotal = 0.153


from neurospaces.chemesis3.components import Reaction

rxn = [Reaction(),
       Reaction(),]

rxn[0].SetSerial(5)
rxn[0].SetProducts([1])
rxn[0].SetSubstrates([0, 2])
rxn[0].dBackwardRate = 0.5
rxn[0].dBackwardSolved = 0.0
rxn[0].dForwardRate = 1e2
rxn[0].dForwardSolved = 0.0

rxn[1].SetSerial(5)
rxn[1].SetProducts([4])
rxn[1].SetSubstrates([3, 5])
rxn[1].dBackwardRate = 0.5
rxn[1].dBackwardSolved = 0.0
rxn[1].dForwardRate = 1e2
rxn[1].dForwardSolved = 0.0


from neurospaces.chemesis3.components import Diffusion

diff = [Diffusion()]

diff[0].SetSerial(5)
diff[0].dDiffusionConstant = 6e-7
diff[0].dLength1 = 0.0002
diff[0].dArea1 = 5.0265440000000004e-07
diff[0].dLength2 = 0.0002
diff[0].dArea2 = 1.2566360000000001e-07
diff[0].dFlux1 = 0.0
diff[0].dFlux2 = 0.0
diff[0].dUnits = 1e-3


from neurospaces.chemesis3.components import SimObjChemesis3
import neurospaces.chemesis3.chemesis3_base as chemesis3_base

ch3 = SimObjChemesis3('cal2')

ch3.SetPools(ca)
ch3.SetReactions(rxn)

diff[0].ppool1 = chemesis3_base.Chemesis3PoolArray_getitem(ch3.ppool, 0)
diff[0].ppool2 = chemesis3_base.Chemesis3PoolArray_getitem(ch3.ppool, 3)

ch3.SetDiffusions(diff)

# set the time step
ch3.dStep = TIME_STEP

chemesis3_base.Chemesis3Initiate(ch3)


# we need an output object so we import from the experiment path

add_package_path("experiment", subdir='neurospaces')

from experiment.output import Output

og = Output("/tmp/output_cal2")

og.SetFormat(' %.9f')


concentration1 = chemesis3_base.Chemesis3AddressVariable(ch3, 2, "concentration")
concentration2 = chemesis3_base.Chemesis3AddressVariable(ch3, 4, "concentration")
concentration3 = chemesis3_base.Chemesis3AddressVariable(ch3, 6, "concentration")
concentration4 = chemesis3_base.Chemesis3AddressVariable(ch3, 8, "concentration")

og.AddOutput("concentration", concentration1)
og.AddOutput("concentration", concentration2)
og.AddOutput("concentration", concentration3)
og.AddOutput("concentration", concentration4)

simulation_time = 0.0

for i in range(0,STEPS):

    simulation_time = i * TIME_STEP + TIME_GRANULARITY

    chemesis3_base.Chemesis3Advance(ch3, simulation_time)

    og.Step(simulation_time)


og.Finish()
print "Done!"

