#pragma once
#include "../cmp/PhysicsComponent.hpp"
#include "../cmp/RenderComponent.hpp"
#include "../cmp/InputComponent.hpp"
#include "utils/SlotMap.hpp"
#include "utils/meta.hpp"
#include <tuple>

struct Entity
{
	template<typename Component>
	using Key = SlotMap<Component>::Key;
	
	using ComponentList = meta::TypeList<RenderComponent, PhysicsComponent, InputComponent>;
	;

	using ListKeys = meta::forall_insert_template<Key, ComponentList>::type;
	using TupleKeys = meta::replace<std::tuple, ListKeys>::type;
	using ComponentTraits = meta::ComponentTraits<ComponentList>;
	
	template<typename T>
	auto &getKey()
	{
		return std::get<ComponentTraits::template getId<T>()>(m_keys);
	}
	/*
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
	*/
	bool operator==(const Entity &e)
	{
		return false;
	}
	template<typename T>
	bool hasComponent()
	{
		int mask = ComponentTraits::getMask<T>();
		return (m_componentMask & mask) == mask;
	}
	bool hasTag(int t)
	{
		return (m_tagMask & t) == t;
	}
	void addTag(int t)
	{
		m_tagMask |= t;
	}
	int m_componentMask = 0;
	int m_tagMask = 0;
	
	TupleKeys m_keys;
};