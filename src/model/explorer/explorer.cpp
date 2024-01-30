#include "explorer.hpp"
#include <sstream>
#include <iostream>

void json::explorer::path(const std::string &path)
{
  path_v.push_back(path);
}

std::string json::explorer::current_path() const
{
  std::string current_path;
  for (auto p : path_v)
  {
    current_path += "/" + p;
  }

  return current_path;
}

std::string json::explorer::show_current()
{
  std::stringstream ss;
  try
  {
    ss << doc.at_pointer(current_path());
  }
  catch (simdjson::simdjson_error &err)
  {
    std::cerr << "Unable to show content : " << err.what() << std::endl;
  }

  return ss.str();
}

void json::explorer::home()
{
  path_v.clear();
}

void json::explorer::previous()
{
  path_v.pop_back();
}

void json::explorer::parse(const std::string &resource)
{
  current_resource = simdjson::padded_string(resource); // Need to make a copy or else when it goes out of scope doc will lose reference.
  auto error = parser.iterate(current_resource).get(doc);

  if (error) // TODO : Kinda useless, maybe let it throw
  {
    std::cerr << error << std::endl;
  }

  path_v.clear();
}
