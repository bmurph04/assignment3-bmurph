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
        ParticleSystemBase* GetSystem() const { return system_raw_; }

        ParticleState GetState() const { return state_; }
        void SetState(ParticleState state) { state_ = state; }

        void InitializeSystem();
        void InitializeState();        

    private:
        std::unique_ptr<ParticleSystemBase> system_;
        ParticleSystemBase* system_raw_;
        ParticleState state_;
};

} // namespace GLOO

#endif