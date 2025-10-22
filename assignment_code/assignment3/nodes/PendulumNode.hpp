#ifndef PENDULUM_NODE_H_
#define PENDULUM_NODE_H_

#include "nodes/BaseSystemNode.hpp"
#include "systems/PendulumSystem.hpp"
#include "ParticleState.hpp"
#include "objects/PendulumParticle.hpp"
#include "objects/PendulumSpring.hpp"

#include "gloo/SceneNode.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"

namespace GLOO {

class PendulumNode : public BaseSystemNode { 
    // SceneNode contianing system and state information for pendulum system
    public:
        PendulumNode(size_t num_particles);
        void Update(double delta_time) override;

        void InitializeState() override;
        void InitializeSystem() override;

        void ExtendPendulum(float mass, glm::vec3 position, glm::vec3 velocity, bool fixed = false);
    
    private:
        // std::vector<SceneNode*> particle_nodes;
        std::shared_ptr<VertexObject> sphere_mesh_;
        std::shared_ptr<ShaderProgram> shader_;

        std::unique_ptr<PendulumSystem> system_;
        ParticleState state_;

        std::vector<PendulumParticle> particles_;
        std::vector<PendulumSpring> springs_;
        size_t num_particles_;

};

} // namespace GLOO

#endif