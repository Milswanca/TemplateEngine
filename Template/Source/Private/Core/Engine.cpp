#include "Core/Engine.h"
#include "Core/World.h"
#include "Platform/Platform.h"
#include "Rendering/RHI/RHI.h"
#include "Rendering/RHI/RHIPlatform.h"
#include <iostream>

unsigned int Engine::s_WindowWidth = 0;
unsigned int Engine::s_WindowHeight = 0;

Engine* s_Engine;

void Engine::Init(const WindowDesc& InWindowDesc)
{
	s_Engine = this;

	m_MainWindow = nullptr;
	m_CurrentWorld = nullptr;
	s_Platform = CreatePlatform();
	s_RHIPlatform = CreateRHIPlatform();
	s_RHI = CreateRHI();
	m_MainWindow = CreateMainWindow(InWindowDesc);

	m_CurrentWorld = NewObject<World>(nullptr);
}

void Engine::Shutdown()
{	
	for (int i = m_Objects.size() - 1; i >= 0; --i)
	{
		delete m_Objects[i];
	}

	m_Objects.clear();

	PlatformDestroyWindow(m_MainWindow);
	m_MainWindow = nullptr;
	
	delete s_RHI;
	s_RHI = nullptr;

	delete s_RHIPlatform;
	s_RHIPlatform = nullptr;

	delete s_Platform;
	s_Platform = nullptr;
}

Engine* Engine::Get()
{
	return s_Engine;
}

World* Engine::GetWorld() const
{
	return m_CurrentWorld;
}

Window* Engine::GetMainWindow() const
{
	return m_MainWindow;
}

Window* Engine::CreateMainWindow(const WindowDesc& InWindowDesc)
{
	m_MainWindow = PlatformCreateWindow(InWindowDesc);
	m_MainWindow->CreateDeviceContext();
	m_MainWindow->MakeWindowCurrent();

	s_WindowWidth = InWindowDesc.m_Width;
	s_WindowHeight = InWindowDesc.m_Height;
	
	RHISetViewport(0, 0, s_WindowWidth, s_WindowHeight);

	return m_MainWindow;
}

void Engine::Run()
{
	while (m_MainWindow != nullptr && !PlatformWantsShutdown())
	{
		s_RHI->RHIBeginFrame();
		s_Platform->PlatformBeginFrame();

		m_CurrentWorld->TickWorld(0.0f);

		s_RHI->RHIEndFrame();
		s_Platform->PlatformEndFrame();
	}
}