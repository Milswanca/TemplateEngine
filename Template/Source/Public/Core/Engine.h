#pragma once
#include "Core/Object.h"
#include "Rendering/RHI/RHI.h"
#include <string>
#include <vector>

struct GLFWwindow;
class Object;
class World;

#define IMPLEMENT_MAIN(screenWidth, screenHeight, screenTitle, applicationClass) \
	int main() \
	{ \
		Engine* Eng = new Engine(nullptr); \
		Eng->Init(); \
		Eng->CreateMainWindow(screenWidth, screenHeight, screenTitle); \
		Eng->InitWorld(); \
		Eng->GetWorld()->SpawnActor<applicationClass>(); \
		Eng->Run(); \
		Eng->Shutdown(); \
		delete Eng; \
		return 0; \
	} \

extern class Engine* s_Engine;

class Engine : public Object
{
public:
	IMPLEMENT_CONSTRUCTOR(Engine, Object);

public:
	static unsigned int s_WindowWidth;
	static unsigned int s_WindowHeight;
	static Engine* Get();


	virtual void Init();
	virtual void InitWorld();
	int CreateMainWindow(int InWidth, int InHeight, const std::string& InTitle);
	int Run();
	virtual void Shutdown();

	virtual World* GetWorld() const;
	RHI* GetRHI() const;
	GLFWwindow* GetMainWindow() const;

	template<typename T>
	T* NewObject(Object* InOuter = nullptr)
	{
		InOuter = InOuter == nullptr ? s_Engine : InOuter;

		T* NewObj = new T(InOuter);
		NewObj->Begin();
		m_Objects.push_back(NewObj);
		return NewObj;
	}

	void DestroyObject(Object* InObj)
	{
		if (InObj == nullptr)
			return;
	
		InObj->End();
		m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), InObj), m_Objects.end());
		delete InObj;
	}

private:
	std::vector<Object*> m_Objects;

	World* m_CurrentWorld;
	GLFWwindow* m_MainWindow;
};