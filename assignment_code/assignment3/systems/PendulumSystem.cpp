#include "PendulumSystem.hpp"

#include "objects/PendulumParticle.hpp"

namespace GLOO {

PendulumSystem::PendulumSystem(int num_particles) : num_particles_(num_particles){
    // Initialize particles in pendulum system, reachable by index
    for (int i = 0; i < num_particles; i++){
        // Call CreatePendulumParticle
    }

    

}

PendulumSystem::~PendulumSystem() {

}

PendulumSystem::CreatePendulumParticle(float mass, PendulumParticle* parent = nullptr, float position = glm::vec3(0.0f), bool fixed = false) {
    // Don't create spring and attach to parent if parent is nullptr (root). Also, make sure fixed is set to true for particle
}

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

ParticleState PendulumSystem::ComputeAcceleration() {
}


}