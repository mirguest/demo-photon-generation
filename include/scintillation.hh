#ifndef scintillation_hh
#define scintillation_hh

#include "OpEngine.hh"
#include "ParametersManager.hh"

template<typename OpEngine, template<typename T> typename ParametersManager>
struct scintillation {
    typedef OpEngine engine_type;
    typedef typename OpEngine::FloatType    engine_float_type;
    typedef typename OpEngine::Vector3Type  engine_vector3_type;

    typedef engine_float_type   op_float_t;
    typedef engine_vector3_type op_vector3_t;

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

        op_float_t cost = 1. - 2.*engine_type::unirand();
        op_float_t sint = engine_type::sqrt_func((1.-cost)*(1.+cost));

        op_float_t phi = engine_type::twopi*engine_type::unirand();
        op_float_t sinp = engine_type::sin_func(phi);
        op_float_t cosp = engine_type::cos_func(phi);

        op_float_t px = sint*cosp;
        op_float_t py = sint*sinp;
        op_float_t pz = cost;

        op_vector3_t photonMomentum{px,py,pz};

        op_float_t sx = cost*cosp;
        op_float_t sy = cost*sinp; 
        op_float_t sz = -sint;

        op_vector3_t photonPolarization{sx, sy, sz};

        op_vector3_t perp = engine_type::cross_func(photonMomentum, photonPolarization);


        phi = engine_type::twopi*engine_type::unirand();
        sinp = engine_type::sin_func(phi);
        cosp = engine_type::cos_func(phi);

        photonPolarization = engine_type::add_func(
                                      engine_type::dot_func(cosp, photonPolarization),
                                      engine_type::dot_func(sinp, perp));

        photonPolarization = engine_type::unit_func(photonPolarization);

        // calculate energy
        // TODO
        op_float_t sampledEnergy = 4.*engine_type::eV;

        op_float_t atime{0.0};
        op_vector3_t apos{0.,0.,0.};

        // calculate delta time
        op_float_t rand = 1.0;

        if (genstep_charge != 0) {
            rand = engine_type::unirand();
        }

        op_float_t delta = rand * genstep_len;

        op_float_t deltaTime = delta / 
            ((genstep_pre_v+genstep_post_v)/2.);

        op_float_t ScintillationTime = 0.0;

        // TODO
        // choose fast/slow/slower ...

        deltaTime = deltaTime - ScintillationTime*engine_type::log_func(engine_type::unirand());

        apos = engine_type::add_func(genstep_pre_pos,
                        engine_type::dot_func(rand, genstep_delta));

        atime = genstep_pre_t + deltaTime;
    }
    
};

typedef scintillation<DummyCpuOpEngine, DummyParametersManager> DummyScintillation_t;

#endif
