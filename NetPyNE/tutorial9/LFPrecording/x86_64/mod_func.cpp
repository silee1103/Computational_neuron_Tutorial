#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _IC_reg(void);
extern void _cadad_reg(void);
extern void _cagk_reg(void);
extern void _cal_mig_reg(void);
extern void _can_mig_reg(void);
extern void _cat_mig_reg(void);
extern void _h_kole_reg(void);
extern void _h_migliore_reg(void);
extern void _ican_sidi_reg(void);
extern void _kBK_reg(void);
extern void _kap_BS_reg(void);
extern void _kdmc_BS_reg(void);
extern void _kdr_BS_reg(void);
extern void _nax_BS_reg(void);
extern void _savedist_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"mod/IC.mod\"");
    fprintf(stderr, " \"mod/cadad.mod\"");
    fprintf(stderr, " \"mod/cagk.mod\"");
    fprintf(stderr, " \"mod/cal_mig.mod\"");
    fprintf(stderr, " \"mod/can_mig.mod\"");
    fprintf(stderr, " \"mod/cat_mig.mod\"");
    fprintf(stderr, " \"mod/h_kole.mod\"");
    fprintf(stderr, " \"mod/h_migliore.mod\"");
    fprintf(stderr, " \"mod/ican_sidi.mod\"");
    fprintf(stderr, " \"mod/kBK.mod\"");
    fprintf(stderr, " \"mod/kap_BS.mod\"");
    fprintf(stderr, " \"mod/kdmc_BS.mod\"");
    fprintf(stderr, " \"mod/kdr_BS.mod\"");
    fprintf(stderr, " \"mod/nax_BS.mod\"");
    fprintf(stderr, " \"mod/savedist.mod\"");
    fprintf(stderr, "\n");
  }
  _IC_reg();
  _cadad_reg();
  _cagk_reg();
  _cal_mig_reg();
  _can_mig_reg();
  _cat_mig_reg();
  _h_kole_reg();
  _h_migliore_reg();
  _ican_sidi_reg();
  _kBK_reg();
  _kap_BS_reg();
  _kdmc_BS_reg();
  _kdr_BS_reg();
  _nax_BS_reg();
  _savedist_reg();
}

#if defined(__cplusplus)
}
#endif
