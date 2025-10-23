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
        SimpleNode(glm::vec3 pos);
        void Update(double delta_time) override;

        void InitializeSystem();
        void InitializeState(glm::vec3 pos, glm::vec3 vel);  
        void InitializeGeometry();      
        
};

} // namespace GLOO

#endif