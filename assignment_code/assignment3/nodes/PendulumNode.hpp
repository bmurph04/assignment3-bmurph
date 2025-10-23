#ifndef PENDULUM_NODE_H_
#define PENDULUM_NODE_H_

#include "nodes/BaseSystemNode.hpp"
#include "systems/PendulumSystem.hpp"
#include "ParticleState.hpp"
#include "objects/ParticleObject.hpp"
#include "objects/SpringObject.hpp"

#include "gloo/SceneNode.hpp"
#include "gloo/VertexObject.hpp"
#include "gloo/shaders/ShaderProgram.hpp"

namespace GLOO {

class PendulumNode : public BaseSystemNode { 
    // SceneNode contianing system and state information for pendulum system
    public:
        PendulumNode(glm::vec3 pos, size_t num_particles);
        PendulumSystem* GetSystem() const override { return dynamic_cast<PendulumSystem*>(system_.get()); }

        void Update(double delta_time) override;

        void InitializeSystem(float mass, float k, float r);
        void InitializeState(float mass, float k, float r, glm::vec3 pos, glm::vec3 vel);
        void InitializeGeometry();

        void ExtendPendulum(float mass, glm::vec3 position, glm::vec3 velocity, float k, float r, bool fixed = false);
    
    private:
        // std::vector<SceneNode*> particle_nodes;
        std::shared_ptr<VertexObject> sphere_mesh_;
        std::shared_ptr<ShaderProgram> shader_;

        std::vector<SceneNode*> sphere_nodes_;
        size_t num_particles_;

};

} // namespace GLOO

#endif