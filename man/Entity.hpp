#pragma once
#include "types.hpp"
struct Entity
{
	template<typename T>
	auto &getKey() const
	{
		return std::get<ComponentTraits::template getId<T>()>(m_keys);
	}
	template<typename T>
	void setKey(auto &&key)
	{
		std::get<ComponentTraits::template getId<T>()>(m_keys) = key;
	}
	template<typename T>
	bool compareKeys(const Entity &e)
	{
		auto key1 = getKey<T>(); 
		auto key2 = e.getKey<T>();
		return key1.id == key2.id && key1.gen == key2.gen;
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