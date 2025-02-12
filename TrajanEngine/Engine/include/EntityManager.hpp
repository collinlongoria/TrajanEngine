#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <queue>
#include <array>
#include <cstdint>

#include "Entity.hpp"
#include "Component.hpp"
#include "Log.hpp"

class EntityManager {
public:
	EntityManager() {
		// Init the queue with all possible entity IDs
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
			availableEntities.push(entity);
		}
	}

	~EntityManager() = default;

	Entity CreateEntity() {
		if(livingEntities >= MAX_ENTITIES){
			Output("Entity count exceeded!", Severity::ERROR);
			return -1;
		}

		// Get ID from front of the queue
		Entity id = availableEntities.front();
		availableEntities.pop();
		++livingEntities;

		return id;
	}

	void DestroyEntity(Entity entity) {
		if (entity >= MAX_ENTITIES) {
			Output("Tried to destroy entity of ID: " + std::to_string(entity) + ", but it is out of range.", Severity::ERROR);
			return;
		}

		// Invalidate signature
		signatures[entity].reset();

		// Put destroyed ID at the back of the queue
		availableEntities.push(entity);
		--livingEntities;
	}

	void SetSignature(Entity entity, Signature signature) {

	}

private:
	// queue of unused entity IDs
	std::queue<Entity> availableEntities{};

	// array of signatures (index corresponds to entity ID)
	std::array<Signature, MAX_ENTITIES> signatures{};

	// total living entities
	uint32_t livingEntities{};
};

#endif