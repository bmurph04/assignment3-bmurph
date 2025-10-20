#ifndef CLOTH_NODE_H_
#define CLOTH_NODE_H_

#include "systems/PendulumSystem.hpp"
#include "ParticleState.hpp"
#include "nodes/BaseSystemNode.hpp"

#include "gloo/SceneNode.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"

namespace GLOO {

class ClothNode : public BaseSystemNode {
    // SceneNode containing system and state information for cloth system
    public:
        ClothNode();
        void Update(double delta_time) override;

    private:
        // shapes not initialized

        std::unique_ptr<ClothNode> system_;
        ParticleState state_;
};

} // namespace GLOO

#endif