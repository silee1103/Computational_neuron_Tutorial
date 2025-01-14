NEURON {
    POINT_PROCESS CustomAlphaSynapse
    RANGE tau, e, gmax, i, peak_time, half_width
    RANGE abs_ref, rel_ref, refractory, relative_factor
    NONSPECIFIC_CURRENT i
}

UNITS {
    (mV) = (millivolt)
    (nA) = (nanoamp)
    (uS) = (microsiemens)
}

PARAMETER {
    tau = 1.7 (ms)       : Time constant for alpha function
    e = 0 (mV)           : Reversal potential
    gmax = 0.14 (uS)     : Peak conductance
    peak_time = 1.7 (ms) : Time to peak
    half_width = 8.5 (ms): Approximate half-width
    abs_ref = 1.0 (ms)   : Absolute refractory period
    rel_ref = 15.0 (ms)  : Relative refractory period
}

ASSIGNED {
    v (mV)               : Membrane potential
    i (nA)               : Current
    g (uS)               : Conductance
    factor               : Scaling factor to ensure peak amplitude
}

STATE {
    A (uS)               : Alpha function conductance
    refractory (ms)      : Timer for absolute refractory period
    relative_factor      : Modulation factor for relative refractoriness
}

INITIAL {
    A = 0
    refractory = 0
    relative_factor = 0
    factor = calculate_factor(tau, gmax) : Precompute scaling factor
}

BREAKPOINT {
    SOLVE state METHOD cnexp
    g = A * (1 - relative_factor)        : Modulate conductance by relative refractoriness
    i = g * (v - e)                      : Compute current
}

DERIVATIVE state {
    A' = -A / tau                        : Exponential decay of conductance
    refractory' = -1 / abs_ref           : Decay refractory period
    relative_factor' = -relative_factor / rel_ref : Gradual recovery from relative refractoriness
}

NET_RECEIVE(weight (uS)) {
    if (refractory <= 0) {               : Check if neuron is in refractory period
        refractory = abs_ref             : Set absolute refractory timer
        relative_factor = 1              : Maximize relative refractoriness
        A = A + weight                   : Increment conductance
    }
}

FUNCTION calculate_factor(tau (ms), gmax (uS)) {
    LOCAL peak_value
    peak_value = tau * exp(-1)           : Alpha function peak occurs at t = tau
    calculate_factor = gmax / peak_value : Scale such that gmax corresponds to peak
}
