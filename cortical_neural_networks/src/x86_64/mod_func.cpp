#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _CustomAlphaSynapse_reg(void);
extern void _RefractoryNeuron_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"CustomAlphaSynapse.mod\"");
    fprintf(stderr, " \"RefractoryNeuron.mod\"");
    fprintf(stderr, "\n");
  }
  _CustomAlphaSynapse_reg();
  _RefractoryNeuron_reg();
}

#if defined(__cplusplus)
}
#endif
