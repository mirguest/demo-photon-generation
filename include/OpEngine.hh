#ifndef OpEngine_hh
#define OpEngine_hh

#include <array>

struct DummyCpuOpEngine {
    typedef double                   FloatType;
    typedef std::array<FloatType, 3> Vector3Type;

    struct UniRandFunc {
        FloatType operator()() {
            return 1.0;
        }
    };
};

#endif
