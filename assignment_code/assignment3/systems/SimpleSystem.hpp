#ifndef SIMPLE_SYSTEM_H_
#define SIMPLE_SYSTEM_H_

#include "ParticleSystemBase.hpp"
#include "ParticleState.hpp"

#include "gloo/SceneNode.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"

namespace GLOO {

class SimpleSystem : public ParticleSystemBase {
    public:
        SimpleSystem();
        ~SimpleSystem() override;

        ParticleState ComputeTimeDerivative(const ParticleState& state, float time) const override;
        
};

} // namespace GLOO

#endif