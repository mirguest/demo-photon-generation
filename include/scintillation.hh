#ifndef scintillation_hh
#define scintillation_hh

#include "OpEngine.hh"

template<typename OpEngine>
struct scintillation {
    typedef typename OpEngine::FloatType    engine_float_type;
    typedef typename OpEngine::Vector3Type  engine_vector3_type;

    typedef typename OpEngine::UniRandFunc  engine_unirand_func; // functional: operator()
    typedef typename OpEngine::SqrtFunc     engine_sqrt_func; // functional: operator()
    typedef typename OpEngine::SinFunc      engine_sin_func; // functional: operator()
    typedef typename OpEngine::CosFunc      engine_cos_func; // functional: operator()
    typedef typename OpEngine::CrossFunc    engine_cross_func; // functional: operator()
    typedef typename OpEngine::DotFunc      engine_dot_func; // functional: operator()
    typedef typename OpEngine::AddFunc      engine_add_func; // functional: operator()
    typedef typename OpEngine::UnitFunc     engine_unit_func; // functional: operator()

    void generate() {
        typedef engine_float_type op_float_t;
        typedef engine_vector3_type op_vector3_t;
        
        engine_unirand_func unirand;
        engine_sqrt_func    sqrt_func;
        engine_sin_func     sin_func;
        engine_cos_func     cos_func;
        engine_cross_func   cross_func;
        engine_dot_func     dot_func;
        engine_add_func     add_func;
        engine_unit_func    unit_func;

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
    }
    
};

typedef scintillation<DummyCpuOpEngine> DummyScintillation_t;

#endif
