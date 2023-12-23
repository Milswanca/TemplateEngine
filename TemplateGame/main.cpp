#include "Core/Engine.h"
#include "Core/World.h"
#include "Application.h"
#include "Platform/Window.h"

int main()
{
    WindowDesc Window;
    Window.m_Width = 620;
    Window.m_Height = 480;
    Window.m_Title = L"Template Engine";
    Engine* Eng = new Engine(nullptr);
    Eng->Init(Window);
    Eng->GetWorld()->SpawnActor<Application>();
    Eng->Run();
    Eng->Shutdown();
    delete Eng;

    return 0;
}