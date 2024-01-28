#pragma once
#ifndef LS_COMMAND_H
#define LS_COMMAND_H

#include "command.hpp"
#include "../explorer/explorer.hpp"

namespace json
{
  namespace command
  {
    class ls : public command
    {
    private:
      json::explorer &explorer;
    public:
      virtual ~ls() = default;
      ls(json::explorer & explorer) : explorer{explorer} {}

      std::variant<std::monostate, std::string> execute(const std::string & path, std::string & result) override;
    };
  }
}
#endif // LS_COMMAND_H
