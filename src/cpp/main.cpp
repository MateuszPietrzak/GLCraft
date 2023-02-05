#define STB_IMAGE_IMPLEMENTATION
#include "../../include/Game.h"

Game game;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double x_pos, double y_pos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

int main() {
    game = Game();
    game.init();
    glfwSetFramebufferSizeCallback(game.getWindow(), framebufferSizeCallback);
    glfwSetCursorPosCallback(game.getWindow(), mouseCallback);
    glfwSetMouseButtonCallback(game.getWindow(), mouseButtonCallback);
    game.mainLoop();
    game.cleanup();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    game.framebufferCallback(window, width, height);
}

void mouseCallback(GLFWwindow* window, double x_pos, double y_pos) {
    game.mouseCallback(window, x_pos, y_pos);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    game.mouseButtonCallback(window, button, action, mods);
}
