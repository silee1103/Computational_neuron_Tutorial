from neuron import h, rxd
from neuron.units import mV, ms, um, mM

import plotly.graph_objects as go

## needed for standard run system
h.load_file("stdrun.hoc")

left = h.Section(name="left")
right = h.Section(name="right")

left.nseg = right.nseg = 101
left.L = right.L = 101

right.connect(left)

cytosol = rxd.Region(left.wholetree())


def initial_protein(node):
    if 90 * um < h.distance(node, left(0)) < 110 * um:
        return 1 * mM
    else:
        return 0

protein = rxd.Species(cytosol, d=1, initial=initial_protein)

def active_region_value(node):
    if node in right:
        return 1
    else:
        return 0
    
in_region = rxd.Parameter(cytosol, value=active_region_value)

production_rate = 0.002 * mM / ms

reaction = rxd.Rate(protein, production_rate * in_region)

h.finitialize(-65 * mV)

def plot(fig):
    y = protein.nodes.concentration
    x = [h.distance(node, left(0)) for node in protein.nodes]
    fig.add_trace(go.Scatter(x=x, y=y, name=f"t = {h.t:g} ms"))



fig = go.Figure()
plot(fig)

for advance_count in range(1, 5):
    h.continuerun(advance_count * 25 * ms)
    plot(fig)

fig.update_layout(xaxis_title="Position (µm)", yaxis_title="Concentration (mM)")

# Save the plot to an HTML file (since WSL doesn't display notebooks natively)
fig.write_html("concentration_plot.html")

print("Plot saved to concentration_plot.html. Open it in a browser to view.")