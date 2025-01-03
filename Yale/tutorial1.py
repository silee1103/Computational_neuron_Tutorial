### MAKE NEURON and Firing

# Packages
from neuron import h
from neuron.units import ms, mV, µm
import random
import matplotlib.pyplot as plt
import numpy as np
# from neuron import gui

# ========================================================================

# Define neuron
MAX_GID = 100
h.load_file("stdrun.hoc")

class BallAndStick:
    def __init__(self, gid = random.randint(0,MAX_GID)):
        self._gid = gid
        self._setup_morphology()
        self._setup_biophysics()

    def _setup_morphology(self):
        self.soma = h.Section(name="soma", cell=self)
        self.dend = h.Section(name="dend", cell=self)
        self.dend.connect(self.soma)
        
        self.all = self.soma.wholetree()

        self.soma.L = self.soma.diam = 12.6157 * µm
        self.dend.L = 200 * µm
        self.dend.diam = 1 * µm

    def _setup_biophysics(self):
        for sec in self.all:
            sec.Ra = 100  # Axial resistance in Ohm * cm
            sec.cm = 1  # Membrane capacitance in micro Farads / cm^2

        self.soma.insert("hh")
        for seg in self.soma:
            seg.hh.gnabar = (
                0.12  # Sodium conductance in S/cm2
            )
            seg.hh.gkbar = (
                0.036  # Potassium conductance in S/cm2
            )
            seg.hh.gl = 0.0003  # Leak conductance in S/cm2
            seg.hh.el = (
                -54.3 * mV
            )  # Reversal potential

        # Insert passive current in the dendrite
        self.dend.insert("pas")
        for seg in self.dend:
            seg.pas.g = 0.001  # Passive conductance in S/cm2
            seg.pas.e = -65 * mV  # Leak reversal potential


    def __repr__(self):
        return "BallAndStick[{}]".format(self._gid)

my_cell_1 = BallAndStick(1)

# print(h.units("gnabar_hh"))

# for sec in h.allsec():
#     print("%s: %s" % (sec, ", ".join(sec.psection()["density_mechs"].keys())))

def plot():
    ps = h.PlotShape(True)  # True를 통해 시각화 활성화
    ps.show(0)  # 섹션 색상 등 GUI 창 표시

# ========================================================================

# Stimulation

# define stimulation
stim = h.IClamp(my_cell_1.dend(1))

print(stim.get_segment())


print(", ".join(item for item in dir(stim) if not item.startswith("__")))

stim.delay = 5
stim.dur = 1
stim.amp = 0.1


# recording - membrane potentail at the centor of soma and time in two Vector
soma_v = h.Vector().record(my_cell_1.soma(0.5)._ref_v)
t = h.Vector().record(h._ref_t)


# plot - membrane potential vs time:

# h.finitialize(-65 * mV)
# h.continuerun(25 * ms)

# t_array = np.array(t)
# soma_v_array = np.array(soma_v)


# # Plot using Matplotlib
# plt.figure(figsize=(8, 4))
# plt.plot(t_array, soma_v_array, label="Soma(0.5)", color="blue", linewidth=2)
# plt.title("Membrane Potential vs Time")
# plt.xlabel("Time (ms)")
# plt.ylabel("Membrane Potential (mV)")
# plt.legend(loc="best")
# plt.grid(True)
# plt.tight_layout()

# # Show the plot
# plt.show()


# plot - membrane potential vs time with many amplituded stimulus:

# Define stimulation amplitudes and colors

# plot + dendrite:
dend_v = h.Vector().record(my_cell_1.dend(0.5)._ref_v)


amps = [0.075 * i for i in range(1, 5)]
colors = ["green", "blue", "red", "black"]

# Prepare the plot
plt.figure(figsize=(10, 6))

# Simulate and plot for each amplitude
for amp, color in zip(amps, colors):
    stim.amp = amp
    
    for nseg, width in [(1, 2), (101, 1)]:
        my_cell_1.dend.nseg = nseg
        h.finitialize(-65 * mV)
        h.continuerun(25 * ms)
    
        # Convert hoc.Vector to numpy array for plotting
        t_array = np.array(t)
        soma_v_array = np.array(soma_v)
        
        # Plot the results
        label = f"Soma amp={amp:.3g}" if nseg == 1 else None
        plt.plot(
            t_array, 
            soma_v_array, 
            label=label, 
            color=color, 
            linewidth=width,
            linestyle="solid"
        )
        
        # plot + dendrite:
        dend_v_array = np.array(dend_v)
        plt.plot(
            t_array,
            dend_v_array,
            label=f"Dendrite amp={amp:.3f}",
            color=color,
            linewidth=2,
            linestyle="dashed"
        )


# Customize the plot
plt.title("Membrane Potential for Different Stimulus Amplitudes")
plt.xlabel("Time (ms)")
plt.ylabel("Membrane Potential (mV)")
plt.legend(loc="best")
plt.grid(True)
plt.tight_layout()

# Show the plot
plt.show()


# ========================================================================
 

# # Prevent script termination
input("Press Enter to exit...")
