#include "SimpleSystem.hpp"
#include "ParticleState.hpp"

#include "gloo/debug/PrimitiveFactory.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"

namespace GLOO{

SimpleSystem::SimpleSystem() {
}

SimpleSystem::~SimpleSystem() {

}

ParticleState SimpleSystem::ComputeTimeDerivative(const ParticleState& state, float time) const {
    std::vector<glm::vec3> positions = state.positions;
    std::vector<glm::vec3> new_positions(state.positions.size());
    
    // for each position vector in the list of vectors,
    for (size_t i = 0; i < new_positions.size(); i++){
        // follow physical system implementation in the documentation
        glm::vec3 position = positions.at(i);
        float& x = position[0];
        float& y = position[1];
        
        glm::vec3 new_position = glm::vec3(-y, x, 0); 
        new_positions.at(i) = new_position;
    }
    
    ParticleState new_state{new_positions, state.velocities};
    return new_state;
}

}