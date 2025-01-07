from neuron import h, rxd
import numpy
from matplotlib import pyplot

# needed for standard run system
h.load_file("stdrun.hoc")

dend = h.Section(name="dend")
dend.nseg = 101

# initial conditions
def my_initial(node):
    return 1 if node.x < 0.2 else 0


# WHERE the dynamics will take place
where = rxd.Region([dend])

# WHO the actors are
u = rxd.Species(where, d=1, initial=my_initial)

# HOW they act
bistable_reaction = rxd.Rate(u, -u * (1 - u) * (0.3 - u))

# initial conditions
h.finitialize(-65)


def plot_it(color="k"):
    y = u.nodes.concentration
    x = u.nodes.x

    # convert x from normalized position to microns
    x = dend.L * numpy.array(x)

    pyplot.plot(x, y, color)


plot_it("r")

for i in range(1, 5):
    h.continuerun(i * 25)
    plot_it()

pyplot.xlabel("t (ms)")
pyplot.ylabel("[u] (mM)")
pyplot.show()