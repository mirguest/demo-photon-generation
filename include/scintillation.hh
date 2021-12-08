#ifndef scintillation_hh
#define scintillation_hh

#include "OpEngine.hh"

template<typename OpEngine>
struct scintillation {
    typedef typename OpEngine::FloatType    engine_float_type;
    typedef typename OpEngine::Vector3Type  engine_vector3_type;
    typedef typename OpEngine::UniRandFunc  engine_unirand_func; // functional: operator()
    typedef typename OpEngine::SqrtFunc     engine_sqrt_func; // functional: operator()


    void generate() {
        engine_unirand_func unirand;
        engine_sqrt_func    sqrt_func;

        typedef engine_float_type op_float_t;
        
        op_float_t cost = 1. - 2.*unirand();
        op_float_t sint = sqrt_func((1.-cost)*(1.+cost));
    }
    
};

typedef scintillation<DummyCpuOpEngine> DummyScintillation_t;

#endif
