//
// Created by mateuszp on 2/4/23.
//

#include "../../include/Crosshair.h"

Crosshair::Crosshair() {

}

void Crosshair::init(int scr_width, int scr_height) {
    textureID = TextureManager::createTexture("assets/textures/crosshair.png");
    shader = Shader("src/glsl/crosshair.vert", "src/glsl/crosshair.frag");

    shader.use();

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    float vertices[] = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            1.0f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    projection = glm::ortho(0.0f, (float)scr_width, 0.0f, (float)scr_height);
    shader.setMat4("projection", projection);
    shader.setInt("width", scr_width);
    shader.setInt("height", scr_height);
}

void Crosshair::render() {
    shader.use();
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);
}

void Crosshair::updateWindowSize(int new_width, int new_height) {

}
