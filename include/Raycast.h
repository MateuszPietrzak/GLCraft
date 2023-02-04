//
// Created by mateuszp on 2/4/23.
//

#ifndef GLCRAFT_RAYCAST_H
#define GLCRAFT_RAYCAST_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

class Raycast {
public:
    static bool raycast(glm::vec3& position, glm::vec3& direction, glm::ivec3& result, std::vector<std::vector<std::vector<int>>>& chunk_block_data);
};


#endif //GLCRAFT_RAYCAST_H
