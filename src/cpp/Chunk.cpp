//
// Created by mateuszp on 2/2/23.
//

#include "../../include/Chunk.h"

Chunk::Chunk() {

}

void Chunk::init() {
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    block_data = chunk_vec(16);
    for(auto& i: block_data) {
        i = std::vector<std::vector<int>>(16);
        for(auto& j: i) {
            j = std::vector<int>(16);
        }
    }
    selected_data = chunk_vec(16);
    for(auto& i: selected_data) {
        i = std::vector<std::vector<int>>(16);
        for(auto& j: i) {
            j = std::vector<int>(16);
        }
    }

    for(int y = 0; y < 16; ++y) {
        for(int x = 0; x < 16; ++x) {
            for(int z = 0; z < 16; ++z) {
                if(y < 4) block_data[x][y][z] = 1;
                else if(y < 6) block_data[x][y][z] = 2;
                else if(y < 7) block_data[x][y][z] = 3;
                else block_data[x][y][z] = 0;
            }
        }
    }
}

void Chunk::generate(TextureManager& texture_manager) {
    vertices.clear();


    for(int x = 0; x < 16; ++x) {
        for(int y = 0; y < 16; ++y) {
            for(int z = 0; z < 16; ++z) {
                if(block_data[x][y][z] == 0) continue;
                int bd = block_data[x][y][z];
                float x1, x2, y1, y2;
                if(x == 15 || block_data[x+1][y][z] == 0) {
                    texture_manager.getResizedTextureCoords(x1, x2, y1, y2, bd, NORTH);
                    for(int i = 0; i < 6; ++i) {
                        vertices.push_back(cube_verts_north[i * 5] + (float) x);
                        vertices.push_back(cube_verts_north[i * 5 + 1] + (float) y);
                        vertices.push_back(cube_verts_north[i * 5 + 2] + (float) z);
                        vertices.push_back(cube_verts_north[5 * i + 3] == 1.0f ? x2 : x1);
                        vertices.push_back(cube_verts_north[5 * i + 4] == 1.0f ? y2 : y1);
                        vertices.push_back((float)selected_data[x][y][z]);
                        vertices.push_back(1.0f);
                    }
                }
                if(x == 0 || block_data[x-1][y][z] == 0) {
                    texture_manager.getResizedTextureCoords(x1, x2, y1, y2, bd, SOUTH);
                    for(int i = 0; i < 6; ++i) {
                        vertices.push_back(cube_verts_south[i * 5] + (float) x);
                        vertices.push_back(cube_verts_south[i * 5 + 1] + (float) y);
                        vertices.push_back(cube_verts_south[i * 5 + 2] + (float) z);
                        vertices.push_back(cube_verts_south[5 * i + 3] == 1.0f ? x2 : x1);
                        vertices.push_back(cube_verts_south[5 * i + 4] == 1.0f ? y2 : y1);
                        vertices.push_back((float)selected_data[x][y][z]);
                        vertices.push_back(1.0f);
                    }
                }
                if(y == 15 || block_data[x][y+1][z] == 0) {
                    texture_manager.getResizedTextureCoords(x1, x2, y1, y2, bd, TOP);
                    for(int i = 0; i < 6; ++i) {
                        vertices.push_back(cube_verts_top[i * 5] + (float) x);
                        vertices.push_back(cube_verts_top[i * 5 + 1] + (float) y);
                        vertices.push_back(cube_verts_top[i * 5 + 2] + (float) z);
                        vertices.push_back(cube_verts_top[5 * i + 3] == 1.0f ? x2 : x1);
                        vertices.push_back(cube_verts_top[5 * i + 4] == 1.0f ? y2 : y1);
                        vertices.push_back((float)selected_data[x][y][z]);
                        vertices.push_back(1.0f);
                    }
                }
                if(y == 0 || block_data[x][y-1][z] == 0) {
                    texture_manager.getResizedTextureCoords(x1, x2, y1, y2, bd, BOTTOM);
                    for(int i = 0; i < 6; ++i) {
                        vertices.push_back(cube_verts_bottom[i * 5] + (float) x);
                        vertices.push_back(cube_verts_bottom[i * 5 + 1] + (float) y);
                        vertices.push_back(cube_verts_bottom[i * 5 + 2] + (float) z);
                        vertices.push_back(cube_verts_bottom[5 * i + 3] == 1.0f ? x2 : x1);
                        vertices.push_back(cube_verts_bottom[5 * i + 4] == 1.0f ? y2 : y1);
                        vertices.push_back((float)selected_data[x][y][z]);
                        vertices.push_back(1.0f);
                    }
                }
                if(z == 15 || block_data[x][y][z+1] == 0) {
                    texture_manager.getResizedTextureCoords(x1, x2, y1, y2, bd, EAST);
                    for(int i = 0; i < 6; ++i) {
                        vertices.push_back(cube_verts_east[i * 5] + (float) x);
                        vertices.push_back(cube_verts_east[i * 5 + 1] + (float) y);
                        vertices.push_back(cube_verts_east[i * 5 + 2] + (float) z);
                        vertices.push_back(cube_verts_east[5 * i + 3] == 1.0f ? x2 : x1);
                        vertices.push_back(cube_verts_east[5 * i + 4] == 1.0f ? y2 : y1);
                        vertices.push_back((float)selected_data[x][y][z]);
                        vertices.push_back(1.0f);
                    }
                }
                if(z == 0 || block_data[x][y][z-1] == 0) {
                    texture_manager.getResizedTextureCoords(x1, x2, y1, y2, bd, WEST);
                    for(int i = 0; i < 6; ++i) {
                        vertices.push_back(cube_verts_west[i * 5] + (float) x);
                        vertices.push_back(cube_verts_west[i * 5 + 1] + (float) y);
                        vertices.push_back(cube_verts_west[i * 5 + 2] + (float) z);
                        vertices.push_back(cube_verts_west[5 * i + 3] == 1.0f ? x2 : x1);
                        vertices.push_back(cube_verts_west[5 * i + 4] == 1.0f ? y2 : y1);
                        vertices.push_back((float)selected_data[x][y][z]);
                        vertices.push_back(1.0f);
                    }
                }
            }
        }
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(5*sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);

    selected_data = chunk_vec(16);
    for(auto& i: selected_data) {
        i = std::vector<std::vector<int>>(16);
        for(auto& j: i) {
            j = std::vector<int>(16);
        }
    }
}

void Chunk::render(Shader& shader) {
    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() * sizeof(float));
}

void Chunk::selectBlock(glm::ivec3 &pos) {
    selected_data[pos.x][pos.y][pos.z] = 1.0;
}


