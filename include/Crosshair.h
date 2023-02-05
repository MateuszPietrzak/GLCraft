//
// Created by mateuszp on 2/4/23.
//

#ifndef GLCRAFT_CROSSHAIR_H
#define GLCRAFT_CROSSHAIR_H


#include "Shader.h"
#include "TextureManager.h"

class Crosshair {
public:
    Crosshair();
    void init(int scr_width, int scr_height);
    void render();

    void updateWindowSize(int new_width, int new_height);
private:
    Shader shader;
    unsigned int textureID;
    unsigned int VBO;
    unsigned int VAO;
    glm::mat4 projection;
};


#endif //GLCRAFT_CROSSHAIR_H
