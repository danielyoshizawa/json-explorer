#pragma once
#ifndef LOAD_COMMAND_HPP
#define LOAD_COMMAND_HPP

#include "command.hpp"
#include "../request/request.hpp"
#include <variant>

namespace json
{
  namespace command
  {
    class load : public command
    {
    private:
      json::request &request;
    public:
      virtual ~load() = default;
      load(json::request & request) : request{request} {}

      std::variant<std::monostate, std::string> execute(const std::string & path, std::string & result) override;
    };
  }
}

#endif // LOAD_COMMAND_HPP
