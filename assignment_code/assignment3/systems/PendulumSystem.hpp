#ifndef PENDULUM_SYSTEM_H_
#define PENDULUM_SYSTEM_H_

#include "ParticleSystemBase.hpp"
#include "ParticleState.hpp"

#include <glm/glm.hpp>

namespace GLOO {
class PendulumSystem : public ParticleSystemBase {
    public:
        PendulumSystem(int num_particles);
        ~PendulumSystem() override;

        int GetNumParticles() const { return num_particles_; }

        void CreatePendulumParticle(float mass, PendulumParticle* parent = nullptr, float position = glm::vec3(0.0f), bool fixed = false);

        ParticleState ComputeTimeDerivative(const ParticleState& state, float time) const override;
        ParticleState ComputeAcceleration();

    private:
        int num_particles_;

};
} // namespace GLOO

#endif