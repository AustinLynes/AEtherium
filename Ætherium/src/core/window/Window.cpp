#include "Window.h"
namespace Ætherium {

    Window::Window(int width, int height) :width{ width }, height{ height }
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, "AEtherium Engine", NULL, NULL);

        if (window == NULL) {
            LOG_ERROR(L"ERROR:: window is null");
            return;
        }

        glfwMakeContextCurrent(window);
        glfwMaximizeWindow(window);
        //glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            LOG_ERROR(L"COULD NOT INITLIZE GLAD");
            return;
        };
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    void Window::Draw()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(window);
    }

    int Window::GetWidth()
    {
        return width;
    }

    int Window::GetHeight()
    {
        return height;
    }

    void Window::Resize(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    GLFWwindow* Window::GetRawWindow()
    {
        return window;
    }
}