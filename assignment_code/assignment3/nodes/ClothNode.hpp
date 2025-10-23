#ifndef CLOTH_NODE_H_
#define CLOTH_NODE_H_

#include "nodes/BaseSystemNode.hpp"
#include "systems/ClothSystem.hpp"

namespace GLOO {

class ClothNode : public BaseSystemNode {
    // SceneNode containing system and state information for cloth system
    public:
        ClothNode(glm::vec3 pos, size_t side_length);
        ClothSystem* GetSystem() const override { return dynamic_cast<ClothSystem*>(system_.get()); }

        void Update(double delta_time) override;

        void InitializeSystem(float mass, float k, float r);
        void InitializeState(float mass, float k, float r, glm::vec3 pos, glm::vec3 vel);
        void InitializeGeometry();
    
    private:
        std::vector<SceneNode*> sphere_nodes_;
        size_t num_particles_;
    
};
} // namespace GLOO

#endif