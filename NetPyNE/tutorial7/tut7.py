from netpyne import specs

###############################################################################
# NETWORK PARAMETERS
###############################################################################

netParams = specs.NetParams()  # object of class NetParams to store the network parameters

# Cell parameters
## PYR cell properties
secs = {}
secs['soma'] = {'geom': {}, 'topol': {}, 'mechs': {}}
secs['soma']['geom'] = {'diam': 18.8, 'L': 18.8}
secs['soma']['mechs']['hh'] = {'gnabar': 0.12, 'gkbar': 0.036, 'gl': 0.003, 'el': -70}
netParams.cellParams['PYR'] = {'secs': secs}  # add dict to list of cell properties

# Population parameters
netParams.popParams['hop'] = {'cellType': 'PYR', 'cellModel': 'HH', 'numCells': 50}      # add dict with params for this pop
#netParams.popParams['background'] = {'cellModel': 'NetStim', 'rate': 50, 'noise': 0.5}  # background inputs

# Synaptic mechanism parameters
netParams.synMechParams['exc'] = {'mod': 'Exp2Syn', 'tau1': 0.1, 'tau2': 1.0, 'e': 0}
netParams.synMechParams['inh'] = {'mod': 'Exp2Syn', 'tau1': 0.1, 'tau2': 1.0, 'e': -80}

# Stimulation parameters
netParams.stimSourceParams['bkg'] = {'type': 'NetStim', 'rate': 50, 'noise': 0.5}
netParams.stimTargetParams['bkg->all'] = {'source': 'bkg', 'conds': {'pop': 'hop'}, 'weight': 0.1, 'delay': 1, 'synMech': 'exc'}

# Connectivity parameters
netParams.connParams['hop->hop'] = {
        'preConds': {'pop': 'hop'},         # presynaptic conditions
        'postConds': {'pop': 'hop'},        # postsynaptic conditions
        'weight': 0.0,                      # weight of each connection
        'synMech': 'inh',                   # target inh synapse
        'delay': 5}                         # delay

###############################################################################
# SIMULATION PARAMETERS
###############################################################################
simConfig = specs.SimConfig()  # object of class SimConfig to store simulation configuration

# Simulation options
simConfig.duration = 0.5*1e3        # Duration of the simulation, in ms
simConfig.dt = 0.025                # Internal integration timestep to use
simConfig.verbose = False           # Show detailed messages
simConfig.recordTraces = {'V_soma':{'sec':'soma','loc':0.5,'var':'v'}}  # Dict with traces to record
simConfig.recordStep = 1            # Step size in ms to save data (eg. V traces, LFP, etc)
simConfig.filename = 'model_output' # Set file output name
simConfig.savePickle = False        # Save params, network and sim output to pickle file

simConfig.analysis['plotRaster'] = {'syncLines': True, 'saveFig': True}      # Plot a raster
simConfig.analysis['plotTraces'] = {'include': [1], 'saveFig': True}         # Plot recorded traces for this list of cells
simConfig.analysis['plot2Dnet'] = {'saveFig': True}         
