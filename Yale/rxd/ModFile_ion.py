from neuron import h, rxd
from neuron.units import mV, ms, um, mM

## needed for standard run system
h.load_file("stdrun.hoc")


import plotly.graph_objects as go
from plotly.subplots import make_subplots

## define morphology
soma = h.Section(name="soma")
soma.L = soma.diam = 10 * um

## add ion channels (h.hh is built in, so always available)
h.hh.insert(soma)

## define cytosol. MUST specify nrn_region for concentrations to update
cyt = rxd.Region([soma], name="cyt", nrn_region="i")

## define sodium. MUST specify name and charge for concentrations to update
na = rxd.Species(cyt, name="na", charge=1)

syn = h.ExpSyn(soma(0.5))
syn.tau = 1 * ms
syn.e = 0 * mV

stim = h.NetStim()
stim.interval = 15 * ms
stim.number = 2
stim.start = 10 * ms

nc = h.NetCon(stim, syn)
nc.weight[0] = 0.001

t = h.Vector().record(h._ref_t)
v = h.Vector().record(soma(0.5)._ref_v)
na_vec = h.Vector().record(soma(0.5)._ref_nai)
ina = h.Vector().record(soma(0.5)._ref_ina)


h.finitialize(-65 * mV)
h.continuerun(50 * ms)

fig = make_subplots(rows=3, cols=1)

fig.add_trace(go.Scatter(x=t, y=v, name="v"), row=1, col=1)
fig.update_yaxes(title_text="v (mV)", row=1, col=1)

fig.add_trace(go.Scatter(x=t, y=ina, name="ina"), row=2, col=1)
fig.update_yaxes(title_text="ina (mA/cm^2)", row=2, col=1)

fig.add_trace(go.Scatter(x=t, y=na_vec, name="[Na+]"), row=3, col=1)
fig.update_xaxes(title_text="t (ms)", row=3, col=1)
fig.update_yaxes(title_text="[Na+] (mM)", row=3, col=1)

output_file = "subplots_wsl.html"
fig.write_html(output_file)

print(h.hh.code)

