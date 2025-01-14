from netpyne.specs import SimConfig

# 시뮬레이션 파라미터
cfg = SimConfig()


cfg.duration = 1000  # ms
cfg.dt = 0.1  # ms
cfg.verbose = True
cfg.recordTraces = {'V_soma': {'sec': 'soma', 'loc': 0.5, 'var': 'v'}}
cfg.recordStep = 0.1
cfg.saveJson = True
cfg.recordSpikes = True  # Enable spike recording
cfg.analysis['plotTraces'] = {'include': [0], 'ylim': [-80, 50]}

cfg.analysis['plotRaster'] = {'saveFig': True}                   # Plot a raster
cfg.analysis['plotTraces'] = {'include': [0], 'saveFig': True}  # Plot recorded traces for this list of cells
# cfg.analysis['plot2Dnet'] = {'saveFig': True}                   # plot 2D cell positions and connections

cfg.saveDataInclude = ['simData', 'simConfig', 'netParams', 'net']
