#ifndef cerenkov_hh
#define cerenkov_hh

#include "OpEngine.hh"
#include "ParametersManager.hh"

template<typename OpEngine, template<typename T> typename ParametersManager>
struct cerenkov {
    typedef OpEngine engine_type;
    typedef typename OpEngine::FloatType    engine_float_type;
    typedef typename OpEngine::Vector3Type  engine_vector3_type;

    typedef engine_float_type op_float_t;
    typedef engine_vector3_type op_vector3_t;

    // parameters
    typedef ParametersManager<OpEngine> engine_pm_type;
    typedef typename engine_pm_type::LookUpTable pm_lookup_t;
    const engine_pm_type& pm;

    cerenkov(const engine_pm_type& _pm): pm(_pm) {

    }

    void generate() {

        // GENSTEP INFO:
        op_float_t genstep_charge = 0.0;
        op_float_t genstep_len = 0.0;
        op_float_t genstep_pre_v = 1.0; // dummy
        op_float_t genstep_post_v = 1.0; // dummy
        op_vector3_t genstep_pre_pos;
        op_vector3_t genstep_delta;
        op_float_t genstep_pre_t = 0.0;
        op_float_t genstep_pre_beta = 0.0;
        op_float_t genstep_post_beta = 0.0;

        size_t genstep_matidx = 0;

        const pm_lookup_t& pm_rindex_lookup = pm.rindex(genstep_matidx);

        op_vector3_t x0 = genstep_pre_pos;
        op_vector3_t p0 = engine_type::unit_func(genstep_delta);

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
            rand = engine_type::unirand();  
            sampledEnergy = Pmin + rand * dp; 
            sampledRI = pm_rindex_lookup.value(sampledEnergy);
            // check if n(E) > 1/beta
            if (sampledRI < BetaInverse) {
                continue;
            }
            cosTheta = BetaInverse / sampledRI;  

            sin2Theta = (1.0 - cosTheta)*(1.0 + cosTheta);
            rand = engine_type::unirand();  

            // Loop checking, 07-Aug-2015, Vladimir Ivanchenko
            if (rand*maxSin2 <= sin2Theta) {
                break;
            }
        }

        rand = engine_type::unirand();

        op_float_t phi = engine_type::twopi*rand;
        op_float_t sinPhi = engine_type::sin_func(phi);
        op_float_t cosPhi = engine_type::cos_func(phi);

        op_float_t sinTheta = engine_type::sqrt_func(sin2Theta); 
        op_float_t px = sinTheta*cosPhi;
        op_float_t py = sinTheta*sinPhi;
        op_float_t pz = cosTheta;

        op_vector3_t photonMomentum{px,py,pz};
        photonMomentum = engine_type::rotateUz_func(photonMomentum, p0);

        op_float_t sx = cosTheta*cosPhi;
        op_float_t sy = cosTheta*sinPhi; 
        op_float_t sz = -sinTheta;

        op_vector3_t photonPolarization{sx, sy, sz};

        photonPolarization = engine_type::rotateUz_func(photonPolarization, p0);

        // 
        // todo:
        // do {
        // 
        // } while ( );
        //
        rand = engine_type::unirand();
        op_float_t delta = rand * genstep_len;
        op_float_t deltaTime = delta / (genstep_pre_v + 
                                        rand*(genstep_post_v-
                                              genstep_pre_v)*0.5);

        op_float_t aSecondaryTime = t0 + deltaTime;

        op_vector3_t aSecondaryPosition = engine_type::add_func(x0, engine_type::dot_func(rand, genstep_delta));

    }
    
};

typedef cerenkov<DummyCpuOpEngine, DummyParametersManager> DummyCerenkov_t;


#endif
