#include "nodes/ScenePhysicsNode.hpp"

#include "ParticleState.hpp"

#include "nodes/SimpleNode.hpp"
#include "nodes/PendulumNode.hpp"
#include "nodes/ClothNode.hpp"

#include "integrators/IntegratorType.hpp"
#include "integrators/IntegratorFactory.hpp"
#include "integrators/IntegratorBase.hpp"

#include <vector>

// // might not be needed
// #include "ParticleSystemBase.hpp"
// #include "SimpleSystem.hpp"
// #include "PendulumSystem.hpp"
// #include "ClothSystem.hpp"
// #include "SystemType.hpp"

namespace GLOO {

ScenePhysicsNode::ScenePhysicsNode(IntegratorType integrator_type, float step, double time_since_update, double time_accumulated) 
    : SceneNode(), step_(step), time_since_start_(time_since_update), time_accumulated_(time_accumulated) {
    
    integrator_ = IntegratorFactory::CreateIntegrator<ParticleSystemBase, ParticleState>(integrator_type);
    
    InitializeSystemNodes();
    
}

void ScenePhysicsNode::InitializeSystemNodes() {
    // Initialize the systems that will be displayed in the scene as nodes
    auto simple_node = make_unique<SimpleNode>();
    // auto pendulum_node = make_unique<PendulumNode>();
    // auto cloth_node = make_unique<ClothNode>();

    system_nodes_.emplace_back(simple_node.get());
    // system_nodes_.emplace_back(pendulum_node);
    // system_nodes_.emplace_back(cloth_node);

    this->AddChild(std::move(simple_node));
    // this->AddChild(std::move(pendulum_node));
    // this->AddChild(std::move(cloth_node));
}

void ScenePhysicsNode::Update(double delta_time) { 
    time_since_start_ += delta_time;
    
    while (time_accumulated_ < time_since_start_){
        float start_time = time_accumulated_;
        
        // Update each state attached to the node
        for (BaseSystemNode* system_node : system_nodes_) {
            ParticleSystemBase* system = system_node->GetSystem();
            ParticleState state = system_node->GetState();
            
            ParticleState new_state = integrator_->Integrate(*system, state, start_time, step_);
            
            system_node->SetState(new_state);
        }

        time_accumulated_ += step_;
    }
    
    // Update each system attached to the node
    for (BaseSystemNode* system_node : system_nodes_) {
        system_node->Update(delta_time);
    }
}


} // namespace GLOO
