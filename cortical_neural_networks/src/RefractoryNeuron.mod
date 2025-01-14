COMMENT

A mechanism to simulate a leaky-integrator neuron with absolute and relative refractory periods.
The model dynamically adjusts the threshold during the relative refractory period and blocks spiking during the absolute refractory period.

ENDCOMMENT

NEURON {
    POINT_PROCESS RefractoryNeuron
    RANGE thresh, abs_refrac, rel_refrac, rel_factor, tau, v, alive
    NONSPECIFIC_CURRENT i
}

UNITS {
    (mV) = (millivolt)
}

PARAMETER {
    thresh = -55 (mV)         : Resting spike threshold
    abs_refrac = 1 (ms)       : Absolute refractory period duration
    rel_refrac = 15 (ms)      : Relative refractory period duration
    rel_factor = 10 (mV)      : Increase in threshold during relative refractory
    tau = 10 (ms)             : Membrane time constant
    alive = 1                 : Neuron is alive (1 = true, 0 = dead)
}

ASSIGNED {
    v (mV)                   : Membrane potential
    i (nA)                   : Output current
    current_thresh (mV)      : Dynamic threshold
    dt (ms)                  : Simulation time step
    t0 (ms)                  : Time of last spike
    state                    : Refractory state (0 = none, 1 = absolute, 2 = relative)
}

INITIAL {
    v = -70
    current_thresh = thresh
    t0 = -1e9                : Initialize to a large negative value to prevent early firing
    state = 0                : No refractory period initially
}

BREAKPOINT {
    if (state == 1) {                      : Absolute refractory period
        current_thresh = 1e9               : Block spiking by setting a high threshold
        if (t - t0 >= abs_refrac) {
            state = 2                      : Switch to relative refractory
            current_thresh = thresh + rel_factor
        }
    } else if (state == 2) {               : Relative refractory period
        current_thresh = thresh + rel_factor * exp(-(t - t0 - abs_refrac) / rel_refrac)
        if (t - t0 >= abs_refrac + rel_refrac) {
            state = 0                      : Exit refractory period
            current_thresh = thresh
        }
    }

    i = calculate_current()
}

NET_RECEIVE(weight (nA)) {
    if (alive && v > current_thresh) {     : Check if the neuron is alive and threshold is crossed
        net_event(t)                       : Emit a spike event
        v = -70                            : Reset membrane potential
        t0 = t                             : Update the time of the last spike
        state = 1                          : Enter absolute refractory period
    }
}

FUNCTION calculate_current() {
    if (state == 1) {                      : No current during absolute refractory
        calculate_current = 0
    } else {
        calculate_current = (v - current_thresh) / tau
    }
}
