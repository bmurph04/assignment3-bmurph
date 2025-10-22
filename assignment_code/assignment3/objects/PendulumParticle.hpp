#ifndef PENDULUM_PARTICLE_H_
#define PENDULUM_PARTICLE_H_

#include "objects/PendulumSpring.hpp"

#include <vector>

namespace GLOO{

struct PendulumParticle {
   // Holds information about a particle's mass, attached springs, and whether its fixed or not
   float mass;
   bool fixed;
   std::vector<PendulumSpring> springs;
}

} // namespace GLOO
