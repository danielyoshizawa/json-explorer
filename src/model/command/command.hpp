#pragma once
#ifndef COMMAND_H
#define COMMAND_H

#include <variant>
#include <string>

namespace json
{
  namespace command
  {
    // Command interface
    template<class ... Arguments>
    class command
    {
    public:
      virtual ~command() = default;
      virtual std::variant<std::monostate, std::string> execute(Arguments &&...args) = 0;
    };
  }
}
#endif // COMMAND_H
