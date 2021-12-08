#ifndef scintillation_hh
#define scintillation_hh

#include "OpEngine.hh"
#include "ParametersManager.hh"

template<typename OpEngine, template<typename T> typename ParametersManager>
struct scintillation {
    typedef typename OpEngine::FloatType    engine_float_type;
    typedef typename OpEngine::Vector3Type  engine_vector3_type;

    typedef typename OpEngine::UniRandFunc  engine_unirand_func; // functional: operator()
    typedef typename OpEngine::SqrtFunc     engine_sqrt_func; // functional: operator()
    typedef typename OpEngine::SinFunc      engine_sin_func; // functional: operator()
    typedef typename OpEngine::CosFunc      engine_cos_func; // functional: operator()
    typedef typename OpEngine::LogFunc      engine_log_func; // functional: operator()
    typedef typename OpEngine::CrossFunc    engine_cross_func; // functional: operator()
    typedef typename OpEngine::DotFunc      engine_dot_func; // functional: operator()
    typedef typename OpEngine::AddFunc      engine_add_func; // functional: operator()
    typedef typename OpEngine::UnitFunc     engine_unit_func; // functional: operator()

    typedef engine_float_type   op_float_t;
    typedef engine_vector3_type op_vector3_t;

    engine_unirand_func unirand;
    engine_sqrt_func    sqrt_func;
    engine_sin_func     sin_func;
    engine_cos_func     cos_func;
    engine_log_func     log_func;
    engine_cross_func   cross_func;
    engine_dot_func     dot_func;
    engine_add_func     add_func;
    engine_unit_func    unit_func;

    // parameters
    typedef ParametersManager<OpEngine> engine_pm_type;
    typedef typename engine_pm_type::LookUpTable pm_lookup_t;
    const engine_pm_type& pm;

    scintillation(const engine_pm_type& _pm): pm(_pm) {

    }


    void generate() {

        // GENSTEP INFO:
        op_float_t genstep_charge = 0.0;
        op_float_t genstep_len = 0.0;
        op_float_t genstep_pre_v = 1.0; // dummy
        op_float_t genstep_post_v = 1.0; // dummy
        op_vector3_t genstep_pre_pos;
        op_vector3_t genstep_delta;
        op_float_t genstep_pre_t;

        op_float_t cost = 1. - 2.*unirand();
        op_float_t sint = sqrt_func((1.-cost)*(1.+cost));

        op_float_t phi = OpEngine::twopi*unirand();
        op_float_t sinp = sin_func(phi);
        op_float_t cosp = cos_func(phi);

        op_float_t px = sint*cosp;
        op_float_t py = sint*sinp;
        op_float_t pz = cost;

        op_vector3_t photonMomentum{px,py,pz};

        op_float_t sx = cost*cosp;
        op_float_t sy = cost*sinp; 
        op_float_t sz = -sint;

        op_vector3_t photonPolarization{sx, sy, sz};

        op_vector3_t perp = cross_func(photonMomentum, photonPolarization);


        phi = OpEngine::twopi*unirand();
        sinp = sin_func(phi);
        cosp = cos_func(phi);

        photonPolarization = add_func(
                                      dot_func(cosp, photonPolarization),
                                      dot_func(sinp, perp));

        photonPolarization = unit_func(photonPolarization);

        // calculate energy
        // TODO
        op_float_t sampledEnergy = 4.*OpEngine::eV;

        op_float_t atime{0.0};
        op_vector3_t apos{0.,0.,0.};

        // calculate delta time
        op_float_t rand = 1.0;

        if (genstep_charge != 0) {
            rand = unirand();
        }

        op_float_t delta = rand * genstep_len;

        op_float_t deltaTime = delta / 
            ((genstep_pre_v+genstep_post_v)/2.);

        op_float_t ScintillationTime = 0.0;

        // TODO
        // choose fast/slow/slower ...

        deltaTime = deltaTime - ScintillationTime*log_func(unirand());

        apos = add_func(genstep_pre_pos,
                        dot_func(rand, genstep_delta));

        atime = genstep_pre_t + deltaTime;
    }
    
};

typedef scintillation<DummyCpuOpEngine, DummyParametersManager> DummyScintillation_t;

#endif
