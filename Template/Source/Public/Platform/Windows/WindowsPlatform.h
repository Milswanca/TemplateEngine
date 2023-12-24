#pragma once
#include "Platform/Platform.h"
#include <windows.h>

class WindowsPlatform : public Platform
{
public:
    WindowsPlatform();
    
    void PlatformBeginFrame() override;
    void PlatformEndFrame() override;
    
    Window* PlatformCreateWindow(const WindowDesc& InDesc) override;
    void PlatformDestroyWindow(Window* InWindow) override;
    bool PlatformWantsShutdown() override;

private:
    static LRESULT HandleWindowMessage(HWND InHWND, UINT InMsg, WPARAM InWParam, LPARAM InLParam);
    static bool m_bPlatformWantsShutdown;
};