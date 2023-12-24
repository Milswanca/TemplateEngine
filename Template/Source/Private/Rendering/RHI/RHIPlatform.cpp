#include "Rendering/RHI/RHIPlatform.h"

RHIPlatform* s_RHIPlatform = nullptr;

void DeleteRHIPlatform(RHIPlatform* InPlatform)
{
    delete InPlatform;
}
