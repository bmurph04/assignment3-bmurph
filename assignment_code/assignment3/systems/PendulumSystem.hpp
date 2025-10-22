#ifndef PENDULUM_SYSTEM_H_
#define PENDULUM_SYSTEM_H_

#include "ParticleSystemBase.hpp"
#include "ParticleState.hpp"
#include "PendulumParticle.hpp"
#include "PendulumSpring.hpp"

#include <utils.hpp>
#include <glm/glm.hpp>

namespace GLOO {
class PendulumSystem : public ParticleSystemBase {
    public:
        PendulumSystem(int num_particles);
        ~PendulumSystem() override;

        int GetNumParticles() const { return num_particles_; }

        ParticleState ComputeTimeDerivative(const ParticleState& state, float time) const override;
        ParticleState ComputeAcceleration();

    private:
        int num_particles_;
        std::vector<PendulumParticle> particles_;
        std::vector<PendulumSpring> springs_;

};
} // namespace GLOO

#endif