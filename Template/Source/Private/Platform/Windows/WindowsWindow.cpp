#include "Platform/Windows/WindowsWindow.h"

WindowsWindow::WindowsWindow(const WindowDesc& InDesc) : Window(InDesc)
{
    RECT WindowRect;

    /*Screen/display attributes*/
    int Width = InDesc.m_Width;
    int Height = InDesc.m_Height;
    int Bits = 32;

    WindowRect.left = (long)0;
    WindowRect.right = (long)Width;	
    WindowRect.top = (long)0;
    WindowRect.bottom = (long)Height;

    m_Handle = CreateWindowEx(NULL,
        s_WindowClassName,
        InDesc.m_Title,
        WS_OVERLAPPEDWINDOW |
        WS_CLIPCHILDREN |
        WS_CLIPSIBLINGS,
        InDesc.m_X, InDesc.m_Y,
        WindowRect.right - WindowRect.left,
        WindowRect.bottom - WindowRect.top,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        this);

    int PixelFormat;

    static PIXELFORMATDESCRIPTOR PFD = {
        sizeof(PIXELFORMATDESCRIPTOR),          //size of structure
        1,                                      //default version
        PFD_DRAW_TO_WINDOW |                    //window drawing support
        PFD_SUPPORT_OPENGL |                    //opengl support
        PFD_DOUBLEBUFFER,                       //double buffering support
        PFD_TYPE_RGBA,                          //RGBA color mode
        32,                                     //32 bit color mode
        0, 0, 0, 0, 0, 0,                       //ignore color bits
        0,                                      //no alpha buffer
        0,                                      //ignore shift bit
        0,                                      //no accumulation buffer
        0, 0, 0, 0,                             //ignore accumulation bits
        16,                                     //16 bit z-buffer size
        0,                                      //no stencil buffer
        0,                                      //no aux buffer
        PFD_MAIN_PLANE,                         //main drawing plane
        0,                                      //reserved
        0, 0, 0 };                              //layer masks ignored

    /*      Choose best matching format*/
    PixelFormat = ChoosePixelFormat(GetDeviceContext(), &PFD);

    /*      Set the pixel format to the device context*/
    SetPixelFormat(GetDeviceContext(), PixelFormat, &PFD);

    ShowWindow(m_Handle, SW_SHOWDEFAULT);
    UpdateWindow(m_Handle);
}

WindowsWindow::~WindowsWindow()
{
    DestroyWindow(m_Handle);
}

void WindowsWindow::SwapWindowBuffers()
{
    Window::SwapWindowBuffers();

    SwapBuffers(GetDeviceContext());
}

void WindowsWindow::Repaint()
{
}

HWND WindowsWindow::GetHandle() const
{
    return m_Handle;
}

HDC WindowsWindow::GetDeviceContext() const
{
    return GetDC(m_Handle);
}
