#include "explorer.hpp"

json::explorer::explorer(const simdjson::padded_string &resource)
{
  auto error = parser.iterate(resource).get(doc);
  if (error)
  {
    std::cerr << error << std::endl;
  }
  std::cout << doc << std::endl;
}

// We will only go forward on the first cut
void json::explorer::path(const std::string & path)
{
  std::string current_path;
  path_v.push_back(path);
  // TODO : Refactor
  for (auto p : path_v)
  {
    std::cout << "/" << p; // TODO : Separation of concepts, shouldn't be here
    current_path += "/" + p;
  }
  std::cout << " : " << std::endl;
  std::cout << doc.at_pointer(current_path) << std::endl;
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
