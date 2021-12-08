#ifndef OpEngine_hh
#define OpEngine_hh

#include <array>
#include <cmath>

struct DummyCpuOpEngine {
    typedef double                   FloatType;
    typedef std::array<FloatType, 3> Vector3Type;

    struct UniRandFunc {
        FloatType operator()() {
            return 1.0;
        }
    };

    struct SqrtFunc {
        FloatType operator()(FloatType v) {
            return std::sqrt(v);
        }
    };
};

#endif
