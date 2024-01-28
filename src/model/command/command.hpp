#pragma once
#ifndef COMMAND_H
#define COMMAND_H

namespace json
{
  namespace command
  {
    // Command interface
    class command
    {
    public:
      virtual ~command() = default;

      template<typename Agent, typename Result, typename ... Arguments>
      virtual std::variant<std::monostate, std::string> execute( Agent & agent, Result & result , const Arguments & ... ) = 0;
    };
  }
}
#endif // COMMAND_H
