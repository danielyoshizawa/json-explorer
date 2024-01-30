#include <catch2/catch_test_macros.hpp>
#include "../model/explorer/explorer.hpp"

TEST_CASE("Walking the walk", "[explorer]")
{
  std::string json = R"([
        {"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]},
        {"make":"Kia", "model":"Soul", "year":2012,"tire_pressure":[30.1,31.0,28.6,40.4]},
        {"make":"Toyota", "model":"Tercel", "year":1999,"tire_pressure":[29.8,30.0,30.2,30.5]}
  ])";

  json::explorer explorer;
  explorer.parse(json);
  std::string path{"1"};
  explorer.path(path);
  path = "tire_pressure";
  explorer.path(path);
  path = "1";
  explorer.path(path);
  REQUIRE(explorer.current_path().compare("/1/tire_pressure/1") == 0);
};

// Not testing invalids yet.
TEST_CASE("Testing commands", "[explorer]")
{
  std::string json = R"([
        {"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]},
        {"make":"Kia", "model":"Soul", "year":2012,"tire_pressure":[30.1,31.0,28.6,40.4]},
        {"make":"Toyota", "model":"Tercel", "year":1999,"tire_pressure":[29.8,30.0,30.2,30.5]}
  ])";

  json::explorer explorer;
  explorer.parse(json);

  SECTION("Testing ls command")
  {
    std::string current(json);
    REQUIRE(explorer.show_current().compare(current) == 0);
  }

  SECTION("Testing cd <path> command")
  {
    explorer.path("0");
    std::string current{R"({"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]})"};
    REQUIRE(explorer.show_current().compare(current) == 0);
  }

  SECTION("Testing cd .. command")
  {
    std::string current(R"([40.1,39.9,37.7,40.4])");
    explorer.path("0");
    explorer.path("tire_pressure");
    REQUIRE(explorer.show_current().compare(current) == 0);
    explorer.previous();
    current = R"({"make":"Toyota", "model":"Cammy", "year":2018,"tire_pressure":[40.1,39.9,37.7,40.4]})";
    REQUIRE(explorer.show_current().compare(current) == 0);
  }

  SECTION("Testing cd / command")
  {
    std::string current(json);
    explorer.path("0");
    explorer.path("tire_pressure");
    explorer.home();
    REQUIRE(explorer.show_current().compare(current) == 0);
  }
}
