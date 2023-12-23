#pragma once
#include "Rendering/RHI/Resources/RHIDeviceContext.h"

struct WindowDesc
{
public:
    const wchar_t* m_Title = L"";
    unsigned int m_X = 0;
    unsigned int m_Y = 0;
    unsigned int m_Width = 0;
    unsigned int m_Height = 0;
};

class Window
{
public:
    Window() = delete;
    Window(const WindowDesc& InDesc);
    virtual ~Window();

    RHIDeviceContext* CreateDeviceContext();
    void MakeWindowCurrent();
    virtual void SwapWindowBuffers();
    
    const WindowDesc& GetDescription() const;
    RHIDeviceContext* GetDeviceContext() const;
    
protected:
    WindowDesc& GetDescription();
    
private:
    WindowDesc m_WindowDescription;
    RHIDeviceContext* m_DeviceContext;
};