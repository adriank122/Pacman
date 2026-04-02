#include "gui_renderer.h"
#include "game.h"
#include "map.h"
#include "platform_utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

GUIRenderer::GUIRenderer() : currentScreen("menu"), window(nullptr) {
    // Create window with space for UI below the map
    int totalHeight = WINDOW_HEIGHT + UI_HEIGHT;
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, totalHeight), "PACMAN");
    window->setFramerateLimit(60);
    
    // Load font
    if (!fonts.loadFromFile("resources/fonts/Roboto-Regular.ttf")) {
        cerr << "Warning: Could not load font from resources/fonts/Roboto-Regular.ttf" << endl;
        cerr << "Text rendering will not work properly!" << endl;
    }
    
    if (!window) {
        cerr << "Failed to create SFML window!" << endl;
    }
}

GUIRenderer::~GUIRenderer() {
    if (window) {
        window->close();
        delete window;
    }
}

void GUIRenderer::handleEvents() {
    if (!window) return;
    
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::W: inputQueue.push('w'); break;
                case sf::Keyboard::A: inputQueue.push('a'); break;
                case sf::Keyboard::S: inputQueue.push('s'); break;
                case sf::Keyboard::D: inputQueue.push('d'); break;
                case sf::Keyboard::Num1: inputQueue.push('1'); break;
                case sf::Keyboard::Num2: inputQueue.push('2'); break;
                case sf::Keyboard::Num3: inputQueue.push('3'); break;
                case sf::Keyboard::Num4: inputQueue.push('4'); break;
                case sf::Keyboard::O: inputQueue.push('o'); break;
                case sf::Keyboard::M: inputQueue.push('m'); break;
                case sf::Keyboard::Return: inputQueue.push(13); break;
                default: break;
            }
        }
    }
}

void GUIRenderer::clear() {
    if (window) {
        window->clear(sf::Color::Black);
    }
}

char GUIRenderer::getChar() {
    if (!inputQueue.empty()) {
        char c = inputQueue.front();
        inputQueue.pop();
        return c;
    }
    return 0;
}

bool GUIRenderer::keyAvailable() {
    handleEvents();
    return !inputQueue.empty() && window->isOpen();
}

void GUIRenderer::sleep(int milliseconds) {
    sleep_ms(milliseconds);
    handleEvents();
}

void GUIRenderer::renderTile(int row, int col, char tileChar, sf::RenderWindow& win) {
    int x = col * TILE_SIZE;
    int y = row * TILE_SIZE;
    
    sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    tile.setPosition(x, y);
    
    sf::CircleShape shape;
    
    switch (tileChar) {
        case 'x':  // Wall
            tile.setFillColor(sf::Color::Blue);
            win.draw(tile);
            break;
        case '.':  // Pellet
            shape.setRadius(2);
            shape.setFillColor(sf::Color::Yellow);
            shape.setPosition(x + TILE_SIZE/2 - 2, y + TILE_SIZE/2 - 2);
            win.draw(shape);
            break;
        case 'e':  // Power pellet (energizer)
            shape.setRadius(4);
            shape.setFillColor(sf::Color::Magenta);
            shape.setPosition(x + TILE_SIZE/2 - 4, y + TILE_SIZE/2 - 4);
            win.draw(shape);
            break;
        case 'O':  // Pacman
            shape.setRadius(7);
            shape.setFillColor(sf::Color::Yellow);
            shape.setPosition(x + 1, y + 1);
            win.draw(shape);
            break;
        case 'A':  // Ghost
            shape.setRadius(7);
            shape.setFillColor(sf::Color::Red);
            shape.setPosition(x + 1, y + 1);
            win.draw(shape);
            break;
        case ' ':  // Empty space
            // Draw nothing
            break;
        default:
            break;
    }
}

void GUIRenderer::drawText(const string& text, float x, float y, unsigned int fontSize, 
                          const sf::Color& color, sf::RenderWindow& win) {
    sf::Text sfText(text, fonts, fontSize);
    sfText.setPosition(x, y);
    sfText.setFillColor(color);
    win.draw(sfText);
}

void GUIRenderer::drawCenteredText(const string& text, float y, unsigned int fontSize, 
                                  const sf::Color& color, sf::RenderWindow& win) {
    sf::Text sfText(text, fonts, fontSize);
    float xPos = (WINDOW_WIDTH - sfText.getLocalBounds().width) / 2.0f;
    sfText.setPosition(xPos, y);
    sfText.setFillColor(color);
    win.draw(sfText);
}

void GUIRenderer::drawMenu(sf::RenderWindow& win) {
    // Draw title
    drawCenteredText("PACMAN", 10, 24, sf::Color::Yellow, win);
    
    // Draw author
    drawCenteredText("by Adrian Kaliciecki", 40, 12, sf::Color::White, win);
    
    // Draw menu options
    drawCenteredText("1) New Game", 90, 16, sf::Color::Green, win);
    drawCenteredText("2) Instructions", 120, 16, sf::Color::Green, win);
    drawCenteredText("3) Ranking", 150, 16, sf::Color::Green, win);
    drawCenteredText("4) Quit", 180, 16, sf::Color::Green, win);
    
    // Draw footer
    drawCenteredText("Select option:", 220, 12, sf::Color::Cyan, win);
}

void GUIRenderer::drawGameUI(const SGame& game, sf::RenderWindow& win) {
    // Draw game statistics at the bottom of the window
    sf::RectangleShape uiBg(sf::Vector2f(WINDOW_WIDTH, UI_HEIGHT));
    uiBg.setFillColor(sf::Color(30, 30, 30));
    uiBg.setPosition(0, WINDOW_HEIGHT);
    win.draw(uiBg);
    
    // Draw separator line
    sf::RectangleShape separator(sf::Vector2f(WINDOW_WIDTH, 2));
    separator.setFillColor(sf::Color::White);
    separator.setPosition(0, WINDOW_HEIGHT);
    win.draw(separator);
    
    // Draw status text
    stringstream ss;
    ss << "Time: " << (game.stoper / 1000) << "s";
    drawText(ss.str(), 10, WINDOW_HEIGHT + 5, 12, sf::Color::Green, win);
    
    ss.str("");
    ss.clear();
    ss << "Points: " << game.pman.points;
    drawText(ss.str(), 10, WINDOW_HEIGHT + 25, 12, sf::Color::Cyan, win);
    
    ss.str("");
    ss.clear();
    ss << "Lives: " << game.pman.lives;
    drawText(ss.str(), 10, WINDOW_HEIGHT + 45, 12, sf::Color::Yellow, win);
    
    // Draw food counter
    int food_count = 0;
    for(int i=0; i<17; i++) {
        for(int j=0; j<20; j++) {
            if(game.map.map[i][j]=='.' || game.map.map[i][j]=='e')
                food_count++;
        }
    }
    
    ss.str("");
    ss.clear();
    ss << "Food: " << food_count;
    drawText(ss.str(), 150, WINDOW_HEIGHT + 5, 12, sf::Color::Magenta, win);
}

void GUIRenderer::drawInstructions(sf::RenderWindow& win) {
    drawCenteredText("INSTRUCTIONS", 10, 20, sf::Color::Yellow, win);
    
    drawText("Movement Keys:", 20, 50, 14, sf::Color::White, win);
    drawText("W - Move Up", 30, 70, 12, sf::Color::Green, win);
    drawText("A - Move Left", 30, 85, 12, sf::Color::Green, win);
    drawText("S - Move Down", 30, 100, 12, sf::Color::Green, win);
    drawText("D - Move Right", 30, 115, 12, sf::Color::Green, win);
    
    drawText("Objective:", 20, 145, 14, sf::Color::White, win);
    drawText("Collect pellets (dots) to advance levels", 30, 165, 12, sf::Color::Cyan, win);
    drawText("Avoid ghosts (red) - You have 3 lives", 30, 180, 12, sf::Color::Cyan, win);
    drawText("Special pellets give 5x points", 30, 195, 12, sf::Color::Cyan, win);
    
    drawCenteredText("Press 1 to return to menu", 230, 12, sf::Color::Yellow, win);
}

void GUIRenderer::drawRanking(sf::RenderWindow& win) {
    drawCenteredText("HIGH SCORES", 10, 20, sf::Color::Yellow, win);
    
    ifstream rankFile("ranking.txt");
    if (!rankFile.is_open()) {
        drawCenteredText("No ranking file found", 150, 16, sf::Color::Red, win);
        drawCenteredText("Press 1 to return to menu", 230, 12, sf::Color::Yellow, win);
        return;
    }
    
    string line;
    int yPos = 50;
    int rank = 1;
    
    while (getline(rankFile, line) && rank <= 10 && yPos < WINDOW_HEIGHT - 20) {
        stringstream rankLine;
        rankLine << rank << ". " << line;
        
        sf::Color rankColor = sf::Color::White;
        if (rank == 1) rankColor = sf::Color::Yellow;
        else if (rank == 2) rankColor = sf::Color(192, 192, 192);  // Silver
        else if (rank == 3) rankColor = sf::Color(184, 134, 11);   // Gold-ish
        
        drawText(rankLine.str(), 30, yPos, 14, rankColor, win);
        yPos += 20;
        rank++;
    }
    rankFile.close();
    
    drawCenteredText("Press 1 to return to menu", 230, 12, sf::Color::Yellow, win);
}

void GUIRenderer::drawGameOver(const string& reason, sf::RenderWindow& win) {
    // Draw semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    overlay.setPosition(0, 0);
    win.draw(overlay);
    
    // Draw message box background
    sf::RectangleShape msgBox(sf::Vector2f(WINDOW_WIDTH - 40, 120));
    if (reason == "lives") {
        msgBox.setFillColor(sf::Color(128, 0, 0));
        drawCenteredText("GAME OVER", 60, 24, sf::Color::White, win);
        drawCenteredText("You ran out of lives!", 100, 16, sf::Color::Yellow, win);
        drawCenteredText("Press 'm' for menu", 140, 12, sf::Color::White, win);
    } else if (reason == "time") {
        msgBox.setFillColor(sf::Color(128, 60, 0));
        drawCenteredText("TIME'S UP!", 60, 24, sf::Color::White, win);
        drawCenteredText("You ran out of time!", 100, 16, sf::Color::Yellow, win);
        drawCenteredText("Press 'm' for menu", 140, 12, sf::Color::White, win);
    } else if (reason == "won") {
        msgBox.setFillColor(sf::Color(0, 128, 0));
        drawCenteredText("LEVEL COMPLETE!", 50, 24, sf::Color::White, win);
        drawCenteredText("You ate all the pellets!", 90, 16, sf::Color::Yellow, win);
        drawCenteredText("Press 'o' for next level or 'm' for menu", 130, 12, sf::Color::White, win);
    }
    
    msgBox.setPosition(20, 40);
    win.draw(msgBox);
}

void GUIRenderer::showMenu() {
    if (!window) return;
    currentScreen = "menu";
    
    window->clear(sf::Color::Black);
    drawMenu(*window);
    window->display();
}

void GUIRenderer::showGameState(const SGame &game) {
    if (!window) return;
    currentScreen = "game";
    
    window->clear(sf::Color::Black);
    showMap(game.map);
    drawGameUI(game, *window);
    window->display();
}

void GUIRenderer::showMap(const SMap &map) {
    if (!window) return;
    
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 20; j++) {
            renderTile(i, j, map.map[i][j], *window);
        }
    }
}

void GUIRenderer::showGameCounter(const SGame &game) {
    // Handled by showGameState
    // Kept for interface compatibility
}

void GUIRenderer::showGameOver(const string &reason) {
    if (!window) return;
    
    window->clear(sf::Color::Black);
    drawGameOver(reason, *window);
    window->display();
}

void GUIRenderer::showInstructions() {
    if (!window) return;
    currentScreen = "instructions";
    
    window->clear(sf::Color::Black);
    drawInstructions(*window);
    window->display();
}

void GUIRenderer::showRanking() {
    if (!window) return;
    currentScreen = "ranking";
    
    window->clear(sf::Color::Black);
    drawRanking(*window);
    window->display();
}
