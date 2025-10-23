#include "nodes/ClothNode.hpp"

#include "objects/ParticleObject.hpp"
#include "nodes/ScenePhysicsNode.hpp"

#include "gloo/debug/PrimitiveFactory.hpp"
#include "gloo/shaders/PhongShader.hpp"
#include "gloo/shaders/SimpleShader.hpp"
#include "gloo/components/ShadingComponent.hpp"
#include "gloo/components/RenderingComponent.hpp"
#include "gloo/VertexObject.hpp"

#include <glm/gtx/string_cast.hpp>

namespace GLOO {

const float ClothNode::b = 0.1f;
 
ClothNode::ClothNode(glm::vec3 pos, size_t side_length) : side_length_(side_length) {
    // Initialize position and number of particles using parameters
    this->GetTransform().SetPosition(pos);
    num_particles_ = side_length * side_length;

    // Create geometry
    sphere_mesh_ = PrimitiveFactory::CreateSphere(0.08f, 25, 25);
    shader_ = std::make_shared<PhongShader>();
    line_shader_ = std::make_shared<SimpleShader>();

    float default_mass = 0.1f;
    float default_k = 10.0f;
    float default_r = 0.5f;
    glm::vec3 default_pos = this->GetTransform().GetPosition() + glm::vec3(-0.5f, 0.0f, 0.0f);
    glm::vec3 default_vel = {0.0f, 0.0f, -3.0f};

    InitializeSystem(default_mass, default_k, default_r);
    InitializeState(default_mass, default_k, default_r, default_pos, default_vel);
    InitializeGeometry();

}

void ClothNode::InitializeSystem(float mass, float k, float r) {
    // Initialize the system for the cloth node
    system_ = make_unique<ClothSystem>();

    // Initialize particles in cloth system with default properties, reachable by index
    for (size_t i = 0; i < num_particles_; i++){
        ParticleObject new_particle{mass, false};
        // If at a particle in the first row, set fixed to true. Row major indexing will be used later
        if (i < side_length_) {
            ///new_particle.fixed = true;
        }
        
        this->GetSystem()->GetParticles().push_back(new_particle);
    }

    // Initialize springs in cloth system with default properties
    float shear_r = r * sqrt(2.0f);
    float flexion_r = r * 2.0f;

    // Start with initializing structural springs
    for (size_t y = 0; y < side_length_; y++){
        for (size_t x = 0; x < side_length_; x++){
            // Get current idx by computing y*side_length_+x
            size_t idx = y*side_length_+x;
            // std::cout << "x: " << x << " y: " << y << std::endl;

            // Create a horizontal spring if there's a particle to the left of the current one
            if (x < side_length_-1) {
                // Structural spring between current idx and y*side_length_+(x+1) (x direction)
                size_t idx_next_x = y*side_length_+(x+1);
                SpringObject new_structural_spring_x{idx, idx_next_x, k, r};
                this->GetSystem()->GetSprings().push_back(new_structural_spring_x);
                // std::cout << "Structural spring created between " << idx << " and " << idx_next_x << std::endl;
            }

            // Create a vertical spring if there's a particle below the current one
            if (y < side_length_ - 1) {
                // Strucutral spring between current idx and (y+1)*side_length_+x (y direction)
                size_t idx_next_y = (y+1)*side_length_+x;
                SpringObject new_structural_spring_y{idx, idx_next_y, k, r};
                this->GetSystem()->GetSprings().push_back(new_structural_spring_y);
                // std::cout << "Structural spring created between " << idx << " and " << idx_next_y << std::endl;
            }
        }
    }
    // std::cout << std::endl;

    // Next, initialize shear springs
    for (int y = 0; y < int(side_length_); y++) {
        for (int x = 0; x < int(side_length_); x++) {
            // Get current idx by computing y*side_length_+x
            size_t idx = y*side_length_+x;
            std::cout << "x: " << x << " y: " << y << std::endl;

            // Create a shear spring between current and bottom left particle if it exists
            if ((x-1) >= 0 && (y+1) < int(side_length_)) {
                size_t idx_left = (y+1)*side_length_+(x-1);
                SpringObject new_shear_spring{idx, idx_left, k, shear_r};
                this->GetSystem()->GetSprings().push_back(new_shear_spring);
                std::cout << "Shear spring created between " << idx << " and " << idx_left << std::endl;
            }

            // Create a shear spring between current and bottom right particle if it exists
            if ((x+1) < int(side_length_) && (y+1) < int(side_length_)) {
                size_t idx_right = (y+1)*side_length_+(x+1);
                SpringObject new_shear_spring{idx, idx_right, k, shear_r};
                this->GetSystem()->GetSprings().push_back(new_shear_spring);
                std::cout << "Shear spring created between " << idx << " and " << idx_right << std::endl;
            }
        }
    }
    std::cout << std::endl;

    // Finally, compute flexion springs
    for (size_t y = 0; y < side_length_; y++) {
        for (size_t x = 0; x < side_length_; x++) {
            // Get current idx by computing y*side_length_+x
            size_t idx = y*side_length_+x;
            std::cout << "x: " << x << " y: " << y << std::endl;

            // Create a flexion spring between current and right particle if it exists
            if (x < side_length_-2){
                size_t idx_right = y*side_length_+(x+2);
                SpringObject new_flexion_spring{idx, idx_right, k, flexion_r};
                this->GetSystem()->GetSprings().push_back(new_flexion_spring);
                std::cout << "Flexion spring created between " << idx << " and " << idx_right << std::endl;
            }

            // Create a flexion spring between current and right particle if it exists
            if (y < side_length_-2){
                size_t idx_down = (y+2)*side_length_+x;
                SpringObject new_flexion_spring{idx, idx_down, k, flexion_r};
                this->GetSystem()->GetSprings().push_back(new_flexion_spring);
                std::cout << "Flexion spring created between " << idx << " and " << idx_down << std::endl;
            }

            
        }
    }

}

void ClothNode::InitializeState(float mass, float k, float r, glm::vec3 pos, glm::vec3 vel) {
    // Initialize the state for the cloth node
    float g = glm::abs(ScenePhysicsNode::g.y);
    float default_x = pos.x;

    // vector of size num_particles for the particles in the system
    std::vector<glm::vec3> state_positions(num_particles_);
    std::vector<glm::vec3> state_velocities(num_particles_);

    // Treat the positions and velocities as a 2D array, indexed by y*side_length_ + x
    for (size_t y = 0; y < side_length_; y++) {
        
        for (size_t x = 0; x < side_length_; x++) {
            size_t state_idx = y * side_length_ + x;

            state_positions.at(state_idx) = pos;
            state_velocities.at(state_idx) = vel;
            pos.x += r;
        }
        
        pos.x = default_x;

        float vertical_stretch = (mass * float(side_length_ * side_length_) * g) / (side_length_ * (side_length_-1) * k);
        // New vertical equilibrium length is x = r + mg/k. Use this to set the initial points at an equilibrium length
        pos.y -= (r + vertical_stretch);

        vel.z -= 0.5f;
    }

    ParticleState cloth_state{state_positions, state_velocities};
    state_ = cloth_state;
}

void ClothNode::InitializeGeometry() {
    // Initialize geometry that we see in the scene for cloth

    // For each particle
    for (size_t i = 0; i < this->GetSystem()->GetParticles().size(); i++){
        auto sphere_node = make_unique<SceneNode>();
        sphere_node->CreateComponent<ShadingComponent>(shader_);
        sphere_node->CreateComponent<RenderingComponent>(sphere_mesh_);
        sphere_node->GetTransform().SetPosition(state_.positions.at(i));

        sphere_nodes_.push_back(sphere_node.get());
        this->AddChild(std::move(sphere_node));
    }
    
    // Create a spring line node that'll hold the drawn line
    auto spring_line_node = make_unique<SceneNode>();
    spring_line_node_ = spring_line_node.get();
    spring_line_node->CreateComponent<ShadingComponent>(line_shader_);
    
    PlotWireframe();

    this->AddChild(std::move(spring_line_node));

}

void ClothNode::PlotWireframe() {

    // Update the vertex object using each spring to render lines
    auto spring_line_positions = make_unique<PositionArray>();
    auto spring_line_indices = make_unique<IndexArray>();

    size_t indexarr_idx = 0;
    for (size_t i = 0; i < this->GetSystem()->GetSprings().size(); i++){
        // Get the spring
        SpringObject spring = this->GetSystem()->GetSprings().at(i);
        // Get the index and position of particle1
        size_t p1_idx = spring.p1_idx;
        glm::vec3 p1_pos = state_.positions.at(p1_idx);
        // Get the index and position of particle2
        size_t p2_idx = spring.p2_idx;
        glm::vec3 p2_pos = state_.positions.at(p2_idx);

        // Set the position array
        spring_line_positions->push_back(p1_pos);
        spring_line_positions->push_back(p2_pos);
        // Set the index array
        spring_line_indices->push_back(indexarr_idx);
        spring_line_indices->push_back(indexarr_idx+1);
        indexarr_idx += 2;
    }

    // If mesh (lines drawn) hasnt been initialized yet, initialize
    if (spring_line_node_->GetComponentPtr<RenderingComponent>() == nullptr) {
        // Create a spring line vertex object that'll update positions of drawn line
        auto spring_line_vobj = std::make_shared<VertexObject>();
        // Update its vertices and positions
        spring_line_vobj->UpdatePositions(std::move(spring_line_positions));
        spring_line_vobj->UpdateIndices(std::move(spring_line_indices));
        // Create a rendering component so lines can be drawn to screen
        auto& rcomp = spring_line_node_->CreateComponent<RenderingComponent>(spring_line_vobj);
        rcomp.SetDrawMode(DrawMode::Lines);
    }
    else{
        // Get the spring line vertex object that'll update positions of drawn line
        VertexObject* spring_line_vobj = spring_line_node_->GetComponentPtr<RenderingComponent>()->GetVertexObjectPtr();
        // Update its vertices and positions
        spring_line_vobj->UpdatePositions(std::move(spring_line_positions));
        spring_line_vobj->UpdateIndices(std::move(spring_line_indices));
    }
}

void ClothNode::Update(double delta_time) {
    // Update function of ScenePhysicsNode for integrator has been run
    // Do specific ClothNode update behavior
    for (size_t i = 0; i < sphere_nodes_.size(); i++){
        glm::vec3 position = state_.positions.at(i);
        SceneNode* sphere_node = sphere_nodes_.at(i);

        sphere_node->GetTransform().SetPosition(position);
    }

    PlotWireframe();

}

} // namespace GLOO