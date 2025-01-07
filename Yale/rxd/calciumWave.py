from neuron import h, rxd
h.load_file("stdrun.hoc")


sec = h.Section(name="sec")
sec.L = 101
sec.diam = 1
sec.nseg = 101

h.CVode().active(True)

caDiff = 0.016
ip3Diff = 0.283
cac_init = 1.0e-4
ip3_init = 0.1
gip3r = 12040
gserca = 0.3913
gleak = 6.020
kserca = 0.1
kip3 = 0.15
kact = 0.4
ip3rtau = 2000
fc = 0.83
fe = 0.17

cyt = rxd.Region(
    h.allsec(),
    nrn_region="i",
    geometry=rxd.FractionalVolume(fc, surface_fraction=1),
    name="cyt",
)


er = rxd.Region(h.allsec(), geometry=rxd.FractionalVolume(fe), name="er")


cyt_er_membrane = rxd.Region(
    h.allsec(), geometry=rxd.DistributedBoundary(2), name="cyt_er_membrane"
)

s = rxd.Species(regions=None, d=0, name=None, charge=0, initial=None, atolscale=1)

caCYT_init = 0.1
ca = rxd.Species([cyt, er], d=caDiff, name="ca", charge=2, initial=caCYT_init)
ip3 = rxd.Species(cyt, d=ip3Diff, initial=ip3_init)
