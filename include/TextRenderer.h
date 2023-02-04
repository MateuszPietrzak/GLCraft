//
// Created by mateuszp on 2/2/23.
//

#ifndef GLCRAFT_TEXTRENDERER_H
#define GLCRAFT_TEXTRENDERER_H

#include <iostream>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"

struct Character {
    unsigned int textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

class TextRenderer {
public:
    TextRenderer();

    void init(int scr_width, int scr_height);
    void render(std::string text, float x, float y, float scale, glm::vec3(color));
    void updateWindowSize(int new_width, int new_height);

private:
    glm::mat4 projection;
    std::map<char, Character> characters;
    Shader shader;
    unsigned int VAO, VBO;
};


#endif //GLCRAFT_TEXTRENDERER_H
