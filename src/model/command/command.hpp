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
    class command
    {
    public:
      virtual ~command() = default;
      virtual std::variant<std::monostate, std::string> execute(const std::string & path, std::string & result) = 0;
    };
  }
}
#endif // COMMAND_H
