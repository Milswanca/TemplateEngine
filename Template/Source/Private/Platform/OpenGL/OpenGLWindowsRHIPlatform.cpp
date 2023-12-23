#include "Platform/OpenGL/OpenGLWindowsRHIPlatform.h"
#include "Platform/Windows/WindowsWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

OpenGLWindowsDeviceContext::OpenGLWindowsDeviceContext(HWND InWindowHandle, HDC InDeviceContext) : OpenGLDeviceContext()
                                                                                                   , m_WindowHandle(InWindowHandle), m_DeviceContext(InDeviceContext)
{
    m_OpenGLContext = wglCreateContext(InDeviceContext);
    DWORD Error = GetLastError();
}

OpenGLWindowsDeviceContext::~OpenGLWindowsDeviceContext()
{
    wglDeleteContext(m_OpenGLContext);
}

void OpenGLWindowsDeviceContext::MakeCurrent()
{
    wglMakeCurrent(m_DeviceContext, m_OpenGLContext);
}

OpenGLWindowsRHIPlatform::OpenGLWindowsRHIPlatform() : OpenGLRHIPlatform()
{
    if(!glfwInit())
    {
        throw "Failed to init glfw";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* Window = glfwCreateWindow(1, 1, "TEMP WINDOW", nullptr, nullptr);
    glfwMakeContextCurrent(Window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw "Failed to init glad";
    }

    glfwDestroyWindow(Window);
}

OpenGLWindowsRHIPlatform::~OpenGLWindowsRHIPlatform()
{
    glfwTerminate();
}

OpenGLDeviceContext* OpenGLWindowsRHIPlatform::RHIPlatformCreateOpenGLContext(Window* InWindow)
{
    WindowsWindow* Window = static_cast<WindowsWindow*>(InWindow);
    OpenGLWindowsDeviceContext* Context = new OpenGLWindowsDeviceContext(Window->GetHandle(), Window->GetDeviceContext());
    
    return Context;
}

void OpenGLWindowsRHIPlatform::RHIPlatformBindOpenGLContext(OpenGLDeviceContext* InContext)
{
    OpenGLWindowsDeviceContext* Context = static_cast<OpenGLWindowsDeviceContext*>(InContext);
    Context->MakeCurrent();
}

void OpenGLWindowsRHIPlatform::RHIPlatformDeleteOpenGLContext(OpenGLDeviceContext* InContext)
{
    OpenGLWindowsDeviceContext* Context = static_cast<OpenGLWindowsDeviceContext*>(InContext);
    delete Context;
}
