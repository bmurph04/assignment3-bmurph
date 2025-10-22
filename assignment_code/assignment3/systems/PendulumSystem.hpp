#ifndef PENDULUM_SYSTEM_H_
#define PENDULUM_SYSTEM_H_

#include "systems/ParticleSystemBase.hpp"
#include "ParticleState.hpp"
#include "objects/PendulumParticle.hpp"
#include "objects/PendulumSpring.hpp"

#include <glm/glm.hpp>

namespace GLOO {
class PendulumSystem : public ParticleSystemBase {
    public:
        PendulumSystem();

        ParticleState ComputeTimeDerivative(const ParticleState& state, float time) const override;
        //ParticleState ComputeAcceleration();       

};
} // namespace GLOO

#endif