from neuron import h, rxd
import matplotlib.pyplot as plt
from neuron.units import ms, mV, µm

h.load_file("stdrun.hoc")

# where
soma = h.Section(name="soma")
cyt = rxd.Region([soma], nrn_region="i")
# who
ca = rxd.Species(cyt, name="ca", charge=2, initial=1e-4)
buf = rxd.Species(cyt, name="buf", initial=1e-4)
cabuf = rxd.Species(cyt, name="cab2uf", initial=0)
# what
buffering = rxd.Reaction(2 * ca + buf, cabuf, 1e6, 1e-2)
degradation = rxd.Rate(buf, -1e-3 * buf)

t = h.Vector()
ca_vec = h.Vector()
buf_vec = h.Vector()
t.record(h._ref_t)
ca_vec.record(soma(0.5)._ref_cai)
buf_vec.record(soma(0.5)._ref_bufi)


# Run the simulation
h.finitialize(-65)
h.continuerun(100 * ms)

# Plot the recorded values
plt.figure(figsize=(10, 6))

# Plot calcium concentration
plt.plot(t, ca_vec, label="Calcium [ca]", color="blue")

# Plot buffer concentration
plt.plot(t, buf_vec, label="Buffer [buf]", color="green")

# Add labels and legend
plt.xlabel("Time (ms)")
plt.ylabel("Concentration (mM)")
plt.title("Calcium and Buffer Concentrations Over Time")
plt.legend()
plt.grid()

# Show the plot
plt.show()