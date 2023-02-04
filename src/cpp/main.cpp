#define STB_IMAGE_IMPLEMENTATION
#include "../../include/Game.h"

Game game;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double x_pos, double y_pos);

int main() {
    game = Game();
    game.init();
    glfwSetFramebufferSizeCallback(game.getWindow(), framebufferSizeCallback);
    glfwSetInputMode(game.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(game.getWindow(), mouseCallback);
    game.mainLoop();
    game.cleanup();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    game.framebufferCallback(window, width, height);
}

void mouseCallback(GLFWwindow* window, double x_pos, double y_pos) {
    game.mouseCallback(window, x_pos, y_pos);
}
