#ifndef scintillation_hh
#define scintillation_hh

#include "OpEngine.hh"

template<typename OpEngine>
struct scintillation {
    typedef typename OpEngine::FloatType    engine_float_type;
    typedef typename OpEngine::Vector3dType engine_vector3_type;
    typedef typename OpEngine::UniRandFunc  engine_unirand_func; // functional: operator()


    void generate() {
        engine_unirand_func unirand;

        typedef engine_float_type op_float_t;
        
        op_float_t cost = 1. - 2.*unirand();
        op_float_t sint = sqrt((1.-cost)*(1.+cost));
    }
    
};

typedef scintillation<DummyCpuOpEngine> DummyScintillation_t;

#endif
