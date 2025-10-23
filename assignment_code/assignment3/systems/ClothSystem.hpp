#ifndef CLOTH_SYSTEM_H_
#define CLOTH_SYSTEM_H_

#include "systems/ParticleSystemBase.hpp"
#include "objects/ParticleObject.hpp"
#include "objects/SpringObject.hpp"
#include "ParticleState.hpp"

#include <glm/glm.hpp>

namespace GLOO {
class ClothSystem : public ParticleSystemBase {
    public:
        ClothSystem() { };

        std::vector<ParticleObject>& GetParticles() { return particles_; }
        std::vector<SpringObject>& GetSprings() { return springs_; }

        ParticleState ComputeTimeDerivative(const ParticleState& state, float time) const override;

        std::vector<glm::vec3> ComputeVelocity(const ParticleState& state) const;
        std::vector<glm::vec3> ComputeAcceleration(const ParticleState& state) const;
    
    private:
        std::vector<ParticleObject> particles_;
        std::vector<SpringObject> springs_;
};

} // namespace GLOO

#endif