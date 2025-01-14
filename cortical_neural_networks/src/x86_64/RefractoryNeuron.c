/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__RefractoryNeuron
#define _nrn_initial _nrn_initial__RefractoryNeuron
#define nrn_cur _nrn_cur__RefractoryNeuron
#define _nrn_current _nrn_current__RefractoryNeuron
#define nrn_jacob _nrn_jacob__RefractoryNeuron
#define nrn_state _nrn_state__RefractoryNeuron
#define _net_receive _net_receive__RefractoryNeuron 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define thresh _p[0]
#define thresh_columnindex 0
#define abs_refrac _p[1]
#define abs_refrac_columnindex 1
#define rel_refrac _p[2]
#define rel_refrac_columnindex 2
#define rel_factor _p[3]
#define rel_factor_columnindex 3
#define tau _p[4]
#define tau_columnindex 4
#define alive _p[5]
#define alive_columnindex 5
#define i _p[6]
#define i_columnindex 6
#define current_thresh _p[7]
#define current_thresh_columnindex 7
#define t0 _p[8]
#define t0_columnindex 8
#define state _p[9]
#define state_columnindex 9
#define v _p[10]
#define v_columnindex 10
#define _g _p[11]
#define _g_columnindex 11
#define _tsav _p[12]
#define _tsav_columnindex 12
#define _nd_area  *_ppvar[0]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 /* declaration of user functions */
 static double _hoc_calculate_current(void*);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(Object* _ho) { void* create_point_process(int, Object*);
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt(void*);
 static double _hoc_loc_pnt(void* _vptr) {double loc_point_process(int, void*);
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(void* _vptr) {double has_loc_point(void*);
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(void* _vptr) {
 double get_loc_point_process(void*); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 "calculate_current", _hoc_calculate_current,
 0, 0
};
#define calculate_current calculate_current_RefractoryNeuron
 extern double calculate_current( _threadargsproto_ );
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "thresh", "mV",
 "abs_refrac", "ms",
 "rel_refrac", "ms",
 "rel_factor", "mV",
 "tau", "ms",
 "i", "nA",
 0,0
};
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 static void nrn_cur(NrnThread*, _Memb_list*, int);
static void  nrn_jacob(NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(void* _vptr) {
   destroy_point_process(_vptr);
}
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"RefractoryNeuron",
 "thresh",
 "abs_refrac",
 "rel_refrac",
 "rel_factor",
 "tau",
 "alive",
 0,
 "i",
 0,
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 13, _prop);
 	/*initialize range parameters*/
 	thresh = -55;
 	abs_refrac = 1;
 	rel_refrac = 15;
 	rel_factor = 10;
 	tau = 10;
 	alive = 1;
  }
 	_prop->param = _p;
 	_prop->param_size = 13;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 2, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _RefractoryNeuron_reg() {
	int _vectorized = 1;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 1,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 13, 2);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
 add_nrn_has_net_event(_mechtype);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 RefractoryNeuron /home/silee1103/Neuron/cortical_neural_networks/src/RefractoryNeuron.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static void _net_receive (Point_process* _pnt, double* _args, double _lflag) 
{  double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   _thread = (Datum*)0; _nt = (NrnThread*)_pnt->_vnt;   _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;  v = NODEV(_pnt->node);
 {
   if ( alive  && v > current_thresh ) {
     net_event ( _pnt, t ) ;
     v = - 70.0 ;
     t0 = t ;
     state = 1.0 ;
     }
   } 
 NODEV(_pnt->node) = v;
 }
 
double calculate_current ( _threadargsproto_ ) {
   double _lcalculate_current;
 if ( state  == 1.0 ) {
     _lcalculate_current = 0.0 ;
     }
   else {
     _lcalculate_current = ( v - current_thresh ) / tau ;
     }
   
return _lcalculate_current;
 }
 
static double _hoc_calculate_current(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (NrnThread*)((Point_process*)_vptr)->_vnt;
 _r =  calculate_current ( _p, _ppvar, _thread, _nt );
 return(_r);
}

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
 {
   v = - 70.0 ;
   current_thresh = thresh ;
   t0 = - 1e9 ;
   state = 0.0 ;
   }

}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _tsav = -1e20;
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
 initmodel(_p, _ppvar, _thread, _nt);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   if ( state  == 1.0 ) {
     current_thresh = 1e9 ;
     if ( t - t0 >= abs_refrac ) {
       state = 2.0 ;
       current_thresh = thresh + rel_factor ;
       }
     }
   else if ( state  == 2.0 ) {
     current_thresh = thresh + rel_factor * exp ( - ( t - t0 - abs_refrac ) / rel_refrac ) ;
     if ( t - t0 >= abs_refrac + rel_refrac ) {
       state = 0.0 ;
       current_thresh = thresh ;
       }
     }
   i = calculate_current ( _threadargs_ ) ;
   }
 _current += i;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type) {

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/silee1103/Neuron/cortical_neural_networks/src/RefractoryNeuron.mod";
static const char* nmodl_file_text = 
  "COMMENT\n"
  "\n"
  "A mechanism to simulate a leaky-integrator neuron with absolute and relative refractory periods.\n"
  "The model dynamically adjusts the threshold during the relative refractory period and blocks spiking during the absolute refractory period.\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "NEURON {\n"
  "    POINT_PROCESS RefractoryNeuron\n"
  "    RANGE thresh, abs_refrac, rel_refrac, rel_factor, tau, v, alive\n"
  "    NONSPECIFIC_CURRENT i\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "    (mV) = (millivolt)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "    thresh = -55 (mV)         : Resting spike threshold\n"
  "    abs_refrac = 1 (ms)       : Absolute refractory period duration\n"
  "    rel_refrac = 15 (ms)      : Relative refractory period duration\n"
  "    rel_factor = 10 (mV)      : Increase in threshold during relative refractory\n"
  "    tau = 10 (ms)             : Membrane time constant\n"
  "    alive = 1                 : Neuron is alive (1 = true, 0 = dead)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    v (mV)                   : Membrane potential\n"
  "    i (nA)                   : Output current\n"
  "    current_thresh (mV)      : Dynamic threshold\n"
  "    dt (ms)                  : Simulation time step\n"
  "    t0 (ms)                  : Time of last spike\n"
  "    state                    : Refractory state (0 = none, 1 = absolute, 2 = relative)\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "    v = -70\n"
  "    current_thresh = thresh\n"
  "    t0 = -1e9                : Initialize to a large negative value to prevent early firing\n"
  "    state = 0                : No refractory period initially\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "    if (state == 1) {                      : Absolute refractory period\n"
  "        current_thresh = 1e9               : Block spiking by setting a high threshold\n"
  "        if (t - t0 >= abs_refrac) {\n"
  "            state = 2                      : Switch to relative refractory\n"
  "            current_thresh = thresh + rel_factor\n"
  "        }\n"
  "    } else if (state == 2) {               : Relative refractory period\n"
  "        current_thresh = thresh + rel_factor * exp(-(t - t0 - abs_refrac) / rel_refrac)\n"
  "        if (t - t0 >= abs_refrac + rel_refrac) {\n"
  "            state = 0                      : Exit refractory period\n"
  "            current_thresh = thresh\n"
  "        }\n"
  "    }\n"
  "\n"
  "    i = calculate_current()\n"
  "}\n"
  "\n"
  "NET_RECEIVE(weight (nA)) {\n"
  "    if (alive && v > current_thresh) {     : Check if the neuron is alive and threshold is crossed\n"
  "        net_event(t)                       : Emit a spike event\n"
  "        v = -70                            : Reset membrane potential\n"
  "        t0 = t                             : Update the time of the last spike\n"
  "        state = 1                          : Enter absolute refractory period\n"
  "    }\n"
  "}\n"
  "\n"
  "FUNCTION calculate_current() {\n"
  "    if (state == 1) {                      : No current during absolute refractory\n"
  "        calculate_current = 0\n"
  "    } else {\n"
  "        calculate_current = (v - current_thresh) / tau\n"
  "    }\n"
  "}\n"
  ;
#endif
