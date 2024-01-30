#pragma once
#ifndef EXPLORER_HPP
#define EXPLORER_HPP

#include <simdjson.h>

namespace json
{
  class explorer
  {
  private:
    simdjson::ondemand::parser parser{};
    simdjson::ondemand::document doc{};
    std::vector<std::string> path_v;
    simdjson::padded_string current_resource;

  public:
    explorer() = default;
    ~explorer() = default;
    void path(const std::string &path);
    std::string current_path() const;
    std::string show_current();
    void home();
    void previous();
    // TODO : Return errors std::variant
    void parse(const std::string &resource);
  };
};

#endif // EXPLORER_HPP
