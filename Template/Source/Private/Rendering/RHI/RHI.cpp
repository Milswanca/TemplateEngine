#include "Rendering/RHI/RHI.h"

RHI* s_RHI;

void DeleteRHI(RHI* InRHI)
{
    delete InRHI;
}
