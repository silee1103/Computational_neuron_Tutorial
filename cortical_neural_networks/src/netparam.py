from netpyne.specs import NetParams

netParams = NetParams()

# Define cell parameters
PYRcell = {'secs': {}}
PYRcell['secs']['soma'] = {
    'geom': {'diam': 20, 'L': 20, 'Ra': 150},
    'mechs': {
        'leak': {'g': 1/10, 'e': -70, 'tau': 10},
        'k': {'gk': 0.01, 'ek': -80}
    },
    'threshold': -55
}
PYRcell['secs']['soma']['vinit'] = -70
netParams.cellParams['PYR'] = PYRcell

# Define layers and populations
num_layers = 10
for layer in range(num_layers):
    layer_label = f'L{layer}'
    netParams.popParams[f'E_{layer_label}'] = {'cellType': 'PYR', 'numCells': 80}
    netParams.popParams[f'I_{layer_label}'] = {'cellType': 'PYR', 'numCells': 20}

# Define synapse mechanisms
netParams.synMechParams['exc'] = {'mod': 'CustomAlphaSynapse', 'tau': 1.7, 'e': 0, 'gmax': 0.14}
netParams.synMechParams['inh'] = {'mod': 'CustomAlphaSynapse', 'tau': 1.7, 'e': -80, 'gmax': 0.14}

# Background input
netParams.stimSourceParams['backgroundE'] = {'type': 'NetStim', 'rate': 2, 'noise': 0.5}
netParams.stimSourceParams['backgroundI'] = {'type': 'NetStim', 'rate': 12.5, 'noise': 0.5}

# Add background stimulation to E/I neurons in all layers
for layer in [range(num_layers)]:
    layer_label = f'L{layer}'
    netParams.stimTargetParams[f'bgE->{layer_label}'] = {
        'source': 'backgroundE',
        'conds': {'pop': f'E_{layer_label}'},
        'sec': 'soma',
        'loc': 0.5,
        'synMech': 'exc'
    }
    netParams.stimTargetParams[f'bgI->{layer_label}'] = {
        'source': 'backgroundI',
        'conds': {'pop': f'I_{layer_label}'},
        'sec': 'soma',
        'loc': 0.5,
        'synMech': 'inh'
    }

# # Add a strong pulse packet to Layer 0
# netParams.stimSourceParams['strongPulsePacket'] = {
#     'type': 'NetStim',
#     'start': 10,       # Start earlier for strong initiation
#     'interval': 1,     # Short interval for frequent spiking
#     'number': 20,      # Larger number of spikes
#     'noise': 0         # Deterministic spiking (no noise)
# }

# netParams.stimTargetParams['strongPulse->L0'] = {
#     'source': 'strongPulsePacket',
#     'conds': {'pop': 'E_L0'},
#     'sec': 'soma',
#     'loc': 0.5,
#     'synMech': 'exc',
#     'weight': 0.1      # High weight for strong input
# }

# Add a pulse packet to the first layer to initiate spiking
netParams.stimSourceParams['pulsePacket'] = {
    'type': 'NetStim',
    'start': 50,
    'interval': 1,
    'number': 10,
    'noise': 0
}
netParams.stimTargetParams['pulse->L0'] = {
    'source': 'pulsePacket',
    'conds': {'pop': 'E_L0'},
    'sec': 'soma',
    'loc': 0.5,
    'synMech': 'exc'
}


# Define intra-layer connections (E->E, I->E)
for layer1 in range(num_layers):
    for layer2 in range(num_layers):
        layer_label1 = f'L{layer1}'
        layer_label2 = f'L{layer2}'
        # Excitatory to Excitatory
        netParams.connParams[f'E_{layer_label1}->E_{layer_label2}'] = {
            'preConds': {'pop': f'E_{layer_label1}'},
            'postConds': {'pop': f'E_{layer_label2}'},
            'probability': 0.02,
            'weight': 0.001,
            'delay': 'normal(5, 1)',
            'synMech': 'exc',
            'sec': 'soma',
            'loc': 0.5
        }
        # Inhibitory to Excitatory
        netParams.connParams[f'I_{layer_label1}->E_{layer_label1}'] = {
            'preConds': {'pop': f'I_{layer_label1}'},
            'postConds': {'pop': f'E_{layer_label2}'},
            'probability': 0.02,
            'weight': 0.002,
            'delay': 'normal(5, 1)',
            'synMech': 'inh',
            'sec': 'soma',
            'loc': 0.5
        }

# Define inter-layer connections (E->E for spike propagation)
for layer in range(num_layers - 1):  # Connect only up to the second last layer
    source_layer = f'L{layer}'
    target_layer = f'L{layer + 1}'
    
    netParams.connParams[f'I_{source_layer}->E_{target_layer}'] = {
        'preConds': {'pop': f'I_{source_layer}'},
        'postConds': {'pop': f'E_{target_layer}'},
        'probability': 0.05,  # Higher probability for inter-layer propagation
        'weight': 0.05,
        'delay': 'normal(5, 1)',
        'synMech': 'exc',
        'sec': 'soma',
        'loc': 0.5
    }

    netParams.connParams[f'E_{source_layer}->I_{target_layer}'] = {
        'preConds': {'pop': f'E_{source_layer}'},
        'postConds': {'pop': f'I_{target_layer}'},
        'probability': 0.05,  # Higher probability for inter-layer propagation
        'weight': 0.05,
        'delay': 'normal(5, 1)',
        'synMech': 'exc',
        'sec': 'soma',
        'loc': 0.5
    }

    netParams.connParams[f'I{source_layer}_to_{target_layer}'] = {
        'preConds': {'pop': f'I_{source_layer}'},
        'postConds': {'pop': f'I_{target_layer}'},
        'probability': 0.05,  # Higher probability for inter-layer propagation
        'weight': 0.05,
        'delay': 'normal(5, 1)',
        'synMech': 'exc',
        'sec': 'soma',
        'loc': 0.5
    }
    

    netParams.connParams[f'E->{source_layer}_to_{target_layer}'] = {
        'preConds': {'pop': f'E_{source_layer}'},
        'postConds': {'pop': f'E_{target_layer}'},
        'probability': 0.05,  # Higher probability for inter-layer propagation
        'weight': 0.05,
        'delay': 'normal(5, 1)',
        'synMech': 'exc',
        'sec': 'soma',
        'loc': 0.5
    }
    
