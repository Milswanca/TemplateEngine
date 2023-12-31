#pragma once

class Engine;
class World;
class OpenGLRHI;

#define IMPLEMENT_CONSTRUCTOR(className, baseClass) \
    className() = delete; \
	className(Object* InOuter) : baseClass(InOuter) {} \
    virtual ~className() {} \
	friend class Engine; \

class Object
{
protected:
	Object() = delete;
	Object(Object* InOuter);
	~Object();

	virtual void Begin();
	virtual void End();

	virtual World* GetWorld() const;
	virtual Object* GetOuter() const;

private:
	Object* m_Outer;
	World* m_CurrentWorld;
	friend class Engine;
};