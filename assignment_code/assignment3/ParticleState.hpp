#ifndef PARTICLE_STATE_H_
#define PARTICLE_STATE_H_

#include <vector>
#include <stdexcept>

#include <glm/glm.hpp>

// added
#include "systems/SystemType.hpp"

namespace GLOO {
struct ParticleState {
  // The state of a particle system: positions and velocities.
  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> velocities;

  ParticleState& operator+=(const ParticleState& rhs) {
    // if (type != rhs.type)
    //   throw std::runtime_error("LHS type \"" + std::string(SystemTypeToString(type)) + "\" and RHS type \"" + std::string(SystemTypeToString(rhs.type)) "\" do not match in arithmetic operation");
    if (positions.size() != rhs.positions.size() ||
        velocities.size() != rhs.velocities.size() ||
        positions.size() != rhs.velocities.size()) {
      throw std::runtime_error(
          "Cannot add particle states with inconsistent sizes!");
    }

    for (size_t i = 0; i < positions.size(); i++) {
      positions[i] += rhs.positions[i];
      velocities[i] += rhs.velocities[i];
    }
    return *this;
  }

  ParticleState& operator*=(float k) {
    for (size_t i = 0; i < positions.size(); i++) {
      positions[i] *= k;
      velocities[i] *= k;
    }
    return *this;
  }
};

// Operators, optimized via overloading + std::move.
inline ParticleState operator+(ParticleState s1, const ParticleState& s2) {
  // if (s1.type != s2.type)
  //     throw std::runtime_error("LHS type \"" + std::string(SystemTypeToString(s1.type)) + "\" and RHS type \"" + std::string(SystemTypeToString(s2.type)) "\" do not match in arithmetic operation");
  
  s1 += s2;
  return s1;
}
inline ParticleState operator+(const ParticleState& s1, ParticleState&& s2) {
  // if (s1.type != s2.type)
  //     throw std::runtime_error("LHS type \"" + std::string(SystemTypeToString(s1.type)) + "\" and RHS type \"" + std::string(SystemTypeToString(s2.type)) "\" do not match in arithmetic operation");
  
  s2 += s1;
  return std::move(s2);
}
inline ParticleState operator*(ParticleState s1, float k) {
  s1 *= k;
  return s1;
}
inline ParticleState operator*(float k, ParticleState s1) {
  s1 *= k;
  return s1;
}
}  // namespace GLOO

#endif
