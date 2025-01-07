from neuron import h, crxd as rxd
from matplotlib import pyplot, animation

rxd.options.enable.extracellular = True

rxd.nthread(4)


h.load_file("stdrun.hoc")
h.load_file("import3d.hoc")


class Cell:
    def __init__(self, filename):
        """Read geometry from a given SWC file and create a cell with a K+ source"""
        cell = h.Import3d_SWC_read()
        cell.input(filename)
        h.Import3d_GUI(cell, 0)
        i3d = h.Import3d_GUI(cell, 0)
        i3d.instantiate(self)
        for sec in self.all:
            sec.nseg = 1 + 10 * int(sec.L / 5)
            sec.insert("steady_k")

    def extrema(self):
        """Give the bounding box that contains the cell"""
        xlo = ylo = zlo = xhi = yhi = zhi = None
        for sec in self.all:
            n3d = sec.n3d()
            xs = [sec.x3d(i) for i in range(n3d)]
            ys = [sec.y3d(i) for i in range(n3d)]
            zs = [sec.z3d(i) for i in range(n3d)]
            my_xlo, my_ylo, my_zlo = min(xs), min(ys), min(zs)
            my_xhi, my_yhi, my_zhi = max(xs), max(ys), max(zs)
            if xlo is None:
                xlo, ylo, zlo = my_xlo, my_ylo, my_zlo
                xhi, yhi, zhi = my_xhi, my_yhi, my_zhi
            else:
                xlo, ylo, zlo = min(xlo, my_xlo), min(ylo, my_ylo), min(zlo, my_zlo)
                xhi, yhi, zhi = max(xhi, my_xhi), max(yhi, my_yhi), max(zhi, my_zhi)
        return (xlo, ylo, zlo, xhi, yhi, zhi)

mycell = Cell("c91662.swc")

xlo, ylo, zlo, xhi, yhi, zhi = mycell.extrema()
padding = 50
ecs = rxd.Extracellular(
    xlo - padding,
    ylo - padding,
    zlo - padding,
    xhi + padding,
    yhi + padding,
    zhi + padding,
    dx=(20, 20, 50),
    volume_fraction=0.2,
    tortuosity=1.6,
)

k = rxd.Species(ecs, d=2.62, name="k", charge=1, initial=3)


# record from an extracellular nodes given by the x,y,z location
kecs_vec0 = h.Vector()
kecs_vec0.record(
    k[ecs].node_by_location(0, 0, 0)._ref_value
)  # same as k[ecs].node_by_ijk(20,15,7)

# record the same node by it's index into stated3d
kecs_vec1 = h.Vector()
kecs_vec1.record(
    k[ecs].node_by_ijk(22, 15, 7)._ref_value
)  # same as k[ecs].node_by_location(50,0,0)

# record the time
t_vec = h.Vector()
t_vec.record(h._ref_t)

# run the simulation
h.finitialize()
h.continuerun(2000)

# plot the concentations
pyplot.plot(t_vec, kecs_vec0, label="near the cell")
pyplot.plot(t_vec, kecs_vec1, label="far from the cell")

pyplot.xlabel("Time (ms)")
pyplot.ylabel("Concentration (mM)")
pyplot.legend()
pyplot.title("Extracellular K+ Concentration Over Time")
pyplot.savefig("extracellular_k_concentration.png", dpi=300)  # Save the plot
pyplot.show()
