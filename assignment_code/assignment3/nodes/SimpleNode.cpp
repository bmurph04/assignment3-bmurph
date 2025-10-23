#include "nodes/SimpleNode.hpp"

#include "gloo/debug/PrimitiveFactory.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

namespace GLOO {

SimpleNode::SimpleNode(glm::vec3 pos) {
    this->GetTransform().SetPosition(pos);

    // Create geometry
    sphere_mesh_ = PrimitiveFactory::CreateSphere(0.1f, 25, 25);
    shader_ = std::make_shared<PhongShader>();

    glm::vec3 default_pos = {0.5f, 0.75f, 0.0f};
    glm::vec3 default_vel = {0.0f, 0.0f, 0.0f};

    InitializeSystem();
    InitializeState(default_pos, default_vel);
    InitializeGeometry();
}

void SimpleNode::InitializeSystem() {
    // Initialize the system for the simple node
    system_ = make_unique<SimpleSystem>();

    // Nothing else to do for system initialization of simple node
}

void SimpleNode::InitializeState(glm::vec3 pos, glm::vec3 vel) {
    // Initialize the state for the simple node

    // Vector of size 1 for the single sphere
    std::vector<glm::vec3> simple_state_positions(1);
    std::vector<glm::vec3> simple_state_velocities(1);
    simple_state_positions.at(0) = pos;
    simple_state_velocities.at(0) = vel;

    ParticleState simple_state{simple_state_positions, simple_state_velocities};
    state_ = simple_state;

}

void SimpleNode::InitializeGeometry() {
    // Initialize geometry that we see in the scene for simple
    auto sphere_node = make_unique<SceneNode>();
    sphere_node->CreateComponent<ShadingComponent>(shader_);
    sphere_node->CreateComponent<RenderingComponent>(sphere_mesh_);
    
    sphere_node->GetTransform().SetPosition(this->GetTransform().GetPosition());

    this->AddChild(std::move(sphere_node));
}

void SimpleNode::Update(double delta_time) {
    // Update function of ScenePhysicsNode for integrator has been run
    // Do specific SimpleNode update behavior
    glm::vec3 position = state_.positions.at(0);
    this->GetTransform().SetPosition(position);
}

}

