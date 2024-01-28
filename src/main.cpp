// Main.cpp
//
// Program entry point

#include <iostream>
#include <simdjson.h>
#include "explorer.hpp"
#include "model/request/request.hpp"
#include "controller/controller.hpp"

int main()
{
  json::controller controller {};
  auto response = controller.execute();
  if (std::holds_alternative<std::string>(response))
  {
    std::cout << "### Error - " << std::get<std::string>(response) << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
