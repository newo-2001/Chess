#include "pch.h"
#include "Window.h"

Window::Window(glm::ivec2 dimensions, std::string title) :
    m_title(title)
{
    InitializeGlfw();

    m_window = glfwCreateWindow(dimensions.x, dimensions.y, title.c_str(), NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }
    
    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);

    InitializeGlew();
    RegisterEventHandlers();
    
    glEnable(GL_DEPTH_TEST);
    SetViewport(dimensions);
    
    // Center window
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    glm::ivec2 monitorDimensions;
    glfwGetMonitorWorkarea(monitor, NULL, NULL, &monitorDimensions.x, &monitorDimensions.y);

    SetPosition((monitorDimensions - dimensions) / 2);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update()
{
    glfwPollEvents();

    glfwSwapBuffers(m_window);
    Clear();
}

void Window::Close()
{
    glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

bool Window::IsClosed() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::SetPosition(glm::ivec2 position)
{
    glfwSetWindowPos(m_window, position.x, position.y);
}

void Window::Resize(glm::ivec2 dimensions)
{
    glfwSetWindowSize(m_window, dimensions.x, dimensions.y);
}

glm::ivec2 Window::GetDimensions() const
{
    glm::ivec2 dimensions;
    glfwGetFramebufferSize(m_window, &dimensions.x, &dimensions.y);

    return dimensions;
}

glm::ivec2 Window::GetViewportDimensions() const
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, &viewport[0]);

    return glm::ivec2 { viewport[2], viewport[3] };
}

void Window::SetTitle(const std::string& title)
{
    glfwSetWindowTitle(m_window, title.c_str());
    m_title = title;
}

void Window::GrabCursor()
{
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    m_cursorGrabbed = true;
}

void Window::ReleaseCursor()
{
    glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glm::ivec2 center = GetDimensions() / 2;
    glfwSetCursorPos(m_window, center.x, center.y);

    m_cursorGrabbed = false;
}

void Window::SetBackgroundColor(glm::vec3 color, float alpha)
{
    glClearColor(color.r, color.g, color.b, alpha);
}

void Window::SetViewport(glm::ivec2 dimensions, glm::ivec2 bottomLeft)
{
    glViewport(bottomLeft.x, bottomLeft.y, dimensions.x, dimensions.y);
}

void Window::InitializeGlfw()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    
}

void Window::InitializeGlew()
{
    glewExperimental = GL_TRUE;

    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        const char* error = (const char*) glewGetErrorString(glewStatus);

        glfwDestroyWindow(m_window);
        glfwTerminate();

        throw std::runtime_error(std::format("Failed to initialize glew: {}", error));
    }
}

void OnResize(GLFWwindow* glfwWindow, int width, int height)
{
    Window* window = (Window*) glfwGetWindowUserPointer(glfwWindow);

    window->SetViewport(glm::ivec2 { width, height });
}

void OnKeyEvent(GLFWwindow* glfwWindow, int key, int code, int action, int mode)
{
    Window* window = (Window*) glfwGetWindowUserPointer(glfwWindow);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        window->Close();
    }

    window->GetInputHandler().OnKeyEvent.Post({ key, action });
}

void OnMouseButtonEvent(GLFWwindow* glfwWindow, int button, int action, int mods)
{
    Window* window = (Window*) glfwGetWindowUserPointer(glfwWindow);

    window->GetInputHandler().OnMouseButtonEvent.Post({ button, action });
}

void OnMouseMoveEvent(GLFWwindow* glfwWindow, double x, double y)
{
    Window* window = (Window*) glfwGetWindowUserPointer(glfwWindow);

    glm::vec2 current = { (float) x, (float) y };
    static glm::vec2 last = current;
    
    glm::vec2 delta = current - last;
    last = current;
    window->GetInputHandler().OnMouseMoveEvent.Post({ current, delta });
}

void OnScrollEvent(GLFWwindow* glfwWindow, double x, double y)
{
    Window* window = (Window*) glfwGetWindowUserPointer(glfwWindow);
    
    window->GetInputHandler().OnMouseScrollEvent.Post(glm::vec2((float) x, (float) y));
}

void Window::RegisterEventHandlers()
{
    glfwSetWindowSizeCallback(m_window, OnResize);
    glfwSetKeyCallback(m_window, OnKeyEvent);
    glfwSetMouseButtonCallback(m_window, OnMouseButtonEvent);
    glfwSetCursorPosCallback(m_window, OnMouseMoveEvent);
    glfwSetScrollCallback(m_window, OnScrollEvent);
}
