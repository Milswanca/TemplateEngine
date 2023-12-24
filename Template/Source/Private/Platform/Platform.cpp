#include "Platform/Platform.h"

Platform* s_Platform;

void DeletePlatform(Platform* InPlatform)
{
    delete InPlatform;
}
