//
// Created by mateuszp on 2/1/23.
//

#ifndef GLCRAFT_GAME_H
#define GLCRAFT_GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include "Shader.h"
#include "Camera.h"
#include "Chunk.h"
#include "TextRenderer.h"
#include "TextureManager.h"
#include "Raycast.h"
#include "Crosshair.h"

enum State {
    GLC_MENU,
    GLC_GAME
};

class Game {
public:
    Game();

    void init();
    void mainLoop();
    void cleanup();

    GLFWwindow* getWindow() { return window; }

    void framebufferCallback(GLFWwindow* _window, int _width, int _height);
    void mouseCallback(GLFWwindow* _window, double x_pos, double y_pos);
    void mouseButtonCallback(GLFWwindow* _window, int button, int action, int mods);

private:

    void processInput();

    Chunk chunk;
    glm::ivec3 block_to_break;
    glm::ivec3 block_to_place;

    GLFWwindow* window;
    Camera camera;
    Shader shader;
    TextRenderer text_renderer;
    TextureManager texture_manager;
    Crosshair crosshair;
    unsigned int VAO, VBO;
    int width = 1200;
    int height = 800;
    float elapsed_time;
    float delta_time;
};


#endif //GLCRAFT_GAME_H
