#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <set>

#include "Entity.hpp"

class System {
public:
	std::set<Entity> entities;
};

#endif