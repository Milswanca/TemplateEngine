#include "Platform/OpenGL/OpenGLWindowsRHIPlatform.h"
#include "Platform/Windows/WindowsWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC hdc, HGLRC hShareContext, const int *attribList);
wglCreateContextAttribsARB_type* wglCreateContextAttribsARB = nullptr;

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

OpenGLWindowsDeviceContext::OpenGLWindowsDeviceContext(HWND InWindowHandle, HDC InDeviceContext) : OpenGLDeviceContext()
    , m_WindowHandle(InWindowHandle), m_DeviceContext(InDeviceContext)
{
    int GLAttributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
    };
    m_OpenGLContext = wglCreateContextAttribsARB(m_DeviceContext, 0, GLAttributes);
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

void* OpenGLWindowsDeviceContext::GetDeviceContext()
{
    return m_DeviceContext;
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


    wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type*)wglGetProcAddress("wglCreateContextAttribsARB");
    int Err = glGetError();
    glfwDestroyWindow(Window);
}

OpenGLWindowsRHIPlatform::~OpenGLWindowsRHIPlatform()
{
    glfwTerminate();
}

OpenGLDeviceContext* OpenGLWindowsRHIPlatform::RHIPlatformCreateOpenGLContext(Window* InWindow)
{
    WindowsWindow* Window = static_cast<WindowsWindow*>(InWindow);
    OpenGLWindowsDeviceContext* Context = new OpenGLWindowsDeviceContext(Window->GetWindowsHandle(), Window->GetWindowsDeviceContext());
    
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
