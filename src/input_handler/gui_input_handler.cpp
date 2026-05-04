#include "input_handler/gui_input_handler.h"

namespace pacman {
namespace input_handler {

GUIInputHandler::GUIInputHandler(sf::RenderWindow *window)
    : window_(window), lastKeyPressed_(0) {}

void GUIInputHandler::handleEvents() {
  if (!window_)
    return;

  sf::Event event;
  while (window_->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_->close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
      case sf::Keyboard::W:
        lastKeyPressed_ = 'w';
        break;
      case sf::Keyboard::A:
        lastKeyPressed_ = 'a';
        break;
      case sf::Keyboard::S:
        lastKeyPressed_ = 's';
        break;
      case sf::Keyboard::D:
        lastKeyPressed_ = 'd';
        break;
      case sf::Keyboard::Num1:
        lastKeyPressed_ = '1';
        break;
      case sf::Keyboard::Num2:
        lastKeyPressed_ = '2';
        break;
      case sf::Keyboard::Num3:
        lastKeyPressed_ = '3';
        break;
      case sf::Keyboard::Num4:
        lastKeyPressed_ = '4';
        break;
      case sf::Keyboard::O:
        lastKeyPressed_ = 'o';
        break;
      case sf::Keyboard::M:
        lastKeyPressed_ = 'm';
        break;
      case sf::Keyboard::Space:
        lastKeyPressed_ = ' ';
        break;
      case sf::Keyboard::Escape:
        lastKeyPressed_ = 27;
        break;
      case sf::Keyboard::Return:
        lastKeyPressed_ = 13;
        break;
      default:
        break;
      }
    }
  }
}

bool GUIInputHandler::keyAvailable() {
  handleEvents();
  return lastKeyPressed_ != 0 && window_->isOpen();
}

Input GUIInputHandler::getInput() {
  Input input(lastKeyPressed_);
  lastKeyPressed_ = 0;
  return input;
}

} // namespace input_handler
} // namespace pacman
