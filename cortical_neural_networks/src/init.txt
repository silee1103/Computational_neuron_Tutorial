from netpyne import sim

# read cfg and netParams from command line arguments if available; otherwise use default
simConfig, netParams = sim.readCmdLineArgs(simConfigDefault='cfg.py', netParamsDefault='netparam.py')

# Create network and run simulation
sim.createSimulateAnalyze(netParams=netParams, simConfig=simConfig)

# Print recorded spike data
print(sim.allSimData['spkTimes'])  # Should show a list of spike times
print(sim.allSimData['spkInds'])   # Should show a list of spike indices
