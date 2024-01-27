#include <catch2/catch_test_macros.hpp>
#include "../explorer.hpp"

TEST_CASE("Walking the walk", "[explorer]")
{
  simdjson::padded_string json = R"([
        {"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]},
        {"make":"Kia", "model":"Soul", "year":2012,"tire_pressure":[30.1,31.0,28.6,40.4]},
        {"make":"Toyota", "model":"Tercel", "year":1999,"tire_pressure":[29.8,30.0,30.2,30.5]}
  ])"_padded;

  json::explorer explorer(json);
  std::string path{"1"};
  explorer.path(path);
  path = "tire_pressure";
  explorer.path(path);
  path = "1";
  explorer.path(path);
  REQUIRE(explorer.current_path().compare("/1/tire_pressure/1") == 0);
};
