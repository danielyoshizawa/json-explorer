// Main.cpp
//
// Program entry point

#include <iostream>
#include "controller/controller.hpp"

int main()
{
  json::controller controller {};
  auto response = controller.execute();
  if (std::holds_alternative<std::string>(response))
  {
    std::cerr << "### Error - " << std::get<std::string>(response) << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
