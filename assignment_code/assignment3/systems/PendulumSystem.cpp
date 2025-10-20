#include "PendulumSystem.hpp"

namespace GLOO {

PendulumSystem::PendulumSystem() {

}

PendulumSystem::~PendulumSystem() {

}

// implementation of time derivative dX(t)/dt = f(X(t), t) for cloth 
ParticleState PendulumSystem::ComputeTimeDerivative(const ParticleState& state, float time) const {
    // not fully implemented
    return state;
}

}