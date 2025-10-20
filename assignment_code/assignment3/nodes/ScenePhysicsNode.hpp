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
        ScenePhysicsNode(IntegratorType integrator_type, float step, double time_since_update);
        
        void InitializeSystemNodes();

        void Update(double delta_time) override;
    
    private:
        std::vector<BaseSystemNode*> system_nodes_;
        std::unique_ptr<IntegratorBase<ParticleSystemBase, ParticleState>> integrator_;
        float step_;

        double time_since_start_;
};

} // namespace GLOO

#endif
