#pragma once
#ifndef CD_COMMAND_H
#define CD_COMMAND_H

#include "command.hpp"
#include "../explorer/explorer.hpp"

namespace json
{
  namespace command
  {
    class cd : public command
    {
    private:
      json::explorer &explorer;
    public:
      virtual ~cd() = default;
      cd(json::explorer & explorer): explorer{explorer} {}

      std::variant<std::monostate, std::string> execute(const std::string & path, std::string & result) override;
    };
  }
}
#endif // LS_COMMAND_H
