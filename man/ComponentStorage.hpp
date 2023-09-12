#pragma once
#include "Entity.hpp"
#include "utils/meta.hpp"
template<typename ComponentList>
struct ComponentStorage
{
	using ListSlots = meta::forall_insert_template<SlotMap, Entity::ComponentList>::type;
	using TupleSlots = meta::replace<std::tuple, ListSlots>::type; 
	template<typename T>
	auto &getComponent(Entity &e)
	{
		if(!e.hasComponent<T>()) throw std::runtime_error("Component doesnt exist");
		constexpr int id = Entity::ComponentTraits::getId<T>();
		return std::get<id>(m_storage)[e.getKey<T>()];
	}
	
	template<typename T>
	void addComponent(T &&cmp, Entity &e)
	{
		if(!e.hasComponent<T>())
		{
			constexpr int id = Entity::ComponentTraits::getId<T>();
			e.getKey<T>() = std::get<id>(m_storage).pushBack(cmp);
			e.m_componentMask |= Entity::ComponentTraits::getMask<T>();
		}
	}
	template<typename T>
	bool removeComponent(Entity& e)
	{
		if (e.hasComponent<T>())
		{
			constexpr int id = Entity::ComponentTraits::getId<T>();
			std::get<id>(m_storage).remove(e.getKey<T>());
			e.m_componentMask ^= Entity::ComponentTraits::getMask<T>();
			return true;
		}
		return false;
	}
private:
	TupleSlots m_storage;

};