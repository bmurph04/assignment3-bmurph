#ifndef TRAPEZOIDAL_INTEGRATOR_H_
#define TRAPEZOIDAL_INTEGRATOR_H_

#include "integrators/IntegratorBase.hpp"

namespace GLOO{

template <class TSystem, class TState>
class TrapezoidalIntegrator : public IntegratorBase<TSystem, TState> {
    // define all methods here to use template classes

    TState Integrate(const TSystem& system,
                        const TState& state,
                        float start_time,
                        float dt) const override {
        
        // Compute time derivative 0
        ParticleState time_deriv_0 = system.ComputeTimeDerivative(state, start_time);
        // Compute time derivative 1
        ParticleState time_deriv_1 = system.ComputeTimeDerivative(state + dt * time_deriv_0, start_time + dt);
        // Trapezoidal integrator
        return state + (dt/2) * (time_deriv_0 + time_deriv_1);
    }
};

} // namespace GLOO

#endif