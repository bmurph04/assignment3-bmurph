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

        std::vector<PendulumParticle>& GetParticles() { return particles_; }
        std::vector<PendulumSpring>& GetSprings() { return springs_; }

        ParticleState ComputeTimeDerivative(const ParticleState& state, float time) const override;
        
        std::vector<glm::vec3> ComputeVelocity(const ParticleState& state) const;
        std::vector<glm::vec3> ComputeAcceleration(const ParticleState& state) const;
    
    private:
        std::vector<PendulumParticle> particles_;
        std::vector<PendulumSpring> springs_;

};
} // namespace GLOO

#endif