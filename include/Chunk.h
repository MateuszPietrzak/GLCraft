//
// Created by mateuszp on 2/2/23.
//

#ifndef GLCRAFT_CHUNK_H
#define GLCRAFT_CHUNK_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "TextureManager.h"
#include <vector>

typedef std::vector<std::vector<std::vector<int>>> chunk_vec;

class Chunk {
public:
    Chunk();

    void init();
    void generate(TextureManager& texture_manager);
    void render(Shader& shader);
    void selectBlock(glm::ivec3& pos);
    chunk_vec& getBlockData() {return block_data;}
private:
    unsigned int VBO;
    unsigned int VAO;

    std::vector<float> vertices;
    chunk_vec block_data;
    chunk_vec selected_data;

    static constexpr float cube_verts_west[] = {
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f
    };

    static constexpr float cube_verts_east[] = {
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
    };

    static constexpr float cube_verts_south[] = {
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    };

    static constexpr float cube_verts_north[] = {
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    };

    static constexpr float cube_verts_bottom[] = {
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    };

    static constexpr float cube_verts_top[] = {
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
};


#endif //GLCRAFT_CHUNK_H
