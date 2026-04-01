#include "platform_utils.h"
#include <iostream>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

using namespace std;

void clear_screen() {
    std::system("clear");
}

void sleep_ms(int milliseconds) {
    if (milliseconds > 0) {
        this_thread::sleep_for(chrono::milliseconds(milliseconds));
    }
}

// Configure terminal for non-blocking input
static struct termios original_termios;

static void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

static void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &original_termios);
    atexit(disable_raw_mode);
    
    struct termios raw = original_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

bool key_available() {
    static bool raw_mode_enabled = false;
    if (!raw_mode_enabled) {
        enable_raw_mode();
        raw_mode_enabled = true;
    }
    
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    
    return select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &tv) > 0;
}

char get_char() {
    char c = 0;
    if (read(STDIN_FILENO, &c, 1) > 0) {
        return c;
    }
    return 0;
}
