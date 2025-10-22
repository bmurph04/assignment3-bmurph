#include "nodes/PendulumNode.hpp"

#include "systems/PendulumSystem.hpp"

#include "gloo/debug/PrimitiveFactory.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

namespace GLOO {

    

PendulumNode::PendulumNode(int num_particles) { 

    // Initialize the system for the pendulum node
    system_ = make_unique<PendulumSystem>(num_particles);

    // Create geometry
    sphere_mesh_ = PrimitiveFactory::CreateSphere(0.2f, 25, 25);
    shader_ = std::make_shared<PhongShader>();

    InitializeState();
    InitializeSystem();

}

void PendulumNode::InitializeState() {
    // Initialize the state for the pendulum node

    // vector of size num_particles for the particles in the system
    std::vector<glm::vec3> pendulum_state_positions(system_->GetNumParticles());
    std::vector<glm::vec3> pendulum_state_velocities(system_->GetNumParticles());

}

void PendulumNode::Update(double delta_time) { }

}