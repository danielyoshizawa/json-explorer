#include "explorer.hpp"
#include <sstream>

json::explorer::explorer(const simdjson::padded_string &resource)
{
  auto error = parser.iterate(resource).get(doc);
  if (error)
  {
    std::cerr << error << std::endl;
  }
}

// We will only go forward on the first cut
void json::explorer::path(const std::string & path)
{
  std::string current_path;
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
  ss << doc.at_pointer(current_path());

  return ss.str();
}
