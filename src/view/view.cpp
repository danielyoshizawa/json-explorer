#include "view.hpp"
#include <iostream>

json::input::result json::view::next(const std::string & path)
{
  std::string input{};
  std::string parameter{};

  std::cout << "$" << path << ": ";
  std::getline(std::cin, input);

  // Split the input
  std::string command{input};
  if (auto split_pos = input.find_first_of(' '); split_pos != std::string::npos)
  {
    command = input.substr(0, split_pos);
    parameter = input.substr(split_pos + 1);
  }

  return json::input::result{command, parameter};
}

void json::view::print(const std::string & content)
{
  std::cout << content << std::endl;
}
