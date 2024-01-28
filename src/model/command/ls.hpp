#pragma once
#ifndef LS_COMMAND_H
#define LS_COMMAND_H

#include "command.hpp"
#include "../explorer/explorer.hpp"

namespace json
{
  namespace command
  {
    class ls : public command<>
    {
    private:
      json::explorer &explorer;
      std::string &result;
    public:
      virtual ~ls() = default;
      ls(json::explorer & explorer, std::string & result)
        : explorer{explorer}, result{result} {}

      std::variant<std::monostate, std::string> execute() override;
    };
  }
}
#endif // LS_COMMAND_H
