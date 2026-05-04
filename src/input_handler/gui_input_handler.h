#ifndef PACMAN_INPUT_HANDLER_GUI_INPUT_HANDLER_H
#define PACMAN_INPUT_HANDLER_GUI_INPUT_HANDLER_H

#include "input_handler/input_handler.h"
#include <SFML/Graphics.hpp>

namespace pacman {
namespace input_handler {

class GUIInputHandler : public InputHandler {
public:
  explicit GUIInputHandler(sf::RenderWindow *window);

  bool keyAvailable() override;
  Input getInput() override;

private:
  sf::RenderWindow *window_;
  char lastKeyPressed_;

  void handleEvents();
};

} // namespace input_handler
} // namespace pacman

#endif // PACMAN_INPUT_HANDLER_GUI_INPUT_HANDLER_H
