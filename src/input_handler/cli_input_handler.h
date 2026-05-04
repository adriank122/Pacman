#ifndef PACMAN_INPUT_HANDLER_CLI_INPUT_HANDLER_H
#define PACMAN_INPUT_HANDLER_CLI_INPUT_HANDLER_H

#include "input_handler/input_handler.h"

namespace pacman {
namespace input_handler {

class CLIInputHandler : public InputHandler {
public:
  bool keyAvailable() override;
  Input getInput() override;
};

} // namespace input_handler
} // namespace pacman

#endif // PACMAN_INPUT_HANDLER_CLI_INPUT_HANDLER_H
