#ifndef PENDULUM_NODE_H_
#define PENDULUM_NODE_H_

#include "systems/PendulumSystem.hpp"
#include "ParticleState.hpp"
#include "nodes/BaseSystemNode.hpp"

#include "gloo/SceneNode.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"

namespace GLOO {

class PendulumNode : public BaseSystemNode { 
    // SceneNode contianing system and state information for pendulum system
    public:
        PendulumNode();
        void Update(double delta_time) override;
    
    private:
        std::vector<SceneNode*> sphere_nodes;
        std::shared_ptr<VertexObject> sphere_mesh_;
        std::shared_ptr<ShaderProgram> shader_;

        std::unique_ptr<PendulumSystem> system_;
        ParticleState state_;

};

} // namespace GLOO

#endif