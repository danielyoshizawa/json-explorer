// Controller
//
// Controls the application flow
// For this first cut we won't implement a dedicated view,
// in a next iteration we have intention to create one.

#include "controller.hpp"
#include "../model/explorer/explorer.hpp"
#include "../model/request/request.hpp"

// TEST
#include "../model/command/ls.hpp"
#include "../model/command/cd.hpp"

// Main loop, in case of unrecoverable error std::variant<std::string> is returned
// caller is responsible to treat this kind of errors.
std::variant<std::monostate, std::string> json::controller::execute()
{
  std::variant<std::monostate, std::string> result;
  std::string endpoint;
  std::cout << "Enter endpoint address : " << std::endl;
  std::cin >> endpoint; // e.g. "https://dogapi.dog/api/v2/facts"

  json::request req; // Could be static
  simdjson::padded_string resource {req.load(endpoint)}; // TODO : May throw

  json::explorer explorer{resource};

  // TODO : Move to a pool (std::map<name, command>)
  json::command::ls ls_command{explorer};
  json::command::cd cd_command{explorer};

  std::string path{};
  std::string input{};
  std::string command{};
  std::string command_result{};
  do
  {
    std::cout << "$" << explorer.current_path() << ": ";
    std::getline(std::cin, input);

    // TODO : Extract method
    if (auto ls = input.find("ls"); ls != std::string::npos)
    {
      // found ls
      if (input.compare("ls") == 0)
      {
        // TODO : May throw, need to recover from it
        ls_command.execute(path, command_result); // Model
        std::cout << command_result << std::endl; // View
        continue;
      } else {
        std::cout << "Invalid command - should be ls" << std::endl;
      }
    }
    if (auto quit = input.find("quit"); quit != std::string::npos)
    {
      // found quit
      if (input.compare("quit") == 0)
      {
        command = "quit";
        continue;
      } else {
        std::cout << "Invalid command - should be quit" << std::endl;
      }
    }
    if (auto exit = input.find("exit"); exit != std::string::npos)
    {
      // found exit
      if (input.compare("exit") == 0)
      {
        command = "exit";
        continue;
      } else {
        std::cout << "Invalid command - should be exit" << std::endl;
      }
    }
    if (auto cd = input.find("cd"); cd != std::string::npos)
    {
      if (auto split_pos = input.find_first_of(' '); split_pos != std::string::npos)
      {
        command = "cd";
        path = input.substr(split_pos + 1);
        cd_command.execute(path, command_result);
      } else {
        std::cout << "Invalid command - should be cd <path>" << std::endl;
      }
    }
  } while (command.compare("exit") != 0 && command.compare("quit") != 0);

  return result;
}
