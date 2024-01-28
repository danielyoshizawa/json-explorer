#include "cd.hpp"
#include <iostream>

std::variant<std::monostate, std::string> json::command::cd::execute(const std::string & path, std::string & result)
{
  if (path.compare("/") == 0)
  {
    explorer.home();
  } else if (path.compare("..") == 0)
  {
    explorer.previous();
  } else {
    explorer.path(path); // TODO : recover from failure
  }

  return std::variant<std::monostate, std::string>{}; // TODO : Implement error handler
}
