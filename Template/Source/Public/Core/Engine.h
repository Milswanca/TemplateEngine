#pragma once
#include "Core/Object.h"
#include <string>
#include <vector>

class Object;
class World;
class Window;
struct WindowDesc;

extern class Engine* s_Engine;

class Engine : public Object
{
public:
	IMPLEMENT_CONSTRUCTOR(Engine, Object);

public:
	static unsigned int s_WindowWidth;
	static unsigned int s_WindowHeight;
	static Engine* Get();
	
	virtual void Init(const WindowDesc& InWindowDesc);
	Window* CreateMainWindow(const WindowDesc& InWindowDesc);
	void Run();
	virtual void Shutdown();

	virtual World* GetWorld() const;
	Window* GetMainWindow() const;

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
	Window* m_MainWindow;
};