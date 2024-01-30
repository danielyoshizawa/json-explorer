#pragma once
#ifndef VIEW_H
#define VIEW_H

#include <string>

namespace json
{
  namespace input
  {
    struct result
    {
      std::string command{};
      std::string parameter{};
      bool is_command(const std::string & _command)
      {
        return command.compare(_command) == 0;
      }
    };
  }

  class view
  {
  public:
    [[nodiscard]] json::input::result next(const std::string & path);
    void print(const std::string & content);
  };
}

#endif // VIEW_H
