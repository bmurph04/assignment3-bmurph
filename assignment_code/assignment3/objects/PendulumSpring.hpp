#ifndef PENDULUM_SPRING_H_
#define PENDULUM_SPRING_H_

namespace GLOO{
struct PendulumSpring {
    // Holds information about the spring constant k, rest length r, and particles it's connected to.
    size_t p1_idx; // Index of the first particle
    size_t p2_idx; // Index of the second particle
    float k;
    float r;
};

}

#endif