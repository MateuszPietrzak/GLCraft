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

private:

    void processInput();

    Chunk chunk;

    GLFWwindow* window;
    Camera camera;
    Shader shader;
    TextRenderer text_renderer;
    TextureManager texture_manager;
    unsigned int VAO, VBO;
    int width = 1200;
    int height = 800;
    float elapsed_time;
    float delta_time;
};


#endif //GLCRAFT_GAME_H
