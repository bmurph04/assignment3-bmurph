#include "nodes/PendulumNode.hpp"

#include "systems/PendulumSystem.hpp"
#include "nodes/ScenePhysicsNode.hpp"

#include "gloo/debug/PrimitiveFactory.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

#include <glm/gtx/string_cast.hpp>


namespace GLOO {

PendulumNode::PendulumNode(glm::vec3 pos, size_t num_particles) : num_particles_(num_particles){ 
    this->GetTransform().SetPosition(pos);

    // Create geometry
    sphere_mesh_ = PrimitiveFactory::CreateSphere(0.08f, 25, 25);
    shader_ = std::make_shared<PhongShader>();

    float default_mass = 0.05f;
    float default_k = 2.5f;
    float default_r = 0.05f;
    glm::vec3 default_pos = this->GetTransform().GetPosition();
    glm::vec3 default_vel = {0.3f, 0.0f, -3.5f};

    InitializeSystem(default_mass, default_k, default_r);
    InitializeState(default_mass, default_k, default_r, default_pos, default_vel);
    InitializeGeometry();

}

void PendulumNode::InitializeSystem(float mass, float k, float r) {
    // Initialize the system for the pendulum node
    system_ = make_unique<PendulumSystem>();
    
    // Initialize particles in pendulum system with default properties, reachable by index
    for (size_t i = 0; i < num_particles_; i++){
        PendulumParticle new_particle{mass, false};
        // If at root, set fixed to true
        if (i == 0)
            new_particle.fixed = true;
    
        this->GetSystem()->GetParticles().push_back(new_particle);
    }

    // Initialize springs in pendulum system with default properties, reachable by index
    for (size_t i = 0; i < num_particles_-1; i++){
        PendulumSpring new_spring{i, i+1, k, r};
        this->GetSystem()->GetSprings().push_back(new_spring);
    }

}

void PendulumNode::InitializeState(float mass, float k, float r, glm::vec3 pos, glm::vec3 vel) {
    // Initialize the state for the pendulum node
    float g = glm::abs(ScenePhysicsNode::g.y);

    // vector of size num_particles for the particles in the system
    std::vector<glm::vec3> state_positions(num_particles_);
    std::vector<glm::vec3> state_velocities(num_particles_);
    
    for (size_t i = 0; i < num_particles_; i++) {
        state_positions.at(i) = pos;
        state_velocities.at(i) = vel;
        
        float mass_below = mass * ((num_particles_-1) - i);
        // New equilibrium length is x = r + mg/k. Use this to set the initial points at an equilibrium length
        pos.y -= r + (mass_below*g/k);
        vel.z -= 0.5f;
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