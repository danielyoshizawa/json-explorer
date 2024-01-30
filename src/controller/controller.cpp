// Controller
//
// Controls the application flow

#include "controller.hpp"
#include "../model/explorer/explorer.hpp"
#include "../model/request/request.hpp"
#include "../view/view.hpp"

// TEST
#include "../model/command/ls.hpp"
#include "../model/command/cd.hpp"
#include "../model/command/load.hpp"

// Main loop, in case of unrecoverable error std::variant<std::string> is returned
// caller is responsible to treat this kind of errors.
std::variant<std::monostate, std::string> json::controller::execute()
{
  std::variant<std::monostate, std::string> result;

  json::view view{};
  json::request req; // Could be static
  json::explorer explorer;

  // TODO : Move to a pool (std::map<name, command>)
  json::command::ls ls_command{explorer};
  json::command::cd cd_command{explorer};
  json::command::load load_command{req};

  std::string command_result{};
  json::input::result view_result{};
  do
  {
     view_result = view.next(explorer.current_path());

    // TODO : Extract method
    if (view_result.is_command("ls"))
    {
      // TODO : May throw, need to recover from it
      ls_command.execute(view_result.parameter, command_result); // Model
      view.print(command_result);
      continue;
    }
    if (view_result.is_command("cd"))
    {
      if (view_result.parameter.length()) // Maybe empty cd would stay at the same place
      {
        cd_command.execute(view_result.parameter, command_result);
      } else {
        // TODO : Change how errors are treated, for now print in the view
        view.print("Invalid command - should be cd <path>");
      }
    }
    if (view_result.is_command("load"))
    {
      if (view_result.parameter.length())
      {
        std::string load_result{}; // I don't really need to keep it around
        load_command.execute(view_result.parameter, load_result);
        explorer.parse(load_result);
      } else {
        // TODO : Change how errors are treated, for now print in the view
        view.print("Invalid command - should be load <path>");
      }
    }
  } while (!view_result.is_command("exit") && !view_result.is_command("quit"));

  return result;
}
