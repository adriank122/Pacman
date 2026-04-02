#ifndef GUI_RENDERER_H
#define GUI_RENDERER_H

#include "renderer.h"
#include <SFML/Graphics.hpp>
#include <queue>

// Forward declarations
struct SGame;
struct SMap;

class GUIRenderer : public Renderer {
public:
    GUIRenderer();
    ~GUIRenderer();
    
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
    sf::RenderWindow* window;
    sf::Font fonts;                      // Font for text rendering
    std::queue<char> inputQueue;
    std::string currentScreen;           // track which screen we're on
    
    static const int TILE_SIZE = 16;
    static const int MAP_WIDTH = 20;
    static const int MAP_HEIGHT = 17;
    static const int WINDOW_WIDTH = 320;   // 20 tiles * 16 pixels
    static const int WINDOW_HEIGHT = 272;  // 17 tiles * 16 pixels
    static const int UI_HEIGHT = 80;       // Space for UI text
    
    // Rendering helpers
    void renderTile(int row, int col, char tileChar, sf::RenderWindow& win);
    void drawText(const std::string& text, float x, float y, unsigned int fontSize, 
                  const sf::Color& color, sf::RenderWindow& win);
    void drawCenteredText(const std::string& text, float y, unsigned int fontSize, 
                          const sf::Color& color, sf::RenderWindow& win);
    void handleEvents();
    void drawMenu(sf::RenderWindow& win);
    void drawGameUI(const SGame& game, sf::RenderWindow& win);
    void drawInstructions(sf::RenderWindow& win);
    void drawRanking(sf::RenderWindow& win);
    void drawGameOver(const std::string& reason, sf::RenderWindow& win);
};

#endif // GUI_RENDERER_H

