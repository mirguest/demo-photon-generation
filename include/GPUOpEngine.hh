#ifndef GPUOpEngine_hh
#define GPUOpEngine_hh

#include <cuda.h>

#if __CUDA_ARCH__
#define OP_DEVICE_FUNC __device__
#define OP_CONSTANT __constant__
#else
#define OP_DEVICE_FUNC
#define OP_CONSTANT
#endif

struct DummyGpuOpEngine {
    typedef float  FloatType;
    typedef float3 Vector3Type;

    OP_DEVICE_FUNC
    static FloatType unirand() {
        return 1.0;
    }

    OP_DEVICE_FUNC
    static FloatType sqrt_func(const FloatType& v) {
        return sqrt(v);
    }

    OP_DEVICE_FUNC
    static FloatType sin_func(const FloatType& v) {
        return sin(v);
    }

    OP_DEVICE_FUNC
    static FloatType cos_func(const FloatType& v) {
        return cos(v);
    }

    OP_DEVICE_FUNC
    static FloatType acos_func(const FloatType& v) {
        return acos(v);
    }

    OP_DEVICE_FUNC
    static FloatType log_func(const FloatType& v) {
        return log(v);
    }

    OP_DEVICE_FUNC
    static Vector3Type add_func(const Vector3Type& v1, const Vector3Type& v2) {
        Vector3Type v;
        return v;
    }

    OP_DEVICE_FUNC
    static Vector3Type cross_func(const Vector3Type& v1, const Vector3Type& v2) {
        Vector3Type v;
        return v;
    }

    OP_DEVICE_FUNC
    static Vector3Type dot_func(const FloatType& v1, const Vector3Type& v2) {
        Vector3Type v;
        return v;
    }

    OP_DEVICE_FUNC
    static Vector3Type unit_func(const Vector3Type& v1) {
        Vector3Type v;
        return v;
    }

    OP_DEVICE_FUNC
    static Vector3Type rotateUz_func(const Vector3Type& v1, const Vector3Type& newv) {
        Vector3Type v;
        return v;
    }

};

#endif

