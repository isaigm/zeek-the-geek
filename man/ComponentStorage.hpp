#pragma once
#include "Entity.hpp"
#include "types.hpp"
struct ComponentStorage
{
	
	template<typename T>
	auto &getComponent(Entity &e)
	{
		if(!e.hasComponent<T>()) throw std::runtime_error("Component doesnt exist");
		constexpr int id = ComponentTraits::getId<T>();
		return std::get<id>(m_storage)[e.getKey<T>()];
	}
	template<typename T>
	auto &getSingletonComponent()
	{
		return std::get<T>(m_singletonComponent);
	}
	template<typename T>
	void addComponent(T &&cmp, Entity &e)
	{
		constexpr int id = ComponentTraits::getId<T>();

		if(!e.hasComponent<T>())
		{
			e.setKey<T>(std::get<id>(m_storage).pushBack(cmp));
			e.m_componentMask |= ComponentTraits::getMask<T>();
		}else{
			std::get<id>(m_storage)[e.getKey<T>()] = cmp;
		}
	}
	template<typename T>
	bool removeComponent(Entity& e)
	{
		if (e.hasComponent<T>())
		{
			constexpr int id = ComponentTraits::getId<T>();
			std::get<id>(m_storage).remove(e.getKey<T>());
			e.m_componentMask ^= ComponentTraits::getMask<T>();
			return true;
		}
		return false;
	}
private:
	TupleSlots m_storage;
	TupleSingleton m_singletonComponent;

};