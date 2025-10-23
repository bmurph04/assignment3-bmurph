#include "nodes/ClothNode.hpp"

#include "objects/ParticleObject.hpp"

#include "gloo/debug/PrimitiveFactory.hpp"
#include "gloo/shaders/PhongShader.hpp"

namespace GLOO {
 
ClothNode::ClothNode(glm::vec3 pos, size_t side_length) : side_length_(side_length) {
    // Initialize position and number of particles using parameters
    this->GetTransform().SetPosition(pos);
    num_particles_ = side_length * side_length;

    // Create geometry
    sphere_mesh_ = PrimitiveFactory::CreateSphere(0.03f, 25, 25);
    shader_ = std::make_shared<PhongShader>();

    float default_mass = 0.05f;
    float default_k = 2.5f;
    float default_r = 0.05f;
    glm::vec3 default_pos = this->GetTransform().GetPosition();
    glm::vec3 default_vel = {0.3f, 0.0f, -3.5f};

    InitializeSystem(default_mass, default_k, default_r);
    // InitializeState(default_mass, default_k, default_r, default_pos, default_vel);
    // InitializeGeometry();

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

}

void ClothNode::InitializeGeometry() {

}

void ClothNode::Update(double delta_time) {

}

} // namespace GLOO