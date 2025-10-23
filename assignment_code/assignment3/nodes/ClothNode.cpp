#include "nodes/ClothNode.hpp"

#include "objects/ParticleObject.hpp"
#include "nodes/ScenePhysicsNode.hpp"

#include "gloo/debug/PrimitiveFactory.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

#include <glm/gtx/string_cast.hpp>

namespace GLOO {
 
ClothNode::ClothNode(glm::vec3 pos, size_t side_length) : side_length_(side_length) {
    // Initialize position and number of particles using parameters
    this->GetTransform().SetPosition(pos);
    num_particles_ = side_length * side_length;

    // Create geometry
    sphere_mesh_ = PrimitiveFactory::CreateSphere(0.08f, 25, 25);
    shader_ = std::make_shared<PhongShader>();

    float default_mass = 0.05f;
    float default_k = 2.5f;
    float default_r = 0.05f;
    glm::vec3 default_pos = this->GetTransform().GetPosition() + glm::vec3(-0.5f, 0.0f, 0.0f);
    glm::vec3 default_vel = {0.3f, 0.0f, -3.5f};

    InitializeSystem(default_mass, default_k, default_r);
    InitializeState(default_mass, default_k, default_r, default_pos, default_vel);
    InitializeGeometry();

}

void ClothNode::InitializeSystem(float mass, float k, float r) {
    // Initialize the system for the cloth node
    system_ = make_unique<ClothSystem>();

    // Initialize particles in cloth system with default properties, reachable by index
    for (size_t i = 0; i < num_particles_; i++){
        ParticleObject new_particle{mass, false};
        // If at a particle in the first row, set fixed to true. Row major indexing will be used later
        if (i < side_length_)
            new_particle.fixed = true;
        
        this->GetSystem()->GetParticles().push_back(new_particle);
    }

}

void ClothNode::InitializeState(float mass, float k, float r, glm::vec3 pos, glm::vec3 vel) {
    // Initialize the state for the cloth node
    float g = glm::abs(ScenePhysicsNode::g.y);
    float default_x = pos.x;

    // vector of size num_particles for the particles in the system
    std::vector<glm::vec3> state_positions(num_particles_);
    std::vector<glm::vec3> state_velocities(num_particles_);
    std::cout << "num_particles: " << num_particles_ << std::endl;

    // Treat the positions and velocities as a 2D array, indexed by y*side_length_ + x
    for (size_t y = 0; y < side_length_; y++) {
        
        float mass_below = mass * ((side_length_-1) - y);

        for (size_t x = 0; x < side_length_; x++) {
            size_t state_idx = y * side_length_ + x;

            state_positions.at(state_idx) = pos;
            state_velocities.at(state_idx) = vel;
            pos.x += 0.5f;
        }
        
        pos.x = default_x;
        // New vertical equilibrium length is x = r + mg/k. Use this to set the initial points at an equilibrium length
        pos.y -= r + (mass_below*g/k);

        vel.z -= 0.5f;
    }

    ParticleState cloth_state{state_positions, state_velocities};
    state_ = cloth_state;
}

void ClothNode::InitializeGeometry() {
    // Initialize geometry that we see in the scene for cloth
    for (size_t i = 0; i < this->GetSystem()->GetParticles().size(); i++){
        auto sphere_node = make_unique<SceneNode>();
        sphere_node->CreateComponent<ShadingComponent>(shader_);
        sphere_node->CreateComponent<RenderingComponent>(sphere_mesh_);
        sphere_node->GetTransform().SetPosition(state_.positions.at(i));

        sphere_nodes_.push_back(sphere_node.get());
        this->AddChild(std::move(sphere_node));
    }
}

void ClothNode::Update(double delta_time) {
    // Update function of ScenePhysicsNode for integrator has been run
    // Do specific ClothNode update behavior
    for (size_t i = 0; i < sphere_nodes_.size(); i++){
        glm::vec3 position = state_.positions.at(i);
        SceneNode* sphere_node = sphere_nodes_.at(i);

        sphere_node->GetTransform().SetPosition(position);
    }

}

} // namespace GLOO