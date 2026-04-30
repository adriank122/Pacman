#ifndef PACMAN_CORE_MAP_LOADER_H
#define PACMAN_CORE_MAP_LOADER_H

#include "core/map/map.h"
#include <string>

namespace pacman {
namespace core {

class MapLoader {
public:
  static Map load(const std::string &path);

private:
  MapLoader() = delete;
};

} // namespace core
} // namespace pacman

#endif // PACMAN_CORE_MAP_LOADER_H
