from netpyne import sim
from tut7 import simConfig, netParams

###############################################################################
# EXECUTION CODE (via netpyne)
###############################################################################

# Create network and run simulation (sim.createAndSimulate()를 대체)
sim.initialize(                     # create network object and set cfg and net params
        simConfig = simConfig,      # pass simulation config and network params as arguments
        netParams = netParams)
sim.net.createPops()                # instantiate network populations
sim.net.createCells()               # instantiate network cells based on defined populations
sim.net.connectCells()              # create connections between cells based on params
sim.net.addStims()                  # add stimulation
sim.setupRecording()                # setup variables to record for each cell (spikes, V traces, etc)

###############################################################################
# INTERACTING WITH INSTANTIATED NETWORK
###############################################################################

# modify conn weights
sim.net.modifyConns({'conds': {'label': 'hop->hop'}, 'weight': 0.5})

###############################################################################

sim.runSim()                        # run parallel Neuron simulation
sim.gatherData()                    # gather spiking data and cell info from each node
sim.saveData()                      # save params, cell info and sim output to file (pickle,mat,txt,etc)
# sim.analysis.plotData()             # plot spike raster


# modify cells geometry
sim.net.modifyCells({'conds': {'pop': 'hop'},
                    'secs': {'soma': {'geom': {'L': 160}}}})

sim.simulate()
sim.analysis.plotRaster(syncLines=True)
sim.analysis.plotTraces(include = [1])

input()

