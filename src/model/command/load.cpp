#include "load.hpp"

#include "cd.hpp"
#include <iostream>

 // TODO : Implement error handler
std::variant<std::monostate, std::string> json::command::load::execute(const std::string & path, std::string & result)
{
  result = request.load(path);

  return std::variant<std::monostate, std::string>{};
}
