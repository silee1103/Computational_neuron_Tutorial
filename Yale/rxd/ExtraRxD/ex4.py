from neuron import h, crxd as rxd

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


from matplotlib import pyplot, animation
from IPython.display import HTML

# use a large timestep as this model only has slow diffusive dynamics.
h.dt = 20

# Create an animation of average (over depth) of the concentrations
def runsim(species, min_conc=3, max_conc=4, frames=1000, output_file='..'):
    h.finitialize()
    fig = pyplot.figure()
    im = pyplot.imshow(species[ecs].states3d.mean(2), vmin=min_conc, vmax=max_conc)
    pyplot.axis("off")

    def init():
        im.set_data(species[ecs].states3d.mean(2))
        return [im]

    def animate(i):
        h.fadvance()
        im.set_data(species[ecs].states3d.mean(2))
        return [im]

    anim = animation.FuncAnimation(
        fig, animate, init_func=init, frames=frames, interval=10
    )
    anim.save(output_file, fps=30, writer="ffmpeg")
    print(f"Animation saved as {output_file}")
    ret = HTML(anim.to_html5_video())
    pyplot.close()
    return ret


# Extracellular reactions
from neuron.crxd import rxdmath

kb = 0.0008
kth = 15.0
kf = kb / (1.0 + rxdmath.exp(-(k - kth) / 1.15))
Bmax = 10

A = rxd.Species(ecs, name="buffer", charge=1, d=0, initial=Bmax)
AK = rxd.Species(ecs, name="bound", charge=1, d=0, initial=0)

buffering = rxd.Reaction(k + A, AK, kf, kb)


runsim(AK, min_conc=0, max_conc=0.01, output_file="concentration_animation_w_reactions.mp4")