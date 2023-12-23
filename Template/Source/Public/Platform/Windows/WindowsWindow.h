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

    HWND GetHandle() const;
    HDC GetDeviceContext() const;

    static inline const wchar_t* s_WindowClassName = L"TemplateWindowClass";

private:
    HWND m_Handle;
};
