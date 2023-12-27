#pragma once
#include "utils/meta.hpp"
#include "../cmp/RenderComponent.hpp"
#include "../cmp/PhysicsComponent.hpp"
#include "../cmp/AnimationComponent.hpp"
#include "../cmp/LevelComponent.hpp"
#include "../cmp/PlantDataComponent.hpp"
#include "../cmp/PlayerDataComponent.hpp"
#include "../cmp/GameInfoComponent.hpp"
#include "../cmp/ExplodableDataComponent.hpp"
#include "../cmp/SfxComponent.hpp"
#include "../cmp/TickComponent.hpp"
#include "../cmp/MonsterDataComponent.hpp"
#include "utils/SlotMap.hpp"
#include <tuple>


template<typename T>
using Key = typename SlotMap<typename T::type, T::val>::Key;

template<typename T>
using NewSlotMap = SlotMap<typename T::type, T::val>;
	
template<typename T>
using ExtractType = typename T::type;

using SlotMapList = meta::TypeList<meta::Pair<PhysicsComponent, 204>, 
meta::Pair<RenderComponent, 204>, meta::Pair<AnimationComponent, 204>, meta::Pair<PlantDataComponent, 204>,
meta::Pair<TickComponent, 204>, meta::Pair<MonsterDataComponent, 1>, meta::Pair<PlayerDataComponent, 1>, meta::Pair<ExplodableDataComponent, 32>>;
using ComponentList = meta::forall_insert_template<ExtractType, SlotMapList>::type;

using ListKeys = meta::forall_insert_template<Key, SlotMapList>::type;
using TupleKeys = meta::replace<std::tuple, ListKeys>::type;
using ComponentTraits = meta::ComponentTraits<ComponentList>;

using ListSlots = meta::forall_insert_template<NewSlotMap, SlotMapList>::type;
using TupleSlots = meta::replace<std::tuple, ListSlots>::type;

using SingletonComponentList = meta::TypeList<LevelComponent, GameInfoComponent, SfxComponent>;
using TupleSingleton = meta::replace<std::tuple, SingletonComponentList>::type;