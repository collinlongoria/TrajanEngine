#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <set>

#include "EngineAPI.hpp"

#include "Entity.hpp"

class ENGINE_API System {
public:
	std::set<Entity> entities;
};

#endif