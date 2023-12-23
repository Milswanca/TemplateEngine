#include "Platform/OpenGL/OpenGLRHIPlatform.h"
#include "Platform/OpenGL/OpenGLWindowsRHIPlatform.h"

RHIPlatform* CreateRHIPlatform()
{
    // TODO Support Other RHI Platforms
    // Currently we only support windows
    return new OpenGLWindowsRHIPlatform();
}

OpenGLDeviceContext::OpenGLDeviceContext()
{
    
}

RHIDeviceContext* OpenGLRHIPlatform::RHIPlatformCreateDeviceContext(Window* InWindow)
{
    return RHIPlatformCreateOpenGLContext(InWindow);
}

void OpenGLRHIPlatform::RHIPlatformBindDeviceContext(RHIDeviceContext* InDevice)
{
    RHIPlatformBindOpenGLContext(static_cast<OpenGLDeviceContext*>(InDevice));
}

void OpenGLRHIPlatform::RHIPlatformDeleteDeviceContext(RHIDeviceContext* InDevice)
{
    RHIPlatformDeleteOpenGLContext(static_cast<OpenGLDeviceContext*>(InDevice));
}
