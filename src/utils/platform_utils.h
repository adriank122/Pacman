#ifndef PACMAN_UTILS_PLATFORM_UTILS_H
#define PACMAN_UTILS_PLATFORM_UTILS_H

#include <chrono>
#include <thread>

namespace pacman {
namespace utils {

// Cross-platform terminal utilities
void clear_screen();
void sleep_ms(int milliseconds);
char get_char();
bool key_available();

} // namespace utils
} // namespace pacman

#endif // PACMAN_UTILS_PLATFORM_UTILS_H
