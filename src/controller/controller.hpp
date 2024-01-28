#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <variant>

namespace json
{
  class controller
  {
  public:
    std::variant<std::monostate, std::string> execute();
  };
}

#endif // CONTROLLER_H
