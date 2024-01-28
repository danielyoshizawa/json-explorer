#pragma once
#ifndef EXPLORER_HPP
#define EXPLORER_HPP

#include <simdjson.h>

namespace json
{
  class explorer
  {
  private:
    simdjson::ondemand::parser parser;
    simdjson::ondemand::document doc;
    std::vector<std::string> path_v;
  private:
    explorer() = delete;
  public:
    explorer(const simdjson::padded_string &resource);
    ~explorer() = default;

    void path(const std::string & path);
    std::string current_path() const;
    std::string show_current();
    void home();
    void previous();
  };
};

#endif // EXPLORER_HPP
