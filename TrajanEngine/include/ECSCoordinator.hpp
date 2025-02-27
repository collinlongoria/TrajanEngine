#ifndef ECSCOORDINATOR_HPP
#define ECSCOORDINATOR_HPP

#include "EngineAPI.hpp"

#include "ComponentManager.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

class ECSCoordinator {
public:
	void Init() {
		// Create all managers
		componentManager = std::make_unique<ComponentManager>();
		entityManager = std::make_unique<EntityManager>();
		systemManager = std::make_unique<SystemManager>();
	}

	/*********************************
	*
	* Entity Functions:
	* 
	*********************************/

	Entity CreateEntity() {
		return entityManager->CreateEntity();
	}

	void DestroyEntity(Entity entity) {
		entityManager->DestroyEntity(entity);

		componentManager->EntityDestoryed(entity);

		systemManager->EntityDestroyed(entity);
	}

	/*********************************
	*
	* Component Functions:
	* 
	*********************************/

	template<typename T>
	void RegisterComponent() {
		componentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T component) {
		componentManager->AddComponent<T>(entity, component);

		auto signature = entityManager->GetSignature(entity);
		signature.set(componentManager->GetComponentType<T>(), true);
		entityManager->SetSignature(entity, signature);

		systemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(Entity entity) {
		componentManager->RemoveComponent<T>(entity);

		auto signature = entityManager->GetSignature(entity);
		signature.set(componentManager->GetComponentType<T>(), false);
		entityManager->SetSignature(entity, signature);

		systemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(Entity entity) {
		return componentManager->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentType GetComponentType() {
		return componentManager->GetComponentType<T>();
	}

	/*********************************
	*
	* System Functions:
	* 
	*********************************/

	template<typename T>
	std::shared_ptr<T> RegisterSystem() {
		return systemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature) {
		systemManager->SetSignature<T>(signature);
	}

private:
	std::unique_ptr<ComponentManager> componentManager;
	std::unique_ptr<EntityManager> entityManager;
	std::unique_ptr<SystemManager> systemManager;
};

#endif