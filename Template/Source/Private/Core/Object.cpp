#include "Core/Object.h"
#include "Core/Engine.h"

Object::Object(Object* InOuter)
{
	m_Outer = InOuter;
	m_CurrentWorld = m_Outer != nullptr ? m_Outer->GetWorld() : nullptr;
}

Object::~Object()
{

}

void Object::Begin()
{

}

void Object::End()
{

}

IRHI* Object::GetImmediateRenderer() const
{
	return GetEngine()->GetImmediateRenderer();
}

Engine* Object::GetEngine() const
{
	return Engine::Get();
}

World* Object::GetWorld() const
{
	return m_CurrentWorld;
}

Object* Object::GetOuter() const
{
	return m_Outer;
}