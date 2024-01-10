#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Resources/ResourceManager.hpp"
#include "Render/ShaderProgram.hpp"
#include "Render/Texture2D.hpp"
#include "Render/Sprite.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Render/AnimatedSprite.hpp"
#include "Game/Game.hpp"

std::unique_ptr<Game> game = std::make_unique<Game>();

glm::vec2 window_size(640*2, 480*2);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    window_size.x = width;
    window_size.y = height;
    glViewport(0, 0, window_size.x, window_size.y);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
    game->set_key(key, action);
}



int main(const int argc, const char** argv)
{
#pragma region INIT_OPNEGL_AND_GLFW
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* pWindow = glfwCreateWindow(window_size.x, window_size.y, "Adventure Time", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD!" << std::endl;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
#pragma endregion


    glClearColor(1, 1, 0, 1);
    

    ResourceManager::init(argv[0]);
    game->init(window_size);

    glfwSwapInterval(1);


    unsigned int delta;
    float t1 = glfwGetTime();
    while (!glfwWindowShouldClose(pWindow))
    {   
        glClear(GL_COLOR_BUFFER_BIT);

        float t2 = glfwGetTime();
        delta = static_cast<unsigned int>((t2 - t1) * 1000);
        t1 = glfwGetTime();




        game->update(delta);
        game->render();




        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}