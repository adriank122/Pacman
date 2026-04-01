#ifndef CLI_RENDERER_H
#define CLI_RENDERER_H

#include "renderer.h"
#include <fstream>

class CLIRenderer : public Renderer {
public:
    CLIRenderer();
    ~CLIRenderer();
    
    void showMenu() override;
    void showGameState(const SGame &game) override;
    void showMap(const SMap &map) override;
    void showGameCounter(const SGame &game) override;
    void showGameOver(const std::string &reason) override;
    void showInstructions() override;
    void showRanking() override;
    void clear() override;
    
    char getChar() override;
    bool keyAvailable() override;
    void sleep(int milliseconds) override;
    
private:
    void showRankingList();
};

#endif // CLI_RENDERER_H
