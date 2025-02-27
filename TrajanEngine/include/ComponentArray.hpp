#ifndef COMPONENTARRAY_HPP
#define COMPONENTARRAY_HPP

#include <array>
#include <unordered_map>

#include "EngineAPI.hpp"

#include "Entity.hpp"
#include "Log.hpp"

class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
	void InsertData(Entity entity, T component) {
		if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
			Output("Attempted to add component of type: " + std::to_string(T) + " to entity of ID: " + std::to_string(entity) + "!", Severity::ERROR);
			return;
		}

		// Insert entry at end and update map
		size_t index = size;
		entityToIndexMap[entity] = index;
		indexToEntityMap[index] = entity;
		ComponentArray[index] = component;
		size++;
	}

	void RemoveData(Entity entity) {
		if (entityToIndexMap.find(entity) == entityToIndexMap.end()) {
			Output("Removing non-existent component from entity with ID: " + std::to_string(entity) + ", ignored.", Severity::WARNING);
			return;
		}

		// Copy element at end into deleted element's place
		// (Goal is to maintain density)
		size_t indexRemoved = entityToIndexMap[entity];
		size_t indexLast = size - 1;
		componentArray[indexRemoved] = componentArray[indexLast];

		// Update the map
		Entity entityLast = indexToEntityMap[indexLast];
		entityToIndexMap[entityLast] = indexRemoved;
		indexToEntityMap[indexRemoved] = entityLast;

		entityToIndexMap.erase(entity);
		indexToEntityMap.erase(indexLast);

		size--;
	}

	T& GetData(Entity entity) {
		if (entityToIndexMap.find(entity) == entityToIndexMap.end()) {
			Output("Tried to retrieve component of type: " + std::to_string(T) + " from entity of ID: " + std::to_string(entity) + " but entity did not have component, returning default component.", Severity::WARNING);
			static T defaultComponent = {};
			return defaultComponent;
		}

		// Return reference to the component
		return componentArray[entityToIndexMap[entity]];
	}

	void EntityDestroyed(Entity entity) {
		if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
			// Remove entity's component if it exists
			RemoveData(entity);
		}
	}

private:
	std::array<T, MAX_ENTITIES> componentArray;
	std::unordered_map<Entity, size_t> entityToIndexMap;
	std::unordered_map<size_t, Entity> indexToEntityMap;
	size_t size;
};

#endif