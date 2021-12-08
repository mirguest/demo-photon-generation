#ifndef ParametersManager_hh
#define ParametersManager_hh

#include <vector>
#include <algorithm>

#include "OpEngine.hh"

template<typename OpEngine>
struct DummyParametersManager {
    typedef typename OpEngine::FloatType    engine_float_type;

    // two columns: key / value
    struct LookUpTable {
        engine_float_type xmin() const {
            if (vx.size()) {
                auto it = std::min_element(vx.begin(), vx.end());
                return *it;
            }
            return 0.0;
        }

        engine_float_type xmax () const {
            if (vx.size()) {
                auto it = std::max_element(vx.begin(), vx.end());
                return *it;
            }
            return 0.0;
        }

        engine_float_type ymin() const {
            if (vy.size()) {
                auto it = std::min_element(vy.begin(), vy.end());
                return *it;
            }
            return 0.0;
        }

        engine_float_type ymax () const {
            if (vy.size()) {
                auto it = std::max_element(vy.begin(), vy.end());
                return *it;
            }
            return 0.0;
        }

        engine_float_type value(engine_float_type x) const {
            engine_float_type y = 0.0;

            if (vx.size() == 0) {
                return y;
            } else if (vx.size() == 1) {
                return *vy.begin();
            }

            auto it = std::upper_bound(vx.begin(), vx.end(), x);

            if (it == vx.begin()) {
                y = *vy.begin();
            } else if (it == vx.end()) {
                y = *(vy.end()-1);
            } else {
                engine_float_type x1 = *(it-1);
                engine_float_type x2 = *(it);

                engine_float_type y1 = *(vy.begin() + (it-1-vx.begin()));
                engine_float_type y2 = *(vy.begin() + (it  -vx.begin()));

                y = y1 + (y2-y1)/(x2-x1)*(x-x1);
            }
            
            return y;
        }
        
        std::vector<engine_float_type> vx; // should be in an ordered range
        std::vector<engine_float_type> vy;
    };

    const LookUpTable nulltable{};

    // for Refractive Index, the x is energy, y is index
    std::vector<LookUpTable> rindices;

    const LookUpTable& rindex(size_t matidx) const {
        if (matidx<rindices.size()) {
            return rindices[matidx];
        }
        return nulltable;
    }

    DummyParametersManager() {

    }
};

typedef DummyParametersManager<DummyCpuOpEngine> DummyParametersManager_t;

#endif
