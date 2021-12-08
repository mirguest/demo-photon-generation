#include "cerenkov.hh"
#include "scintillation.hh"

int main(int argc, char* argv[]) {

    DummyParametersManager_t parameters_manager;

    DummyCerenkov_t cerenkov_generator(parameters_manager);
    DummyScintillation_t scintillation_generator;

    size_t n_cerenkov = 100;
    size_t n_scintillation = 10000;

    for (size_t i = 0; i < n_cerenkov; ++i) {
        cerenkov_generator.generate();
    }

    for (size_t i = 0; i < n_scintillation; ++i) {
        scintillation_generator.generate();
    }

    return 0;
}
