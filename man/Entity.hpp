#pragma once
#include "../cmp/PhysicsComponent.hpp"
#include "../cmp/RenderComponent.hpp"
#include "../cmp/InputComponent.hpp"
#include "utils/SlotMap.hpp"
struct Entity
{
	SlotMap<RenderComponent>::Key   m_renderKey;
	SlotMap<PhysicsComponent>::Key  m_physicsKey;
	SlotMap<InputComponent, 1>::Key m_inputKey;
	int m_componentMask = 0;
	int m_tagMask = 0;
	bool operator==(const Entity& e)
	{
		return m_tagMask == e.m_tagMask &&
			m_componentMask == e.m_componentMask &&
			m_physicsKey.gen == e.m_physicsKey.gen &&
			m_physicsKey.id == e.m_physicsKey.id &&
			m_inputKey.gen == e.m_inputKey.gen &&
			m_inputKey.id == e.m_inputKey.id &&
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