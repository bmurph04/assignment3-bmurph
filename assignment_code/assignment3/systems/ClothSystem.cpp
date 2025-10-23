#include "ClothSystem.hpp"

#include "nodes/ScenePhysicsNode.hpp"
#include "objects/ParticleObject.hpp"
#include "objects/SpringObject.hpp"

namespace GLOO {

// implementation of time derivative dX(t)/dt = f(X(t), t) for cloth 
ParticleState ClothSystem::ComputeTimeDerivative(const ParticleState& state, float time) const{
    // not fully implemented
    std::vector<glm::vec3> deriv_positions(state.positions.size());
    std::vector<glm::vec3> deriv_velocities(state.velocities.size());

    // Get the accelerations for particles in the system
    std::vector<glm::vec3> state_accelerations = ComputeAcceleration(state);
    std::vector<glm::vec3> state_velocities = ComputeVelocity(state);

    // set derivative of position to be current velocity
    deriv_positions = state_velocities;

    // set derivative of velocity
    deriv_velocities = state_accelerations;

    ParticleState new_state{deriv_positions, deriv_velocities};
    return new_state;
}

std::vector<glm::vec3> ClothSystem::ComputeVelocity(const ParticleState& state) const {
    // Compute the velocities at each pixel (masked by fixed boolean from each particle)
    std::vector<glm::vec3> velocities(state.velocities.size());

    for (size_t i = 0; i < velocities.size(); i++) {
        // Get the particle associated with the ith index
        ParticleObject particle = particles_.at(i);

        // If the particle is fixed, the new velocity is 0.
        if (particle.fixed) {
            velocities.at(i) = glm::vec3(0.0f);
        }
        // If it's not fixed, the velocity stays the same
        else {
            velocities.at(i) = state.velocities.at(i);
        }
    }

    return velocities;

}

std::vector<glm::vec3> ClothSystem::ComputeAcceleration(const ParticleState& state) const {
    // Compute the accelerations for each pixel
    std::vector<glm::vec3> accelerations(state.positions.size());

    // For loop with the intent of looking at each particle
    for (size_t i = 0; i < particles_.size(); i++) {
        // Get the particle associated with the ith index
        ParticleObject particle = particles_.at(i);
        
        if (particle.fixed == true){
            accelerations.at(i) == glm::vec3(0.0f);
            continue;
        }

        // Get the velocity associated with the particle (at first idx)
        glm::vec3 velocity = state.velocities.at(i);

        // Compute gravity
        glm::vec3 grav_force = particle.mass * ScenePhysicsNode::g;
        // Compute drag force
        glm::vec3 drag_force = -10.0f * velocity;
        
        // Add to accelerations at idx i (for particle i). Spring force not yet computed
        accelerations.at(i) = (grav_force + drag_force) / particle.mass;
    }

    // For loop with the intent of looking at each spring
    for (size_t i = 0; i < springs_.size(); i++){
        // Get the spring associated with the ith index
        SpringObject spring = springs_.at(i);
        // Get the particle and particle position associated with the 1st index 
        ParticleObject particle1 = particles_.at(spring.p1_idx);
        glm::vec3 particle1_position = state.positions.at(spring.p1_idx);
        // Get the particle and particle position associated with the 2nd index
        ParticleObject particle2 = particles_.at(spring.p2_idx);
        glm::vec3 particle2_position = state.positions.at(spring.p2_idx);
        
        // Compute the spring force between particles 1 and 2
        glm::vec3 d = particle1_position - particle2_position;
        glm::vec3 spring_force = -spring.k * (glm::length(d) - spring.r) * d/glm::length(d);

        // Add spring force / mass to particle 1 accelerations
        if (!particle1.fixed)
            accelerations.at(spring.p1_idx) += spring_force / particle1.mass;
        // Add spring force / mass to particle 2 accelerations (negative of particle 1)
        if (!particle2.fixed)
            accelerations.at(spring.p2_idx) -= spring_force / particle2.mass;
    }

    return accelerations;
    
}

} // namespace GLOO