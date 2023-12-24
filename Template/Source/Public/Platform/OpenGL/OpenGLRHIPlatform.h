#pragma once
#include "Rendering/RHI/RHIPlatform.h"

class OpenGLDeviceContext : public RHIDeviceContext
{
public:
    OpenGLDeviceContext();

    void* GetDeviceContext() override = 0;
};

class OpenGLRHIPlatform : public RHIPlatform
{
public:
    virtual OpenGLDeviceContext* RHIPlatformCreateOpenGLContext(Window* InWindow) = 0;
    virtual void RHIPlatformBindOpenGLContext(OpenGLDeviceContext* InContext) = 0;
    virtual void RHIPlatformDeleteOpenGLContext(OpenGLDeviceContext* InContext) = 0;

protected:
    RHIDeviceContext* RHIPlatformCreateDeviceContext(Window* InWindow) final;
    void RHIPlatformBindDeviceContext(RHIDeviceContext* InDevice) final;
    void RHIPlatformDeleteDeviceContext(RHIDeviceContext* InDevice) final;
};