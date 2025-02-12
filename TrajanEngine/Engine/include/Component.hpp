#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <cstdint>
#include <bitset>

// Component type alias
using ComponentType = uint8_t;

// Maximum number of components
const ComponentType MAX_COMPONENTS = 32;

// Bitset of component type
using Signature = std::bitset<MAX_COMPONENTS>;

#endif