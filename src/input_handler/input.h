#ifndef PACMAN_INPUT_HANDLER_INPUT_H
#define PACMAN_INPUT_HANDLER_INPUT_H

namespace pacman {
namespace input_handler {

class Input {
public:
  Input() : value_('\0') {}
  explicit Input(char c) : value_(c) {}

  char value() const { return value_; }
  bool isNull() const { return value_ == '\0'; }

private:
  char value_;
};

} // namespace input_handler
} // namespace pacman

#endif // PACMAN_INPUT_HANDLER_INPUT_H
