#ifndef PACMAN_INPUT_HANDLER_INPUT_HANDLER_H
#define PACMAN_INPUT_HANDLER_INPUT_HANDLER_H

#include "input_handler/input.h"

namespace pacman {
namespace input_handler {

class InputHandler {
public:
  virtual ~InputHandler() = default;

  virtual bool keyAvailable() = 0;
  virtual Input getInput() = 0;
};

} // namespace input_handler
} // namespace pacman

#endif // PACMAN_INPUT_HANDLER_INPUT_HANDLER_H
