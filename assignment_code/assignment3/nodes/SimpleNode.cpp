#include "nodes/SimpleNode.hpp"

#include "gloo/debug/PrimitiveFactory.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

namespace GLOO {

SimpleNode::SimpleNode() {

    // Initialize the system and state for the simple node
    system_ = make_unique<SimpleSystem>();
    system_raw_ = system_.get();

    // Create geometry
    sphere_mesh_ = PrimitiveFactory::CreateSphere(0.2f, 25, 25);
    shader_ = std::make_shared<PhongShader>();

    InitializeState();
 
}


void SimpleNode::InitializeState() {
    // Initialize the state for the simple node

    // Vector of size 1 for the single sphere
    std::vector<glm::vec3> simple_state_positions(1);
    std::vector<glm::vec3> simple_state_velocities(1);

    auto sphere_node = make_unique<SceneNode>();
    sphere_node->CreateComponent<ShadingComponent>(shader_);
    sphere_node->CreateComponent<RenderingComponent>(sphere_mesh_);
    sphere_node->GetTransform().SetPosition(this->GetTransform().GetPosition());

    //sphere_node_ = sphere_node.get();
    this->AddChild(std::move(sphere_node));

    glm::vec3 position = glm::vec3(0.5f, 0.75f, 0.5f);
    glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    
    simple_state_positions.at(0) = position;
    simple_state_velocities.at(0) = velocity;

    ParticleState simple_state{simple_state_positions, simple_state_velocities};
    state_ = simple_state;

}

void SimpleNode::Update(double delta_time) {
    // Update function of ScenePhysicsNode for integrator has been run
    // Do specific SimpleNode update behavior
    glm::vec3 position = state_.positions.at(0);
    this->GetTransform().SetPosition(position);
}

}

