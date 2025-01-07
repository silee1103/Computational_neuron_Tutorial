from neuron import h, crxd as rxd

h.load_file("stdrun.hoc")

dend = h.Section(name="dend")
dend.L = 100
dend.nseg = 101

def my_initial(node):
    if 0.4 < node.segment.x < 0.6:
        return 1
    else:
        return 0

cyt = rxd.Region(h.allsec(), name="cyt", nrn_region="i")
ip3 = rxd.Species(cyt, name="ip3", d=1, initial=my_initial)

from matplotlib import pyplot


def plot_it():
    xs = [seg.x * dend.L for seg in dend]
    ys = [seg.ip3i for seg in dend]
    pyplot.plot(xs, ys)

h.finitialize(-65)
for tstop in [0, 50, 100, 150]:
    h.continuerun(tstop)
    plot_it()
pyplot.xlabel("x (µm)")
pyplot.ylabel("[IP3]")

pyplot.show()

nM = 1e-6  # relative to NEURON's default mM

h.finitialize(-65)
while dend(0.7).ip3i < 100 * nM:
    h.fadvance()

print("crossed 100 nM at t = {} ms".format(h.t))

ip3_vec = h.Vector()
ip3_vec.record(dend(0.7)._ref_ip3i)
t_vec = h.Vector()
t_vec.record(h._ref_t)

h.finitialize(-65)
h.continuerun(1000)
max_ip3 = max(ip3_vec)
print("peak ip3 =", max_ip3)
print("final ip3 =", dend(0.7).ip3i)

