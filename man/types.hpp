#pragma once
#include "utils/meta.hpp"
#include "../cmp/RenderComponent.hpp"
#include "../cmp/PhysicsComponent.hpp"
#include "utils/SlotMap.hpp"
#include <tuple>


constexpr int MAX_ENTITIES = 204;

template<typename T>
using Key = SlotMap<typename T::type, T::val>::Key;

template<typename T>
using NewSlotMap = SlotMap<typename T::type, T::val>;
	
template<typename T>
using ExtractType = T::type;

using SlotMapList = meta::TypeList<meta::Pair<PhysicsComponent, 204>, meta::Pair<RenderComponent, 204>>;
using ComponentList = meta::forall_insert_template<ExtractType, SlotMapList>::type;

using ListKeys = meta::forall_insert_template<Key, SlotMapList>::type;
using TupleKeys = meta::replace<std::tuple, ListKeys>::type;
using ComponentTraits = meta::ComponentTraits<ComponentList>;

using ListSlots = meta::forall_insert_template<NewSlotMap, SlotMapList>::type;
using TupleSlots = meta::replace<std::tuple, ListSlots>::type;