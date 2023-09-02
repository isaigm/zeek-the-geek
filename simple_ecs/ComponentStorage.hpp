#pragma once
#include "SlotMap.hpp"
#include "PhysicsComponent.hpp"
#include "RenderComponent.hpp"
#include "Entity.hpp"
struct ComponentStorage
{
	RenderComponent& getRenderComponent(Entity &e)
	{
		if (!e.hasComponent(RenderComponent::mask)) throw std::runtime_error("RenderComponent doesnt exist");
		return m_renderStorage[e.m_renderKey];
	}
	PhysicsComponent& getPhysicsComponent(Entity& e)
	{
		if (!e.hasComponent(PhysicsComponent::mask)) throw std::runtime_error("PhysicsComponent doesnt exist");
		return m_physicsStorage[e.m_physicsKey];
	}
	void addRenderComponent(RenderComponent&& renderCmp, Entity& e)
	{
		if (!e.hasComponent(RenderComponent::mask))
		{
			e.m_renderKey = m_renderStorage.pushBack(renderCmp);
			e.m_componentMask |= RenderComponent::mask;
		}
	}
	void addPhysicsComponent(PhysicsComponent && physicsCmp, Entity& e)
	{
		if (!e.hasComponent(PhysicsComponent::mask))
		{
			e.m_physicsKey = m_physicsStorage.pushBack(physicsCmp);
			e.m_componentMask |= PhysicsComponent::mask;
		}
	}
	bool removeRenderComponent(Entity& e)
	{
		if (e.hasComponent(RenderComponent::mask))
		{
			m_renderStorage.remove(e.m_renderKey);
			e.m_componentMask ^= RenderComponent::mask;
			return true;
		}
		return false;
	}
	bool removePhysicsComponent(Entity& e)
	{
		if (e.hasComponent(PhysicsComponent::mask))
		{
			m_physicsStorage.remove(e.m_physicsKey);
			e.m_componentMask ^= PhysicsComponent::mask;
			return true;
		}
		return false;
	}
private:
	SlotMap<PhysicsComponent> m_physicsStorage;
	SlotMap<RenderComponent>  m_renderStorage;
};