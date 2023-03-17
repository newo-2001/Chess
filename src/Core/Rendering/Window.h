#pragma once

#include "pch.h"

#include <Core/Input/InputHandler.h>

class Window
{
public:
    Window(glm::ivec2 dimensions, std::string title);
    ~Window();
    
    glm::ivec2 GetDimensions() const;
    void Resize(glm::ivec2 dimensions);
    void SetPosition(glm::ivec2 position);

    void SetViewport(glm::ivec2 dimensions, glm::ivec2 bottomLeft = { 0, 0 });
    glm::ivec2 GetViewportDimensions() const;

    void SetTitle(const std::string& title);
    const std::string& GetTitle() const { return m_title; }

    void SetBackgroundColor(glm::vec3 color, float alpha = 1.0f);

    void GrabCursor();
    void ReleaseCursor();
    bool CursorIsGrabbed() const { return m_cursorGrabbed; }
    
    void Close();
    bool IsClosed() const;

    void Update();
    void Clear();
    
    InputHandler& GetInputHandler() { return m_inputHandler; }
private:
    InputHandler m_inputHandler;

    std::string m_title;
    GLFWwindow* m_window;
    bool m_cursorGrabbed;

    void InitializeGlew();
    void InitializeGlfw();
    void RegisterEventHandlers();
};

