#include "Core/World.h"

void World::Begin()
{
	m_ConstThis = this;
}

void World::TickWorld(float InDelta)
{
	for (int i = 0; i < m_Actors.size(); ++i)
	{
		m_Actors[i]->Tick(InDelta);
	}
}

World* World::GetWorld() const
{
	return m_ConstThis;
}