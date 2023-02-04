//
// Created by mateuszp on 2/3/23.
//

#ifndef GLCRAFT_TEXTUREMANAGER_H
#define GLCRAFT_TEXTUREMANAGER_H

#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

struct TextureBlockCoords {
    TextureBlockCoords(int _x, int _y) : x(_x), y(_y) {}
    int x;
    int y;
};

enum Side {
    TOP,
    BOTTOM,
    NORTH,
    SOUTH,
    WEST,
    EAST
};

class TextureManager {
public:
    TextureManager();

    void init();
    unsigned int getTexture();

    static unsigned int createTexture(const char* filepath);
    void getResizedTextureCoords(float& x1, float& x2, float& y1, float& y2, int block_id, Side side);
private:
    int wx;
    int wy;
    unsigned int textureID;
    std::vector<TextureBlockCoords> texture_block_coords;
};


#endif //GLCRAFT_TEXTUREMANAGER_H
