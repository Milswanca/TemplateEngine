#include "Platform/Platform.h"
#include "Platform/Windows/WindowsPlatform.h"

#include "Core/Engine.h"
#include "Platform/Windows/WindowsWindow.h"

bool WindowsPlatform::m_bPlatformWantsShutdown = false;

Platform* CreatePlatform()
{
    return new WindowsPlatform();
}

WindowsPlatform::WindowsPlatform() : Platform()
{
    WNDCLASSEX WindowClass = {}; //window class

    /*Fill out the window class structure*/
    WindowClass.cbSize = sizeof(WNDCLASSEX);
    WindowClass.style = CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = WindowsPlatform::HandleWindowMessage;
    WindowClass.cbClsExtra = 0;
    WindowClass.cbWndExtra = 0;
    WindowClass.hInstance = GetModuleHandle(NULL);
    WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WindowClass.hbrBackground = NULL;
    WindowClass.lpszMenuName = NULL;
    WindowClass.lpszClassName = WindowsWindow::s_WindowClassName;
    WindowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

    /*      Register window class*/
    if (!RegisterClassEx(&WindowClass))
    {
        throw "Failed to register window class";
    }
}

void WindowsPlatform::PlatformBeginFrame()
{
    Platform::PlatformBeginFrame();

    MSG Msg;
    while(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
    {
        if(Msg.message == WM_QUIT)
        {
            m_bPlatformWantsShutdown = true;
        }
        
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
}

void WindowsPlatform::PlatformEndFrame()
{
    Platform::PlatformEndFrame();

    s_Engine->GetMainWindow()->SwapWindowBuffers();
}

Window* WindowsPlatform::PlatformCreateWindow(const WindowDesc& InDesc)
{
    return new WindowsWindow(InDesc);
}

void WindowsPlatform::PlatformDestroyWindow(Window* InWindow)
{
    delete InWindow;
}

bool WindowsPlatform::PlatformWantsShutdown()
{
    return m_bPlatformWantsShutdown;
}

LRESULT WindowsPlatform::HandleWindowMessage(HWND InHWND, UINT InMsg, WPARAM InWParam, LPARAM InLParam)
{
    switch(InMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(InHWND, InMsg, InWParam, InLParam);
}
