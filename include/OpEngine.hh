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
        FloatType operator()(const FloatType& v) {
            return std::sqrt(v);
        }
    };

    struct SinFunc {
        FloatType operator()(const FloatType& v) {
            return std::sin(v);
        }
    };

    struct CosFunc {
        FloatType operator()(const FloatType& v) {
            return std::cos(v);
        }
    };

    struct LogFunc {
        FloatType operator()(const FloatType& v) {
            return std::log(v);
        }
    };

    struct AddFunc {
        Vector3Type operator()(const Vector3Type& v1, const Vector3Type& v2) {
            Vector3Type v;
            return v;
        }
    };

    struct CrossFunc {
        Vector3Type operator()(const Vector3Type& v1, const Vector3Type& v2) {
            Vector3Type v;
            return v;
        }
    };

    struct DotFunc {
        Vector3Type operator()(const FloatType& v1, const Vector3Type& v2) {
            Vector3Type v;
            return v;
        }
    };

    struct UnitFunc {
        Vector3Type operator()(const Vector3Type& v1) {
            Vector3Type v;
            return v;
        }
    };

    struct RotateUzFunc {
        Vector3Type operator()(const Vector3Type& v1, const Vector3Type& newv) {
            Vector3Type v;
            return v;
        }
    };

    // const
    static const FloatType twopi;
    // units
    static const FloatType MeV;
    static const FloatType eV;
};



#endif
