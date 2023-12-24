#pragma once
#include "Platform/OpenGL/OpenGLRHIPlatform.h"
#include "Platform/Windows/WindowsPlatform.h"

class OpenGLWindowsDeviceContext : public OpenGLDeviceContext
{
public:
    OpenGLWindowsDeviceContext(HWND InWindowHandle, HDC InDeviceContext);
    ~OpenGLWindowsDeviceContext();

    void MakeCurrent();
    void* GetDeviceContext() override;
    
private:
    HWND m_WindowHandle;
    HDC m_DeviceContext;
    HGLRC m_OpenGLContext;
};

class OpenGLWindowsRHIPlatform : public OpenGLRHIPlatform
{
public:
    OpenGLWindowsRHIPlatform();
    ~OpenGLWindowsRHIPlatform();
    
    OpenGLDeviceContext* RHIPlatformCreateOpenGLContext(Window* InWindow) override;
    void RHIPlatformBindOpenGLContext(OpenGLDeviceContext* InContext) override;
    void RHIPlatformDeleteOpenGLContext(OpenGLDeviceContext* InContext) override;
};
