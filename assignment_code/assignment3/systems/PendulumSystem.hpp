#ifndef PENDULUM_SYSTEM_H_
#define PENDULUM_SYSTEM_H_

#include "ParticleSystemBase.hpp"
#include "ParticleState.hpp"

namespace GLOO {
class PendulumSystem : public ParticleSystemBase {
    public:
        PendulumSystem();
        ~PendulumSystem() override;

        ParticleState ComputeTimeDerivative(const ParticleState& state, float time) const override;
};

} // namespace GLOO

#endif