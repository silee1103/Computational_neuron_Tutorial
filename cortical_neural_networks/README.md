# Methods
## Model neuron
leaky-integrator with voltage-threshold model
### Parameters
#### neuron
- membrane time constant: 10 ms
- resting potential: -70 mV
- spike threshold: -55 mV
- absolute refractoriness: 1 ms
- relative refractoriness: ~= 15 ms (modelled by K conductances)
#### stimulation
- synaptic noise input
#### cortical network + intergroup and background connections
- 20,000 synapses: 88% excitatory, 12% inhibitory
- Postsynaptic currents (PSCs) : alpha-function
    - peak amplitude: 0.14 mV
    - time-to-peak: 1.7 ms
    - half-width: 8.5 ms
- Background firing rates
    - excitatory: 2 Hz
    - inhibitory: 12.5 Hz
    - all uncorrelated stationary Poisson
    == output rate of 2 Hz
    == output statistics were approximately Poisson
    - membrane potential shot noise ~= `balanced' excitation/inhibition
        - mean: 8.25 mV
        - s.d: 2.85 mV
- construction of background fluctuations are not essential
- time steps: 0.1 ms

## Threshold packet
### (ain,aout) curves : cross the diagonal in two point
- output spikes = input spikes가 되는 가장 왼쪽 지점
    = lower bound of minimum input spike number
- Decreasing the group's size
    - rotates the diagonal relative to the (ain,aout) curves counterclockwise around the origin
    - the intersection points approach each other
    - the threshold packet size increases.
    - more curves fall below the diagonal (a_in > a_out)
    - the attractor vanished
    = stable propagation of synchronous spiking is no longer possible.

## Isoclines
- a-isocline: all states for which the spike number in a volley does not change from stage to stage, irrespective of sigma 
- sigma-isocline: all states maintaining temporal spread, irrespective of a

- The sigma-isocline is independent of w
- The spike number is proportional to w
- Hence, with decreasing w, the a-isocline shrinks and moves left until it ceases to exist.
Thus, the group's size w acts as bifurcation parameter, controlling the existence and separation of fixpoints.

## Fluctuations
- evolution of synchronous activity in the mean,
    = subsequent values of the expectation (a,sigma) across trials with different background activity realizations. 
    - Around each point of a trajectory, these realizations form a distribution with width determined by a, sigma, w and intergroup connectivity
    - This width becomes more important near the separatrix because of the increased probability- even for trajectories stable in the mean- that individual realizations leave the basin of attraction (and vice versa)
- Upscaling the synaptic weights by a factor up to 10 while downscaling the groups size accordingly does not alter the structure of the state space, except close to the separatrix where the probability to leave the basin of attraction increases.
- The contribution of individual input spikes grows; consequently, fluctuations in membrane-potential response to pulse-packet realizations with identical parameters and, hence, trial-by-trial variability, increases.

## Background activity
- Background activity in different neurons was considered independent, stationary Poisson.
However, on-going cortical activity is known to exhibit coherent spatio-temporal
structure
- Hence, anatomically nearby neurons within a group tend to be excited (inhibited) together
- This affects the pulse-packet propferties needed to make these neurons fire simultaneously
- The impact of such coherence in background activity is
currently being studied

## Membrane time constantm;
The temporal precision of spike response is not constrained by membrane time constant itself; the limiting factor is the up s lope of the excitatory PSP. The larger this slope, the faster the membrane-potential response to a pulse packet traverses the threshold region17

This reduces the chance of interference with background fluctuations, which degrade
response spike prec


ision. The membrane time constant does, however, limit transmission
of synchronous spikes in the opposite way. It determines the integration time window of
the receiving neuron, limiting the extent over which a spike volley is `seen' as a single
packet, rather than as individual spikes. For a too-small membrane time constant, PSPs no
longer overlap and cannot add up to threshold. Reliable transmission of incompletely
synchronized spike volleys, therefore, requires a minimal (rather than maximal) membrane time constant, in the order of the volley duration.