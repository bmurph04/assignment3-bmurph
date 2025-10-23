#ifndef PENDULUM_PARTICLE_H_
#define PENDULUM_PARTICLE_H_

#include "objects/SpringObject.hpp"

#include <vector>

namespace GLOO{

struct ParticleObject {
   // Holds information about a particle's mass and whether its fixed or not
   float mass;
   bool fixed;
};

} // namespace GLOO

#endif