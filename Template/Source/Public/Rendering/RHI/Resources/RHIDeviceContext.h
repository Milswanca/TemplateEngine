#pragma once
#include "Rendering/RHI/Resources/RHIResource.h"

class RHIDeviceContext : public RHIResource
{
public:
    RHIDeviceContext();

    virtual void* GetDeviceContext() = 0;
};
