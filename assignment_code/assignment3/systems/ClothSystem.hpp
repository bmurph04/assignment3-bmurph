#ifndef CLOTH_SYSTEM_H_
#define CLOTH_SYSTEM_H_

#include "ParticleSystemBase.hpp"

namespace GLOO {
class ClothSystem : public ParticleSystemBase {
    public:
        ClothSystem();

        ~ClothSystem() override;

        ParticleState ComputeTimeDerivative(const ParticleState& state, float time) const override;
};

} // namespace GLOO

#endif