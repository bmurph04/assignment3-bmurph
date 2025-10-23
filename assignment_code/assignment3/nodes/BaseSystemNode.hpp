#ifndef BASE_SYSTEM_NODE_H_
#define BASE_SYSTEM_NODE_H_

#include "systems/ParticleSystemBase.hpp"
#include "ParticleState.hpp"

#include "gloo/SceneNode.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"

namespace GLOO {

class BaseSystemNode : public SceneNode {
    // SceneNode containing system and state information for simple system
    public:
        virtual ParticleSystemBase* GetSystem() const { return system_.get(); }

        ParticleState GetState() const { return state_; }
        void SetState(ParticleState state) { state_ = state; }

    protected:
        std::unique_ptr<ParticleSystemBase> system_;
        ParticleState state_;

        std::shared_ptr<VertexObject> sphere_mesh_;
        std::shared_ptr<ShaderProgram> shader_;
};

} // namespace GLOO

#endif