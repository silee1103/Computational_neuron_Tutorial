from neuron import h, rxd

dend = h.Section(name="dend")
cyt = rxd.Region(h.allsec(), nrn_region="i")

cl = rxd.Species(cyt, initial=1, name="cl", charge=-1)
ca = rxd.Species(cyt, initial=1, name="ca", charge=2)
cacl2 = rxd.Species(cyt, initial=0, name="cacl2")

reaction = rxd.Reaction(2 * cl + ca, cacl2, 1)

h.finitialize(-65)

heading = "{t:>10s}  {cl:>10s}  {ca:>10s}  {cacl2:>10s}"
data = "{t:10g}  {cl:10g}  {ca:10g}  {cacl2:10g}"


def advance_a_bit():
    for i in range(5):
        h.fadvance()
        print(
            data.format(
                t=h.t,
                cl=cl.nodes[0].concentration,
                ca=ca.nodes[0].concentration,
                cacl2=cacl2.nodes[0].concentration,
            )
        )


print(heading.format(t="t", cl="cl", ca="ca", cacl2="CaCl2"))
print(heading.format(t="-", cl="--------", cacl2="--------", ca="--------"))

advance_a_bit()

# increase the forward reaction rate
reaction.f_rate *= 5

print()
print("---- cacl2 production rate should speed up below here ----")
print()

advance_a_bit()