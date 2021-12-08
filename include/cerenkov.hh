#ifndef cerenkov_hh
#define cerenkov_hh

#include "OpEngine.hh"
#include "ParametersManager.hh"

template<typename OpEngine, template<typename T> typename ParametersManager>
struct cerenkov {
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
    typedef typename OpEngine::RotateUzFunc engine_rotateUz_func; // functional: operator()

    typedef engine_float_type op_float_t;
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
    engine_rotateUz_func rotateUz_func;

    // parameters
    typedef typename ParametersManager<OpEngine>::LookUpTable pm_lookup_t;
    ParametersManager<OpEngine> pm;

    void generate() {
        // GENSTEP INFO:
        op_float_t genstep_charge = 0.0;
        op_float_t genstep_len = 0.0;
        op_float_t genstep_pre_v = 1.0; // dummy
        op_float_t genstep_post_v = 1.0; // dummy
        op_vector3_t genstep_pre_pos;
        op_vector3_t genstep_delta;
        op_float_t genstep_pre_t;
        op_float_t genstep_pre_beta;
        op_float_t genstep_post_beta;

        size_t genstep_matidx = 0;

        const pm_lookup_t& pm_rindex_lookup = pm.rindex(genstep_matidx);

        op_vector3_t x0 = genstep_pre_pos;
        op_vector3_t p0 = unit_func(genstep_delta);

        op_float_t t0 = genstep_pre_t;
        op_float_t beta = (genstep_pre_beta+genstep_post_beta)*0.5;

        op_float_t Pmin = pm_rindex_lookup.xmin();
        op_float_t Pmax = pm_rindex_lookup.xmax();
        op_float_t dp = Pmax - Pmin;

        op_float_t nMax = pm_rindex_lookup.ymax();

        op_float_t BetaInverse = 1./beta;

        op_float_t maxCos = BetaInverse / nMax;
        op_float_t maxSin2 = (1.0 - maxCos) * (1.0 + maxCos);



        op_float_t rand;
        op_float_t sampledEnergy, sampledRI; 
        op_float_t cosTheta, sin2Theta;

        // sample an energy

        while (true) {
            rand = unirand();  
            sampledEnergy = Pmin + rand * dp; 
            sampledRI = pm_rindex_lookup.value(sampledEnergy);
            // check if n(E) > 1/beta
            if (sampledRI < BetaInverse) {
                continue;
            }
            cosTheta = BetaInverse / sampledRI;  

            sin2Theta = (1.0 - cosTheta)*(1.0 + cosTheta);
            rand = unirand();  

            // Loop checking, 07-Aug-2015, Vladimir Ivanchenko
            if (rand*maxSin2 <= sin2Theta) {
                break;
            }
        }

        rand = unirand();

        op_float_t phi = OpEngine::twopi*rand;
        op_float_t sinPhi = sin_func(phi);
        op_float_t cosPhi = cos_func(phi);

        op_float_t sinTheta = sqrt_func(sin2Theta); 
        op_float_t px = sinTheta*cosPhi;
        op_float_t py = sinTheta*sinPhi;
        op_float_t pz = cosTheta;

        op_vector3_t photonMomentum{px,py,pz};
        photonMomentum = rotateUz_func(photonMomentum, p0);

        op_float_t sx = cosTheta*cosPhi;
        op_float_t sy = cosTheta*sinPhi; 
        op_float_t sz = -sinTheta;

        op_vector3_t photonPolarization{sx, sy, sz};

        photonPolarization = rotateUz_func(photonPolarization, p0);

        // 
        // todo:
        // do {
        // 
        // } while ( );
        //
        rand = unirand();
        op_float_t delta = rand * genstep_len;
        op_float_t deltaTime = delta / (genstep_pre_v + 
                                        rand*(genstep_post_v-
                                              genstep_pre_v)*0.5);

        op_float_t aSecondaryTime = t0 + deltaTime;

        op_vector3_t aSecondaryPosition = add_func(x0, dot_func(rand, genstep_delta));

    }
    
};

typedef cerenkov<DummyCpuOpEngine, DummyParametersManager> DummyCerenkov_t;


#endif
