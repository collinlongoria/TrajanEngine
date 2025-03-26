#include <functional>
#include <unordered_map>
#include <typeindex>
#include <any>
#include <optional>

#include "Entity.hpp"

class EventBus {
public:
	template<typename T>
	using Callback = std::function<void(const T&)>;

	// Bind member function for specific entity
	template<typename T, typename Obj>
	void on(Entity id, void (Obj::* method)(const T&), Obj* instance) {
		addListener<T>(std::make_optional(id), [instance, method](const T& e) {
			(instance->*method)(e);
		});
	}

	// Member function, global listener
	template<typename T, typename Obj>
	void on(void (Obj::* method)(const T&), Obj* instance) {
		addListener<T>(std::nullopt, [instance, method](const T& e) {
			(instance->*method)(e);
		});
	}

	// Lambda or free function for entity
	template<typename T>
	void on(Entity id, Callback<T> cb) {
		addListener<T>(std::make_optional(id), std::move(cb));
	}

	// Lambda or free function globally
	template<typename T>
	void on(Callback<T> cb) {
		addListener<T>(std::nullopt, std::move(cb));
	}

	// Emit an event (global)
	template<typename T>
	void emit(const T& data) {
		emitTo<T>(std::nullopt, data);
	}

	// Emit to specific entity
	template<typename T>
	void emit(Entity id, const T& data) {
		emitTo<T>(std::make_optional(id), data);
	}

	// One-time listener
	template<typename T>
	void once(Callback<T> cb) {
		std::type_index type = typeid(T);
		std::optional<EntityID> key = std::nullopt;
		auto wrapper = std::make_shared<Callback<T>>();
		*wrapper = [this, cb, wrapper](const T& e) {
			cb(e);
			this->off<T>(*wrapper);
			};
		addListener<T>(key, *wrapper);
	}

	// Queue delayed event
	template<typename T>
	void emitLater(const T& data, std::optional<Entity> id = std::nullopt) {
		queuedEvents.emplace_back(typeid(T), std::make_any<T>(data), id);
	}

	void dispatchQueued() {
		for (const auto& event : queuedEvents) {
			dispatchAny(event);
		}
		queuedEvents.clear();
	}

private:
	using AnyCallback = std::function<void(const std::any&)>;
	struct QueuedEvent {
		std::type_index type;
		std::any data;
		std::optional<Entity> target;
		QueuedEvent(std::type_index t, std::any d, std::optional<Entity> tgt)
			: type(t), data(std::move(d)), target(tgt) {}
	};

	std::vector<QueuedEvent> queuedEvents;

	std::unordered_map<std::type_index, std::unordered_map<std::optional<Entity>, std::vector<AnyCallback>>> listeners;

	template<typename T>
	void addListener(std::optional<Entity> id, Callback<T> cb) {
		std::type_index type = typeid(T);
		listeners[type][id].emplace_back([cb = std::move(cb)](const std::any_cast& anyData) {
			cb(std::any_cast<const T&>(anyData));
			}
		);
	}

	template<typename T>
	void emitTo(std::optional<Entity> id, const T& data) {
		std::type_index type = typeid(T);

		// Targeted
		if (auto it = listeners.find(type); it != listeners.end()) {
			auto& table = it->second;

			if (table.count(id)) {
				for (auto& cb : table[id]) cb(data);
			}

			// Must also notify global listeners
			if (id && table.count(std::nullopt)) {
				for (auto& cb : table[std::nullopt]) cb(data);
			}
		}
	}

	void dispatchAny(const QueuedEvent& event) {
		auto it = listeners.find(event.type);
		if (it != listeners.end()) {
			auto& map = it->second;
			auto& list = map[event.target];
			for (auto& cb : list) cb(event.data);

			if (event.target && map.count(std::nullopt)) {
				for (auto& cb : map[std::nullopt]) cb(event.data);
			}
		}
	}

};