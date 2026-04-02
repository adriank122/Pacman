#ifndef PACMAN_RENDERING_CLI_RENDERER_H
#define PACMAN_RENDERING_CLI_RENDERER_H

#include "renderer.h"
#include <fstream>

namespace pacman {
namespace rendering {

class CLIRenderer : public Renderer {
public:
    CLIRenderer();
    ~CLIRenderer();
    
    void showMenu() override;
    void showGameState(const core::SGame &game) override;
    void showMap(const core::SMap &map) override;
    void showGameCounter(const core::SGame &game) override;
    void showGameOver(const std::string &reason) override;
    void showInstructions() override;
    void showLeaderboard() override;
    void clear() override;
    
    char getChar() override;
    bool keyAvailable() override;
    void sleep(int milliseconds) override;
    
private:
    void showLeaderboardList();
};

} // namespace rendering
} // namespace pacman

#endif // PACMAN_RENDERING_CLI_RENDERER_H
