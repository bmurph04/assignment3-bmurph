#include "PendulumSystem.hpp"

#include "objects/PendulumParticle.hpp"
#include "objects/PendulumSpring.hpp"

namespace GLOO {

PendulumSystem::PendulumSystem() { }

// implementation of time derivative dX(t)/dt = f(X(t), t) for pendulum 
ParticleState PendulumSystem::ComputeTimeDerivative(const ParticleState& state, float time) const {
    // not fully implemented
    std::vector<glm::vec3> deriv_positions(state.positions.size());
    std::vector<glm::vec3> deriv_velocities(state.velocities.size());

    // set derivative of position to be current velocity
    deriv_positions = state.velocities;

    // set derivative of velocity
    

    ParticleState new_state{deriv_positions, deriv_velocities};
    return new_state;
}

// ParticleState PendulumSystem::ComputeAcceleration() {
// }


}