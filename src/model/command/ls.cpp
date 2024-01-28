#include "ls.hpp"
#include <iostream>

std::variant<std::monostate, std::string> json::command::ls::execute()
{
  result = explorer.show_current();

  return std::variant<std::monostate, std::string>{}; // TODO : Implement error handler
}
