#include "Core/Engine.h"
#include "Core/World.h"
#include "Rendering/RHI/Platform/OpenGL/OpenGLRHI.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

unsigned int Engine::s_WindowWidth = 0;
unsigned int Engine::s_WindowHeight = 0;

Engine* s_Engine;

void framebuffer_size_callback(GLFWwindow* Window, int Width, int Height)
{
	Engine::s_WindowWidth = Width;
	Engine::s_WindowHeight = Height;
	glViewport(0, 0, Width, Height);
}

void Engine::Init()
{
	s_Engine = this;

	m_MainWindow = nullptr;
	m_CurrentWorld = nullptr;
	s_RHI = new OpenGLRHI();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void Engine::InitWorld()
{
	m_CurrentWorld = NewObject<World>(nullptr);
}

void Engine::Shutdown()
{
	glfwTerminate();

	for (int i = m_Objects.size() - 1; i >= 0; --i)
	{
		delete m_Objects[i];
	}

	m_Objects.clear();
}

Engine* Engine::Get()
{
	return s_Engine;
}

RHI* Engine::GetRHI() const
{
	return s_RHI;
}

World* Engine::GetWorld() const
{
	return m_CurrentWorld;
}

GLFWwindow* Engine::GetMainWindow() const
{
	return m_MainWindow;
}

int Engine::CreateMainWindow(int InWidth, int InHeight, const std::string& InTitle)
{
	if (m_MainWindow != nullptr)
		return -1;

	m_MainWindow = glfwCreateWindow(InWidth, InHeight, InTitle.c_str(), NULL, NULL);
	if (m_MainWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(m_MainWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	s_WindowWidth = InWidth;
	s_WindowHeight = InHeight;
	glViewport(0, 0, InWidth, InHeight);
	glfwSetFramebufferSizeCallback(m_MainWindow, framebuffer_size_callback);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

int Engine::Run()
{
	while (m_MainWindow != nullptr && !glfwWindowShouldClose(m_MainWindow))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_CurrentWorld->TickWorld(0.0f);

		glfwSwapBuffers(m_MainWindow);
		glfwPollEvents();
	}

	return 0;
}