sigmoid for a_in -> alpha
linear for sigma_in -> sigma_out
sigma_in > sigma_out -> syn!
bg noise activity -> neuron response variability

each neuron responds to an incoming pulse packet with at most one spike

For a group of identical independent neurons,
the distribution of response spikes to an input pulse packet
is identical to the response distribution for a single neuron

Thus, the spread of the group's response 
equals the single neuron's response dispersion sigma_out

The expected number of response spikes a_out in a group equals alpha * group size w

relationship between input and output jitter (a = 65, j = 1.2 ms).

This lower bound is essentially determined by the ratio of the distance
from mean membrane potential to spike threshold
and the postsynaptic potential (PSP) amplitude;
stronger intergroup synapses reduce this number (see Methods: Fluctuations).


############################################################################
synapses delivering activity from the preceding group
and the synapses delivering background activity were set at equal strength

Each neuron in a group contributes a single spike to the passing volley.

Once the neuron recovers from refractoriness, it is ready to engage in another group

Thus, each neuron may participate in multiple volleys with different neuron compositions,
- spike by spike, not limited by a specific arrangement of synaptic weights-
provided its engagements differ by more than the refractory period

enough neurons must be recruited in successive groups to generate new spike group.

network only needs to be locally feed forward

Several such volleys may propagate through the network simultaneously,
allowing multiple synchronous processes to coexist
while maintaining their identities