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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    crosshair = Crosshair();
    crosshair.init(width, height);

    chunk = Chunk();
    chunk.init();
    chunk.generate(texture_manager);
}

void Game::mainLoop() {
    while(!glfwWindowShouldClose(window)) {
        processInput();

        glClearColor(0.38f, 0.62f, 0.89f, 1.0f);
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

        crosshair.render();

        Side cast_side;
        if(Raycast::raycast(camera.getPos(), camera.getDirection(), block_to_break, cast_side, chunk.getBlockData())) {
            chunk.selectBlock(block_to_break);
        }
        block_to_place = block_to_break;
        switch(cast_side) {
            case TOP:
                block_to_place.y++;
                break;
            case BOTTOM:
                block_to_place.y--;
                break;
            case NORTH:
                block_to_place.x++;
                break;
            case SOUTH:
                block_to_place.x--;
                break;
            case EAST:
                block_to_place.z++;
                break;
            case WEST:
                block_to_place.z--;
                break;
        }


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

void Game::mouseButtonCallback(GLFWwindow *_window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        chunk.getBlockData()[block_to_break.x][block_to_break.y][block_to_break.z] = 0;
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        chunk.getBlockData()[block_to_place.x][block_to_place.y][block_to_place.z] = 1;
}
