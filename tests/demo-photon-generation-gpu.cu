
#include "scintillation.hh"
#include "GPUOpEngine.hh"
#include "GPUParametersManager.hh"

typedef scintillation<DummyGpuOpEngine, DummyGpuParametersManager> DummyGpuScintillation_t;

DummyGpuParametersManager_t parameters_manager;
DummyGpuScintillation_t scint(parameters_manager);

__global__
void launch_kernel() {
    scint.generate();
}

int main() {
    const int N = 1024;
    launch_kernel<<<1, N>>>();
}
