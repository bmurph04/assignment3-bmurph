#ifndef SCENE_PHYSICS_NODE_H_
#define SCENE_PHYSICS_NODE_H_

#include "gloo/SceneNode.hpp"
#include "integrators/IntegratorBase.hpp"
#include "integrators/IntegratorType.hpp"
#include "systems/ParticleSystemBase.hpp"
#include "nodes/BaseSystemNode.hpp"
#include "ParticleState.hpp"

#include <vector>

namespace GLOO {

// Create derived SceneNode that handles state, integrator, and physical system
class ScenePhysicsNode : public SceneNode {
    public:
        ScenePhysicsNode(IntegratorType integrator_type, float step, double time_since_update, double time_accumulated);
        
        void InitializeSystemNodes();

        void Update(double delta_time) override;

        static const glm::vec3 g;
        static const float b;
    
    private:
        std::vector<BaseSystemNode*> system_nodes_;
        std::unique_ptr<IntegratorBase<ParticleSystemBase, ParticleState>> integrator_;
        float step_;

        double time_since_start_;
        double time_accumulated_;
};

} // namespace GLOO

#endif
