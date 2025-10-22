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
        ParticleSystemBase* GetSystem() const { return system_.get(); }

        ParticleState GetState() const { return state_; }
        void SetState(ParticleState state) { state_ = state; }

        virtual void InitializeSystem() = 0;
        virtual void InitializeState() = 0;        

    protected:
        std::unique_ptr<ParticleSystemBase> system_;
        ParticleState state_;
};

} // namespace GLOO

#endif