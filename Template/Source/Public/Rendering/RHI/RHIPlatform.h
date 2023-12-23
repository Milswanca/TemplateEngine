#pragma once
#include "Rendering/RHI/Resources/RHIDeviceContext.h"

class Window;
class RHIDeviceContext;

extern class RHIPlatform* s_RHIPlatform;
extern RHIPlatform* CreateRHIPlatform();

class RHIPlatform 
{
public:
    virtual RHIDeviceContext* RHIPlatformCreateDeviceContext(Window* InWindow) = 0;
    virtual void RHIPlatformBindDeviceContext(RHIDeviceContext* InDevice) = 0;
    virtual void RHIPlatformDeleteDeviceContext(RHIDeviceContext* InDevice) = 0;
};

inline RHIDeviceContext* RHIPlatformCreateDeviceContext(Window* InWindow)
{
    return s_RHIPlatform->RHIPlatformCreateDeviceContext(InWindow);
}

inline void RHIPlatformBindDeviceContext(RHIDeviceContext* InDevice)
{
    s_RHIPlatform->RHIPlatformBindDeviceContext(InDevice);
}

inline void RHIPlatformDeleteDeviceContext(RHIDeviceContext* InDevice)
{
    s_RHIPlatform->RHIPlatformDeleteDeviceContext(InDevice);
}