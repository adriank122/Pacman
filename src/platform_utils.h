#ifndef PLATFORM_UTILS_H
#define PLATFORM_UTILS_H

#include <chrono>
#include <thread>

// Cross-platform terminal utilities
void clear_screen();
void sleep_ms(int milliseconds);
char get_char();
bool key_available();

#endif // PLATFORM_UTILS_H
