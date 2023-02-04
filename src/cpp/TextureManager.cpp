//
// Created by mateuszp on 2/3/23.
//

#include "../../include/TextureManager.h"

TextureManager::TextureManager() {

}

void TextureManager::init() {
    textureID = TextureManager::createTexture("assets/textures/texture.png");
}

unsigned int TextureManager::createTexture(const char* filepath) {
    int width, height, nrChannels;
//    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);

    unsigned int result;
    glGenTextures(1, &result);
    glBindTexture(GL_TEXTURE_2D, result);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return result;
}

unsigned int TextureManager::getTexture() {
    return textureID;
}

void TextureManager::getResizedTextureCoords(float &x1, float &x2, float &y1, float &y2, int block_id, Side side) {
    if(block_id == 1) {
        x1 = 0.5f;
        x2 = 1.0f;
        y1 = 0.5f;
        y2 = 1.0f;
        return;
    }
    if(block_id == 2) {
        x1 = 0.0f;
        x2 = 0.5f;
        y1 = 0.5f;
        y2 = 1.0f;
        return;
    }
    if(block_id == 3 && side == TOP) {
        x1 = 0.5f;
        x2 = 1.0f;
        y1 = 0.0f;
        y2 = 0.5f;
        return;
    }
    if(block_id == 3 && side == BOTTOM) {
        x1 = 0.0f;
        x2 = 0.5f;
        y1 = 0.5f;
        y2 = 1.0f;
        return;
    }
    if(block_id == 3) {
        x1 = 0.0f;
        x2 = 0.5f;
        y1 = 0.0f;
        y2 = 0.5f;
        return;
    }
}


