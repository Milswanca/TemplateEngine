#pragma once
#include "Core/Actor.h"

class Application : public Actor
{
protected:
    IMPLEMENT_CONSTRUCTOR(Application, Actor);

    virtual void Begin() override;
};
