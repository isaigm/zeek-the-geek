#pragma once
#include "Entity.hpp"
struct ComponentStorage
{
	//-------->Render
	RenderComponent& getRenderComponent(Entity &e)
	{
		if (!e.hasComponent(RenderComponent::mask)) throw std::runtime_error("RenderComponent doesnt exist");
		return m_renderStorage[e.m_renderKey];
	}
	void addRenderComponent(RenderComponent&& renderCmp, Entity& e)
	{
		if (!e.hasComponent(RenderComponent::mask))
		{
			e.m_renderKey = m_renderStorage.pushBack(renderCmp);
			e.m_componentMask |= RenderComponent::mask;
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
	//-------->Input
	InputComponent& getInputComponent(Entity& e)
	{
		if (!e.hasComponent(InputComponent::mask)) throw std::runtime_error("InputComponent doesnt exist");
		return m_inputStorage[e.m_inputKey];
	}
	void addInputComponent(InputComponent&& inputCmp, Entity& e)
	{
		if (!e.hasComponent(InputComponent::mask))
		{
			e.m_inputKey = m_inputStorage.pushBack(inputCmp);
			e.m_componentMask |= InputComponent::mask;
		}
	}
	bool removeInputComponent(Entity& e)
	{
		if (e.hasComponent(InputComponent::mask))
		{
			m_inputStorage.remove(e.m_inputKey);
			e.m_componentMask ^= InputComponent::mask;
			return true;
		}
		return false;
	}
	//-------->Physics
	PhysicsComponent& getPhysicsComponent(Entity& e)
	{
		if (!e.hasComponent(PhysicsComponent::mask)) throw std::runtime_error("PhysicsComponent doesnt exist");
		return m_physicsStorage[e.m_physicsKey];
	}
	void addPhysicsComponent(PhysicsComponent && physicsCmp, Entity& e)
	{
		if (!e.hasComponent(PhysicsComponent::mask))
		{
			e.m_physicsKey = m_physicsStorage.pushBack(physicsCmp);
			e.m_componentMask |= PhysicsComponent::mask;
		}
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
	SlotMap<InputComponent, 1> m_inputStorage;
};