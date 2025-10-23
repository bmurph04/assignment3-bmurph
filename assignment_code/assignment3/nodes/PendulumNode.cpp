#include "nodes/PendulumNode.hpp"

#include "systems/PendulumSystem.hpp"

#include "gloo/debug/PrimitiveFactory.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

#include <glm/gtx/string_cast.hpp>


namespace GLOO {

PendulumNode::PendulumNode(size_t num_particles) : num_particles_(num_particles){ 

    // Create geometry
    sphere_mesh_ = PrimitiveFactory::CreateSphere(0.1f, 25, 25);
    shader_ = std::make_shared<PhongShader>();

    InitializeSystem();
    InitializeState();
    InitializeGeometry();

}

void PendulumNode::InitializeSystem() {
    // Initialize the system for the pendulum node
    system_ = make_unique<PendulumSystem>();
    
    // Initialize particles in pendulum system with default properties, reachable by index
    float mass = 1;
    for (size_t i = 0; i < num_particles_; i++){
        PendulumParticle new_particle{mass, false};
        // If at root, set fixed to true
        if (i == 0)
            new_particle.fixed = true;
    
        this->GetSystem()->GetParticles().push_back(new_particle);
    }

    // Initialize springs in pendulum system with default properties, reachable by index
    float k = 20;
    float r = 1;
    for (size_t i = 0; i < num_particles_-1; i++){
        PendulumSpring new_spring{i, i+1, k, r};
        this->GetSystem()->GetSprings().push_back(new_spring);
    }

}

void PendulumNode::InitializeState() {
    // Initialize the state for the pendulum node

    // vector of size num_particles for the particles in the system
    std::vector<glm::vec3> state_positions(num_particles_);
    std::vector<glm::vec3> state_velocities(num_particles_);

    glm::vec3 position(-1.0f, 0.0f, 0.0f);
    glm::vec3 velocity(0.5f, 0.0f, -0.5f);

    for (size_t i = 0; i < num_particles_; i++) {
        state_positions.at(i) = position;
        state_velocities.at(i) = velocity;

        position.y -= 0.75f;
    }

    ParticleState pendulum_state{state_positions, state_velocities};
    state_ = pendulum_state;

}

void PendulumNode::InitializeGeometry() {
    // Initialize geometry that we see in the scene for pendulum
    for (size_t i = 0; i < this->GetSystem()->GetParticles().size(); i++){
        auto sphere_node = make_unique<SceneNode>();
        sphere_node->CreateComponent<ShadingComponent>(shader_);
        sphere_node->CreateComponent<RenderingComponent>(sphere_mesh_);
        sphere_node->GetTransform().SetPosition(state_.positions.at(i));

        sphere_nodes_.push_back(sphere_node.get());
        this->AddChild(std::move(sphere_node));
    }
}

void PendulumNode::ExtendPendulum(float mass, glm::vec3 position, glm::vec3 velocity, float k, float r, bool fixed) {
    // // Assuming a linear chain as in the sample solution where each particle has at most one parent and one child.

    // // Create a particle
    // PendulumParticle new_particle{mass, fixed};
    // // Add particle to list of particles
    // particles_.push_back(new_particle);
    // // Create a spring connecting this particle with the last
    // PendulumSpring new_spring{particles_.size()-2, particles_.size()-1, k, r}
    

}

void PendulumNode::Update(double delta_time) { 
    // Update function of ScenePhysicsNode for integrator has been run
    // Do specific PendulumNode update behavior
    for (size_t i = 0; i < sphere_nodes_.size(); i++){
        glm::vec3 position = state_.positions.at(i);
        SceneNode* sphere_node = sphere_nodes_.at(i);

        sphere_node->GetTransform().SetPosition(position);
    }
}

} // namespace GLOO