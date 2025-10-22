#include "nodes/PendulumNode.hpp"

#include "systems/PendulumSystem.hpp"

#include "gloo/debug/PrimitiveFactory.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

namespace GLOO {

PendulumNode::PendulumNode(size_t num_particles) : num_particles_(num_particles){ 

    // Initialize the system for the pendulum node
    system_ = make_unique<PendulumSystem>();

    // Create geometry
    sphere_mesh_ = PrimitiveFactory::CreateSphere(0.2f, 25, 25);
    shader_ = std::make_shared<PhongShader>();

    InitializeSystem();
    InitializeState();

}

void PendulumNode::InitializeSystem() {
    // Initialize particles in pendulum system with default properties, reachable by index
    float mass = 1;
    float k = 0.5;
    float r = 0.5;

    for (size_t i = 0; i < num_particles_; i++){
        // If at root, just create first root particle and set fixed to true
        if (i == 0){
            auto root_particle = PendulumParticle{mass, true};
            particles_.push_back(root_particle);
            continue;
        }
        else {
            // Call ExtendPendulum
            // ExtendPendulum(mass, position, velocity);
        }

        // position.y -= 5.0f;
    }

}

void PendulumNode::InitializeState() {
    // Initialize the state for the pendulum node

    // vector of size num_particles for the particles in the system
    std::vector<glm::vec3> state_positions(num_particles_);
    std::vector<glm::vec3> state_velocities(num_particles_);

    glm::vec3 position(-10.0f, 0.0f, 0.0f);
    glm::vec3 velocity(0.5f, 0.0f, -0.5f);

    for (size_t i = 0; i < num_particles_; i++) {
        state_positions.at(i) = position;
        state_positions.at(i) = velocity;

        position.y -= 5.0f;
    }

    ParticleState pendulum_state{state_positions, state_velocities};
    state_ = pendulum_state;

}

void PendulumNode::ExtendPendulum(float mass, glm::vec3 position, glm::vec3 velocity, bool fixed) {
    // // Assuming a linear chain as in the sample solution where each particle has at most one parent and one child.

    // // Create a particle
    // PendulumParticle new_particle{mass, fixed};
    // // Add particle to list of particles
    // particles_.push_back(new_particle);
    // // Create a spring connecting this particle with the last
    // PendulumSpring new_spring{particles_.size()-2, particles_.size()-1, k, r}
    

}

void PendulumNode::Update(double delta_time) { }

}