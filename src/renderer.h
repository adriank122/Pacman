#ifndef RENDERER_H
#define RENDERER_H

#include <string>

// Forward declarations to avoid circular dependencies
struct SGame;
struct SMap;

class Renderer {
public:
    virtual ~Renderer() = default;
    
    // Rendering functions
    virtual void showMenu() = 0;
    virtual void showGameState(const SGame &game) = 0;
    virtual void showMap(const SMap &map) = 0;
    virtual void showGameCounter(const SGame &game) = 0;
    virtual void showGameOver(const std::string &reason) = 0;
    virtual void showInstructions() = 0;
    virtual void showRanking() = 0;
    virtual void clear() = 0;
    
    // Input functions
    virtual char getChar() = 0;
    virtual bool keyAvailable() = 0;
    virtual void sleep(int milliseconds) = 0;
};

#endif // RENDERER_H
