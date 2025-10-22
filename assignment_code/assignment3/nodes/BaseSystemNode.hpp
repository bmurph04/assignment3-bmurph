#ifndef BASE_SYSTEM_NODE_H_
#define BASE_SYSTEM_NODE_H_

#include "systems/SimpleSystem.hpp"
#include "ParticleState.hpp"

#include "gloo/SceneNode.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"

namespace GLOO {

class BaseSystemNode : public SceneNode {
    // SceneNode containing system and state information for simple system
    public:
        void Update(double delta_time) override;
        ParticleSystemBase* GetSystem() const { return system_; }

        ParticleState GetState() const { return state_; }
        void SetState(ParticleState state) { state_ = state; }

        virtual void InitializeSystem();
        virtual void InitializeState();        

    protected:
        std::unique_ptr<ParticleSystemBase> system_;
        ParticleState state_;
};

} // namespace GLOO

#endif