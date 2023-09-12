#pragma once
#include "utils/meta.hpp"
#include "../cmp/RenderComponent.hpp"
#include "../cmp/PhysicsComponent.hpp"
#include "utils/SlotMap.hpp"
#include <tuple>

constexpr int MAX_ENTITIES = 204;

template<typename Component>
using Key = SlotMap<Component>::Key;

template<typename Component>
using NewSlotMap = SlotMap<Component, MAX_ENTITIES>;
	
using ComponentList = meta::TypeList<RenderComponent, PhysicsComponent>;
	

using ListKeys = meta::forall_insert_template<Key, ComponentList>::type;
using TupleKeys = meta::replace<std::tuple, ListKeys>::type;
using ComponentTraits = meta::ComponentTraits<ComponentList>;

using ListSlots = meta::forall_insert_template<NewSlotMap, ComponentList>::type;
using TupleSlots = meta::replace<std::tuple, ListSlots>::type;