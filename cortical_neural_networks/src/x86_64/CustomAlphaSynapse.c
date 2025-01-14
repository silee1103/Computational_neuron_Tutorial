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
 
#define nrn_init _nrn_init__CustomAlphaSynapse
#define _nrn_initial _nrn_initial__CustomAlphaSynapse
#define nrn_cur _nrn_cur__CustomAlphaSynapse
#define _nrn_current _nrn_current__CustomAlphaSynapse
#define nrn_jacob _nrn_jacob__CustomAlphaSynapse
#define nrn_state _nrn_state__CustomAlphaSynapse
#define _net_receive _net_receive__CustomAlphaSynapse 
#define state state__CustomAlphaSynapse 
 
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
#define tau _p[0]
#define tau_columnindex 0
#define e _p[1]
#define e_columnindex 1
#define gmax _p[2]
#define gmax_columnindex 2
#define peak_time _p[3]
#define peak_time_columnindex 3
#define half_width _p[4]
#define half_width_columnindex 4
#define abs_ref _p[5]
#define abs_ref_columnindex 5
#define rel_ref _p[6]
#define rel_ref_columnindex 6
#define i _p[7]
#define i_columnindex 7
#define A _p[8]
#define A_columnindex 8
#define refractory _p[9]
#define refractory_columnindex 9
#define relative_factor _p[10]
#define relative_factor_columnindex 10
#define g _p[11]
#define g_columnindex 11
#define factor _p[12]
#define factor_columnindex 12
#define DA _p[13]
#define DA_columnindex 13
#define Drefractory _p[14]
#define Drefractory_columnindex 14
#define Drelative_factor _p[15]
#define Drelative_factor_columnindex 15
#define v _p[16]
#define v_columnindex 16
#define _g _p[17]
#define _g_columnindex 17
#define _tsav _p[18]
#define _tsav_columnindex 18
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
 static double _hoc_calculate_factor(void*);
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
 "calculate_factor", _hoc_calculate_factor,
 0, 0
};
#define calculate_factor calculate_factor_CustomAlphaSynapse
 extern double calculate_factor( _threadargsprotocomma_ double , double );
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "tau", "ms",
 "e", "mV",
 "gmax", "uS",
 "peak_time", "ms",
 "half_width", "ms",
 "abs_ref", "ms",
 "rel_ref", "ms",
 "A", "uS",
 "refractory", "ms",
 "i", "nA",
 0,0
};
 static double A0 = 0;
 static double delta_t = 0.01;
 static double relative_factor0 = 0;
 static double refractory0 = 0;
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
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(NrnThread*, _Memb_list*, int);
static void _ode_matsol(NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[2]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"CustomAlphaSynapse",
 "tau",
 "e",
 "gmax",
 "peak_time",
 "half_width",
 "abs_ref",
 "rel_ref",
 0,
 "i",
 0,
 "A",
 "refractory",
 "relative_factor",
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
 	_p = nrn_prop_data_alloc(_mechtype, 19, _prop);
 	/*initialize range parameters*/
 	tau = 1.7;
 	e = 0;
 	gmax = 0.14;
 	peak_time = 1.7;
 	half_width = 8.5;
 	abs_ref = 1;
 	rel_ref = 15;
  }
 	_prop->param = _p;
 	_prop->param_size = 19;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _CustomAlphaSynapse_reg() {
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
  hoc_register_prop_size(_mechtype, 19, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 CustomAlphaSynapse /home/silee1103/Neuron/cortical_neural_networks/src/CustomAlphaSynapse.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[3], _dlist1[3];
 static int state(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   DA = - A / tau ;
   Drefractory = - 1.0 / abs_ref ;
   Drelative_factor = - relative_factor / rel_ref ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 DA = DA  / (1. - dt*( ( - 1.0 ) / tau )) ;
 Drefractory = Drefractory  / (1. - dt*( 0.0 )) ;
 Drelative_factor = Drelative_factor  / (1. - dt*( ( - 1.0 ) / rel_ref )) ;
  return 0;
}
 /*END CVODE*/
 static int state (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
    A = A + (1. - exp(dt*(( - 1.0 ) / tau)))*(- ( 0.0 ) / ( ( - 1.0 ) / tau ) - A) ;
    refractory = refractory - dt*(- ( ( - 1.0 ) / abs_ref ) ) ;
    relative_factor = relative_factor + (1. - exp(dt*(( - 1.0 ) / rel_ref)))*(- ( 0.0 ) / ( ( - 1.0 ) / rel_ref ) - relative_factor) ;
   }
  return 0;
}
 
static void _net_receive (Point_process* _pnt, double* _args, double _lflag) 
{  double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   _thread = (Datum*)0; _nt = (NrnThread*)_pnt->_vnt;   _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t; {
   if ( refractory <= 0.0 ) {
       if (nrn_netrec_state_adjust && !cvode_active_){
    /* discon state adjustment for cnexp case (rate uses no local variable) */
    double __state = refractory;
    double __primary = (abs_ref) - __state;
     __primary -= 0.5*dt*( - ( ( - 1.0 ) / abs_ref )  );
    refractory += __primary;
  } else {
 refractory = abs_ref ;
       }
   if (nrn_netrec_state_adjust && !cvode_active_){
    /* discon state adjustment for cnexp case (rate uses no local variable) */
    double __state = relative_factor;
    double __primary = (1.0) - __state;
     __primary += ( 1. - exp( 0.5*dt*( ( - 1.0 ) / rel_ref ) ) )*( - ( 0.0 ) / ( ( - 1.0 ) / rel_ref ) - __primary );
    relative_factor += __primary;
  } else {
 relative_factor = 1.0 ;
       }
   if (nrn_netrec_state_adjust && !cvode_active_){
    /* discon state adjustment for cnexp case (rate uses no local variable) */
    double __state = A;
    double __primary = (A + _args[0]) - __state;
     __primary += ( 1. - exp( 0.5*dt*( ( - 1.0 ) / tau ) ) )*( - ( 0.0 ) / ( ( - 1.0 ) / tau ) - __primary );
    A += __primary;
  } else {
 A = A + _args[0] ;
       }
 }
   } }
 
double calculate_factor ( _threadargsprotocomma_ double _ltau , double _lgmax ) {
   double _lcalculate_factor;
 double _lpeak_value ;
 _lpeak_value = _ltau * exp ( - 1.0 ) ;
   _lcalculate_factor = _lgmax / _lpeak_value ;
   
return _lcalculate_factor;
 }
 
static double _hoc_calculate_factor(void* _vptr) {
 double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   _p = ((Point_process*)_vptr)->_prop->param;
  _ppvar = ((Point_process*)_vptr)->_prop->dparam;
  _thread = _extcall_thread;
  _nt = (NrnThread*)((Point_process*)_vptr)->_vnt;
 _r =  calculate_factor ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 return(_r);
}
 
static int _ode_count(int _type){ return 3;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 (_p, _ppvar, _thread, _nt);
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 3; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  A = A0;
  relative_factor = relative_factor0;
  refractory = refractory0;
 {
   A = 0.0 ;
   refractory = 0.0 ;
   relative_factor = 0.0 ;
   factor = calculate_factor ( _threadargscomma_ tau , gmax ) ;
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
   g = A * ( 1.0 - relative_factor ) ;
   i = g * ( v - e ) ;
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
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
 {   state(_p, _ppvar, _thread, _nt);
  }}}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = A_columnindex;  _dlist1[0] = DA_columnindex;
 _slist1[1] = refractory_columnindex;  _dlist1[1] = Drefractory_columnindex;
 _slist1[2] = relative_factor_columnindex;  _dlist1[2] = Drelative_factor_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/silee1103/Neuron/cortical_neural_networks/src/CustomAlphaSynapse.mod";
static const char* nmodl_file_text = 
  "NEURON {\n"
  "    POINT_PROCESS CustomAlphaSynapse\n"
  "    RANGE tau, e, gmax, i, peak_time, half_width\n"
  "    RANGE abs_ref, rel_ref, refractory, relative_factor\n"
  "    NONSPECIFIC_CURRENT i\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "    (mV) = (millivolt)\n"
  "    (nA) = (nanoamp)\n"
  "    (uS) = (microsiemens)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "    tau = 1.7 (ms)       : Time constant for alpha function\n"
  "    e = 0 (mV)           : Reversal potential\n"
  "    gmax = 0.14 (uS)     : Peak conductance\n"
  "    peak_time = 1.7 (ms) : Time to peak\n"
  "    half_width = 8.5 (ms): Approximate half-width\n"
  "    abs_ref = 1.0 (ms)   : Absolute refractory period\n"
  "    rel_ref = 15.0 (ms)  : Relative refractory period\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    v (mV)               : Membrane potential\n"
  "    i (nA)               : Current\n"
  "    g (uS)               : Conductance\n"
  "    factor               : Scaling factor to ensure peak amplitude\n"
  "}\n"
  "\n"
  "STATE {\n"
  "    A (uS)               : Alpha function conductance\n"
  "    refractory (ms)      : Timer for absolute refractory period\n"
  "    relative_factor      : Modulation factor for relative refractoriness\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "    A = 0\n"
  "    refractory = 0\n"
  "    relative_factor = 0\n"
  "    factor = calculate_factor(tau, gmax) : Precompute scaling factor\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "    SOLVE state METHOD cnexp\n"
  "    g = A * (1 - relative_factor)        : Modulate conductance by relative refractoriness\n"
  "    i = g * (v - e)                      : Compute current\n"
  "}\n"
  "\n"
  "DERIVATIVE state {\n"
  "    A' = -A / tau                        : Exponential decay of conductance\n"
  "    refractory' = -1 / abs_ref           : Decay refractory period\n"
  "    relative_factor' = -relative_factor / rel_ref : Gradual recovery from relative refractoriness\n"
  "}\n"
  "\n"
  "NET_RECEIVE(weight (uS)) {\n"
  "    if (refractory <= 0) {               : Check if neuron is in refractory period\n"
  "        refractory = abs_ref             : Set absolute refractory timer\n"
  "        relative_factor = 1              : Maximize relative refractoriness\n"
  "        A = A + weight                   : Increment conductance\n"
  "    }\n"
  "}\n"
  "\n"
  "FUNCTION calculate_factor(tau (ms), gmax (uS)) {\n"
  "    LOCAL peak_value\n"
  "    peak_value = tau * exp(-1)           : Alpha function peak occurs at t = tau\n"
  "    calculate_factor = gmax / peak_value : Scale such that gmax corresponds to peak\n"
  "}\n"
  ;
#endif
