#include "ClothSystem.hpp"

namespace GLOO {

// implementation of time derivative dX(t)/dt = f(X(t), t) for cloth 
ParticleState ClothSystem::ComputeTimeDerivative(const ParticleState& state, float time) const{
    // not fully implemented
    return state;
}

}