# make gruops (inhibitory / excitory) - and make them spatially separated
# X (horiaental), Z (lateral) is plane / Y is depth (vertical)


from netpyne import specs, sim

# Network parameters
netParams = specs.NetParams()  # object of class NetParams to store the network parameters

# make 100x100 um (horizental) x1000um (vertical) cuboid
netParams.sizeX = 100             # x-dimension (horizontal length) size in um
netParams.sizeY = 1000            # y-dimension (vertical height or cortical depth) size in um
netParams.sizeZ = 100             # z-dimension (horizontal length) size in um
netParams.propVelocity = 100.0    # propagation velocity (um/ms) - 호가 축삭(axon)을 따라 전파되는 속도
netParams.probLengthConst = 150.0 # length constant for conn probability (um) 
                                  # 멀수록 낮아짐... 두 뉴런 간 거리(distance)가 연결 확률(connection probability)에 미치는 영향을 정의

secs = {}

secs['soma'] = {'geom': {}, 'mechs':{}}
secs['soma']['geom'] = {'diam': 15.0, 'L': 14.0, 'Ra': 120.0}
secs['soma']['mechs']['hh'] = {'gnabar': 0.13, 'gkbar': 0.036, 'gl': 0.003, 'el': -70}

netParams.cellParams['E'] = {'secs': secs}

secs = {}

secs['soma'] = {'geom': {}, 'mechs':{}}
secs['soma']['geom'] = {'diam': 10.0, 'L': 9.0, 'Ra': 110.0}
secs['soma']['mechs']['hh'] = {'gnabar': 0.11, 'gkbar': 0.036, 'gl': 0.003, 'el': -70}

netParams.cellParams['I'] = {'secs': secs}

netParams.popParams['E2'] = {'cellType': 'E', 'numCells': 50, 'yRange':[100,300]}
netParams.popParams['I2'] = {'cellType': 'I', 'numCells': 50, 'yRange':[100,300]}
netParams.popParams['E4'] = {'cellType': 'E', 'numCells': 50, 'yRange':[300,600]}
netParams.popParams['I4'] = {'cellType': 'I', 'numCells': 50, 'yRange':[300,600]}
netParams.popParams['E5'] = {'cellType': 'E', 'numCells': 50, 'ynormRange':[0.6,1.0]}
netParams.popParams['I5'] = {'cellType': 'I', 'numCells': 50, 'ynormRange':[0.6,1.0]}


## Synaptic mechanism parameters (tau1: rise time / tau2: decay time)
netParams.synMechParams['exc'] = {'mod': 'Exp2Syn', 'tau1': 0.8, 'tau2': 5.3, 'e': 0}  # excitatory synaptic mechanism
netParams.synMechParams['inh'] = {'mod': 'Exp2Syn', 'tau1': 0.6, 'tau2': 8.5, 'e': -75}  # inhibitory synaptic mechanism

netParams.stimSourceParams['bkg'] = {'type': 'NetStim', 'rate': 20, 'noise': 0.3}
netParams.stimTargetParams['bkg->all'] = {'source': 'bkg', 'conds': {'cellType': ['E','I']}, 'weight': 0.01, 'delay': 'max(1, normal(5,2))', 'synMech': 'exc'}

## cell connectivity rules
netParams.connParams['E->all'] = {
        'preConds': {'cellType': 'E'}, 'postConds': {'y': [100,1000]},  #  E -> all (100-1000 um)
        'probability': 0.1 ,                  # probability of connection
        'weight': '0.005*post_ynorm',         # synaptic weight
        'delay': 'dist_3D/propVelocity',      # transmission delay (ms)
        'synMech': 'exc'                      # synaptic mechanism
}

# netParams.connParams['I->E'] = {                          # I -> E
#         'preConds': {'cellType': 'I'},                        # presynaptic conditions
#         'postConds': {'pop': ['E2','E4','E5']},               # postsynaptic conditions
#         'probability': '0.4*exp(-dist_3D/probLengthConst)',   # probability of connection
#         'weight': 0.001,                                      # synaptic weight
#         'delay': 'dist_3D/propVelocity',                      # transmission delay (ms)
#         'synMech': 'inh'                                      # synaptic mechanism
# }

# Simulation options
simConfig = specs.SimConfig()       # object of class SimConfig to store simulation configuration

simConfig.duration = 1*1e3          # Duration of the simulation, in ms
simConfig.dt = 0.025                 # Internal integration timestep to use - simulation 계산 주기기
simConfig.verbose = False           # Show detailed messages
simConfig.recordTraces = {'V_soma':{'sec':'soma','loc':0.5,'var':'v'}}  # Dict with traces to record
simConfig.recordStep = 1          # Step size in ms to save data (e.g. V traces, LFP, etc)
simConfig.filename = 'tut5'         # Set file output name
simConfig.savePickle = False        # Save params, network and sim output to pickle file

simConfig.analysis['plotRaster'] = {'orderBy': 'y', 'orderInverse': True, 'saveFig': True}         # Plot a raster
simConfig.analysis['plotTraces'] = {'include': [('E2',0), ('E4', 0), ('E5', 5)], 'saveFig': True}  # Plot recorded traces for this list of cells
simConfig.analysis['plot2Dnet'] = {'saveFig': True}                                                # plot 2D cell positions and connections
# simConfig.analysis['plotConn'] = {'saveFig': True}