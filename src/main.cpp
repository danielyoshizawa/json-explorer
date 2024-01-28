// Main.cpp
//
// Program entry point

#include <iostream>
#include <simdjson.h>
#include "explorer.hpp"
#include "model/request/request.hpp"

int main()
{
  // TODO : Extract class
  std::string endpoint;
  std::cout << "Enter endpoint address : " << std::endl;
  std::cin >> endpoint; // e.g. "https://dogapi.dog/api/v2/facts"

  json::request req; // Could be static
  simdjson::padded_string resource {req.load(endpoint)};

  // TODO : Extract class
  json::explorer explorer{resource};

  std::string path{};
  std::string input{};
  std::string command{};
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
        std::cout << explorer.show_current() << std::endl;
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
        if (path.compare("/") == 0)
        {
          explorer.home();
          continue;
        }
        if (path.compare("..") == 0)
        {
          explorer.previous();
          continue;
        }
        explorer.path(path); // TODO : recover from failure
      } else {
        std::cout << "Invalid command - should be cd <path>" << std::endl;
      }
    }
  } while (command.compare("exit") != 0 && command.compare("quit") != 0);

  return EXIT_SUCCESS;
}
