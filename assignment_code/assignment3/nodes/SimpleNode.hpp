#ifndef SIMPLE_NODE_H_
#define SIMPLE_NODE_H_

#include "systems/SimpleSystem.hpp"
#include "ParticleState.hpp"
#include "nodes/BaseSystemNode.hpp"

#include "gloo/SceneNode.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"

namespace GLOO {

class SimpleNode : public BaseSystemNode {
    // SceneNode containing system and state information for simple system
    public:
        SimpleNode();
        void Update(double delta_time) override;

        void InitializeSystem() override;
        void InitializeState() override;        

    private:
        std::shared_ptr<VertexObject> sphere_mesh_;
        std::shared_ptr<ShaderProgram> shader_;

};

} // namespace GLOO

#endif