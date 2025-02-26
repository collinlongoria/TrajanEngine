#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include "EngineAPI.hpp"

#include <memory>
#include <unordered_map>

#include "Component.hpp"
#include "Entity.hpp"
#include "System.hpp"
#include "Log.hpp"

class ENGINE_API SystemManager {
public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem() {
		const char* type = typeid(T).name();

		if (systems.find(type) != systems.end()) {
			Output("Registering a system of type " + type + " more than once.", Severity::ERROR);
			return nullptr;
		}

		// Create pointer to the system and return it
		auto system = std::make_shared<T>();
		systems.insert({ type, system });
		return system;
	}

	template<typename T>
	void SetSignature(Signature signature) {
		const char* type = typeid(T).name();

		if (systems.find(type) == systems.end()) {
			Output("System of type " + type + " used before being registered.", Severity::ERROR);
			return;
		}

		// Set signature for the system
		signatures.insert({ type, signature });
	}

	void EntityDestroyed(Entity entity) {
		// Erase destroyed entity from all system lists
		for (auto const& pair : systems) {
			auto const& system = pair.second;

			system->entities.erase(entity);
		}
	}

	void EntitySignatureChanged(Entity entity, Signature signature) {
		// Notify each system of signature change
		for (auto const& pair : systems) {
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& system_signature = signatures[type];

			// Entity signature matches system -> insert into set
			if ((signature & system_signature) == system_signature) {
				system->entities.insert(entity);
			}
			// Entity does not match -> erase from the set
			else {
				system->entities.erase(entity);
			}
		}
	}

private:
	// Map from system type string pointer to a signature
	std::unordered_map<const char*, Signature> signatures{};

	// Map from system type string pointer to a system pointer
	std::unordered_map<const char*, std::shared_ptr<System>> systems{};
};

#endif