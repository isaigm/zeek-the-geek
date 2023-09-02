#pragma once
#include "PhysicsComponent.hpp"
#include "RenderComponent.hpp"
#include "SlotMap.hpp"
struct Entity
{
	SlotMap<RenderComponent>::Key m_renderKey;
	SlotMap<PhysicsComponent>::Key m_physicsKey;
	int m_componentMask = 0;
	int m_tagMask = 0;
	bool operator==(const Entity& e)
	{
		return m_tagMask == e.m_tagMask &&
			m_componentMask == e.m_componentMask &&
			m_physicsKey.gen == e.m_physicsKey.gen &&
			m_physicsKey.id == e.m_physicsKey.id &&
			m_renderKey.gen == e.m_renderKey.gen &&
			m_renderKey.id == e.m_renderKey.id;
	}
	bool hasComponent(int m)
	{
		return (m_componentMask & m) == m;
	}
	bool hasTag(int t)
	{
		return (m_tagMask & t) == t;
	}
	void addTag(int t)
	{
		m_tagMask |= t;
	}
};