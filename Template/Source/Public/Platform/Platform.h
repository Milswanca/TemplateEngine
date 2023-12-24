#pragma once
#include "Platform/Window.h"

extern class Platform* s_Platform;
extern class Platform* CreatePlatform();
extern void DeletePlatform(class Platform* InPlatform);

class Platform
{
public:
    virtual void PlatformBeginFrame() {};
    virtual void PlatformEndFrame() {};
    
    virtual Window* PlatformCreateWindow(const WindowDesc& InDesc) = 0;
    virtual void PlatformDestroyWindow(Window* InWindow) = 0;

    virtual bool PlatformWantsShutdown() = 0;
};

inline Window* PlatformCreateWindow(const WindowDesc& InDesc)
{
    return s_Platform->PlatformCreateWindow(InDesc);
}

inline void PlatformDestroyWindow(Window* InWindow)
{
    s_Platform->PlatformDestroyWindow(InWindow);
}

inline bool PlatformWantsShutdown()
{
    return s_Platform->PlatformWantsShutdown();
}