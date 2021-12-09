#ifndef OpEngine_hh
#define OpEngine_hh

#include <array>
#include <cmath>

struct DummyCpuOpEngine {
    typedef double                   FloatType;
    typedef std::array<FloatType, 3> Vector3Type;

    static FloatType unirand() {
        return 1.0;
    }

    static FloatType sqrt_func(const FloatType& v) {
        return std::sqrt(v);
    }

    static FloatType sin_func(const FloatType& v) {
        return std::sin(v);
    }

    static FloatType cos_func(const FloatType& v) {
        return std::cos(v);
    }

    static FloatType log_func(const FloatType& v) {
        return std::log(v);
    }

    static Vector3Type add_func(const Vector3Type& v1, const Vector3Type& v2) {
        Vector3Type v;
        return v;
    }

    static Vector3Type cross_func(const Vector3Type& v1, const Vector3Type& v2) {
        Vector3Type v;
        return v;
    }

    static Vector3Type dot_func(const FloatType& v1, const Vector3Type& v2) {
        Vector3Type v;
        return v;
    }

    static Vector3Type unit_func(const Vector3Type& v1) {
        Vector3Type v;
        return v;
    }

    static Vector3Type rotateUz_func(const Vector3Type& v1, const Vector3Type& newv) {
        Vector3Type v;
        return v;
    }

    // const
    static const FloatType twopi;
    // units
    static const FloatType MeV;
    static const FloatType eV;
};



#endif
