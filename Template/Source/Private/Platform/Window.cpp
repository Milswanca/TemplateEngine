#include "Platform/Window.h"

#include "Platform/OpenGL/OpenGLWindowsRHIPlatform.h"
#include "Rendering/RHI/RHIPlatform.h"

Window::Window(const WindowDesc& InDesc) : m_WindowDescription(InDesc)
{
}

Window::~Window()
{
    RHIPlatformDeleteDeviceContext(m_DeviceContext);
}

RHIDeviceContext* Window::CreateDeviceContext()
{
    if(m_DeviceContext)
    {
        RHIPlatformDeleteDeviceContext(m_DeviceContext);
        m_DeviceContext = nullptr;
    }
    
    m_DeviceContext = RHIPlatformCreateDeviceContext(this);
    return m_DeviceContext;
}

void Window::MakeWindowCurrent()
{
    RHIPlatformBindDeviceContext(m_DeviceContext);
}

void Window::SwapWindowBuffers()
{
}

WindowDesc& Window::GetDescription()
{
    return m_WindowDescription;
}

const WindowDesc& Window::GetDescription() const
{
    return m_WindowDescription;
}
