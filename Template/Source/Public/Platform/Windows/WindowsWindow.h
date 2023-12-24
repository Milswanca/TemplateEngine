#pragma once
#include "Platform/Window.h"
#include <Windows.h>

class WindowsWindow : public Window
{
public:
    WindowsWindow(const WindowDesc& InDesc);
    ~WindowsWindow();

    virtual void SwapWindowBuffers() override;
    virtual void Repaint();

    HWND GetWindowsHandle() const;
    HDC GetWindowsDeviceContext() const;
    
    static inline const wchar_t* s_WindowClassName = L"TemplateWindowClass";

private:
    HWND m_WindowsHandle;
    HDC m_WindowsDeviceContext;
};
