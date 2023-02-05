//
// Created by mateuszp on 2/4/23.
//

#include "../../include/Raycast.h"

bool Raycast::raycast(glm::vec3 &position, glm::vec3 &direction, glm::ivec3 &result, Side& cast_side, std::vector<std::vector<std::vector<int>>>& chunk_block_data) {
    float x = position.x + 0.5;
    float y = position.y + 0.5;
    float z = position.z + 0.5;

    int step_x = (direction.x > 0 ? 1 : -1);
    int step_y = (direction.y > 0 ? 1 : -1);
    int step_z = (direction.z > 0 ? 1 : -1);


    if(direction.x == 0.0f || direction.y == 0.0f || direction.z == 0.0f) return false;

    double temp;
    glm::vec3 dir = glm::normalize(direction);

    float t_max_x = glm::length((direction / direction.x) * (float)(step_x == 1 ? 1 - modf(position.x + 0.5, &temp) : modf(position.x + 0.5, &temp)));
    float t_max_y = glm::length((direction / direction.y) * (float)(step_y == 1 ? 1 - modf(position.y + 0.5, &temp) : modf(position.y + 0.5, &temp)));
    float t_max_z = glm::length((direction / direction.z) * (float)(step_z == 1 ? 1 - modf(position.z + 0.5, &temp) : modf(position.z + 0.5, &temp)));

    float t_delta_x = glm::length(direction / direction.x);
    float t_delta_y = glm::length(direction / direction.y);
    float t_delta_z = glm::length(direction / direction.z);

    int last_move = 0;

    do {
        if(t_max_x < t_max_y) {
            if(t_max_x < t_max_z) {
                x = x + step_x;
                last_move = 1;
                if(x < 0 || x > 15)
                    return false;
                t_max_x = t_max_x + t_delta_x;
            } else {
                z = z + step_z;
                last_move = 3;
                if(z < 0 || z > 15)
                    return false;
                t_max_z = t_max_z + t_delta_z;
            }
        } else {
            if(t_max_y < t_max_z) {
                y = y + step_y;
                last_move = 2;
                if(y < 0 || y > 15)
                    return false;
                t_max_y = t_max_y + t_delta_y;
            } else {
                z = z + step_z;
                last_move = 3;
                if(z < 0 || z > 15)
                    return false;
                t_max_z = t_max_z + t_delta_z;
            }
        }
    } while(chunk_block_data[(int)x][(int)y][(int)z] == 0);

    if(last_move == 1 && step_x == 1) cast_side = SOUTH;
    if(last_move == 1 && step_x == -1) cast_side = NORTH;
    if(last_move == 2 && step_y == 1) cast_side = BOTTOM;
    if(last_move == 2 && step_y == -1) cast_side = TOP;
    if(last_move == 3 && step_z == 1) cast_side = WEST;
    if(last_move == 3 && step_z == -1) cast_side = EAST;

    result = glm::ivec3((int)x, (int)y, (int)z);
    return true;
}
