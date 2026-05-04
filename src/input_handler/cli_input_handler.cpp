#include "input_handler/cli_input_handler.h"
#include "utils/platform_utils.h"

namespace pacman {
namespace input_handler {

bool CLIInputHandler::keyAvailable() { return utils::key_available(); }

Input CLIInputHandler::getInput() { return Input(utils::get_char()); }

} // namespace input_handler
} // namespace pacman
