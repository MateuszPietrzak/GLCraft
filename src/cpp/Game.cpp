//
// Created by mateuszp on 2/1/23.
//

#include "../../include/Game.h"

Game::Game() {
}

void Game::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if(window == NULL) {
        std::cout << "Failed to create a window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);


    elapsed_time = 0.0f;
    delta_time = 0.0f;

    shader = Shader("src/glsl/shader.vert", "src/glsl/shader.frag");

    camera = Camera(width, height);

    text_renderer = TextRenderer();
    text_renderer.init(width, height);

    texture_manager = TextureManager();
    texture_manager.init();

    chunk = Chunk();
    chunk.init();
    chunk.generate(texture_manager);
}

void Game::mainLoop() {
    while(!glfwWindowShouldClose(window)) {
        processInput();

        glClearColor(0.20f, 0.19f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 projection = glm::perspective(3.14f / 4.0f, (float)width/(float)height, 0.01f, 100.0f);
        glm::mat4 view = camera.getMatrix();

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setInt("tex", 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_manager.getTexture());

        chunk.render(shader);

        text_renderer.render("FPS: " + std::to_string(1.0f/delta_time), 10, 780, 0.3, glm::vec3(1.0f, 1.0f, 1.0f));
        text_renderer.render("Cam pos: " + std::to_string(camera.getPos().x) + ", " + std::to_string(camera.getPos().y) + ", " + std::to_string(camera.getPos().z), 10, 760, 0.3, glm::vec3(1.0f, 1.0f, 1.0f));
        text_renderer.render("Cam yaw / pitch: " + std::to_string(camera.getYawPitch().x) + ", " + std::to_string(camera.getYawPitch().y), 10, 740, 0.3, glm::vec3(1.0f, 1.0f, 1.0f));

        glm::ivec3 res;
        if(Raycast::raycast(camera.getPos(), camera.getDirection(), res, chunk.getBlockData())) {
            chunk.selectBlock(res);
        }
        std::cout << res.x << " " << res.y << " " << res.z << "\n";

        chunk.generate(texture_manager);

        glfwSwapBuffers(window);
        glfwPollEvents();

        delta_time = glfwGetTime() - elapsed_time;
        elapsed_time = glfwGetTime();
    }
}

void Game::cleanup() {
    glfwTerminate();
}

void Game::framebufferCallback(GLFWwindow *_window, int _width, int _height) {
    width = _width;
    height = _height;
    glViewport(0, 0, width, height);
    text_renderer.updateWindowSize(width, height);
}


void Game::processInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    camera.processKeyboard(window, delta_time);
}

void Game::mouseCallback(GLFWwindow* _window, double x_pos, double y_pos) {
    camera.processMouse(x_pos, y_pos, delta_time);
}
