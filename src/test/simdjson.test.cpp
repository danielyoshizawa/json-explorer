#include <catch2/catch_test_macros.hpp>
#include <simdjson.h>

TEST_CASE("Getting a value inside objects using brackets", "[simdjson]")
{
  auto abstract_json = R"(
    {"str" : { "123" : { "abc" : 3.14 }}}
  )"_padded;
  simdjson::ondemand::parser parser;
  auto doc = parser.iterate(abstract_json);
  double x = doc["str"]["123"]["abc"].get_double();

  REQUIRE(x == 3.14);
};

TEST_CASE("Getting a value inside objects getting the object", "[simdjson]")
{
  auto abstract_json = R"(
    {"str" : { "123" : { "abc" : 3.14 }}}
  )"_padded;
  simdjson::ondemand::parser parser;
  auto doc = parser.iterate(abstract_json);

  simdjson::ondemand::value obj_str = doc["str"];
  simdjson::ondemand::value obj_123 = obj_str["123"];
  simdjson::ondemand::value obj_abc = obj_123["abc"];

  double x = obj_abc.get_double();

  REQUIRE(x == 3.14);
}

TEST_CASE("Identifying the type of a value is an object", "[simdjson]")
{
  auto abstract_json = R"(
    {"str" : { "123" : { "abc" : 3.14 }}}
  )"_padded;
  simdjson::ondemand::parser parser;
  auto doc = parser.iterate(abstract_json);

  simdjson::ondemand::object obj_str;
  auto error = doc["str"].get(obj_str);
  auto is_obj{false};
  if (!error)
  {
    is_obj = true;
  }

  REQUIRE(is_obj);
}

TEST_CASE("Identifying the type of a value is not an array", "[simdjson]")
{
  auto abstract_json = R"(
    {"str" : { "123" : { "abc" : 3.14 }}}
  )"_padded;
  simdjson::ondemand::parser parser;
  auto doc = parser.iterate(abstract_json);

  simdjson::ondemand::array array_str;
  auto error = doc["str"].get(array_str);
  auto is_array{false};
  if (!error)
  {
    is_array = true;
  }

  REQUIRE_FALSE(is_array);
}

TEST_CASE("Consuming an object doesn't invalidate the previous", "[simdjson]")
{
  auto abstract_json = R"(
    {"str" : { "123" : { "abc" : 3.14 }}}
  )"_padded;
  simdjson::ondemand::parser parser;
  auto doc = parser.iterate(abstract_json);

  simdjson::ondemand::object obj_str;
  auto error = doc["str"].get(obj_str);
  simdjson::ondemand::object obj_123;
  error = obj_str.find_field("123").get(obj_123);
  if (error)
  {
    REQUIRE(false); // To fail if the previous behavior is incorrect
  }
  simdjson::ondemand::object obj_str_2;
  error = doc["str"].get(obj_str_2);
  if (error)
  {
    REQUIRE(false); // To fail if the previous behavior is incorrect
  }
}

TEST_CASE("Validating element type", "[simdjson]")
{
  auto abstract_json = R"(
    {"str" : { "123" : [{ "abc" : 3.14 }]}}
  )"_padded;
  simdjson::ondemand::parser parser;
  auto doc = parser.iterate(abstract_json);

  simdjson::ondemand::object obj_123;
  auto error = doc["str"]["123"].get(obj_123);
  // simdjson::ondemand::object obj_123;
  // error = obj_str.find_field("abc").get(obj_123);
  if (error)
  {
    REQUIRE(true); // Not an object
    // Not an object
  }
  simdjson::ondemand::array arr_123;
  error = doc["str"]["123"].get(arr_123);
  if (error)
  {
    REQUIRE(false); // Should cast correct now
  }
}

TEST_CASE("Checking the type of the first element - Array", "[simdjson]")
{
  auto abstract_json = R"(
    []
  )"_padded;
  simdjson::ondemand::parser parser;
  auto doc = parser.iterate(abstract_json);

  simdjson::ondemand::object obj;
  auto error = doc.get(obj);
  if (error)
  {
    REQUIRE(true); // Not an object
  }

  simdjson::ondemand::array arr;
  error = doc.get(arr);
  if (error)
  {
    REQUIRE(false);
  }
}

TEST_CASE("Checking the type of the first element - Object", "[simdjson]")
{
  auto abstract_json = R"(
    {}
  )"_padded;
  simdjson::ondemand::parser parser;
  auto doc = parser.iterate(abstract_json);

  simdjson::ondemand::array arr;
  auto error = doc.get(arr);
  if (error)
  {
    REQUIRE(true); // Not an array
  }

  simdjson::ondemand::object obj;
  error = doc.get(obj);
  if (error)
  {
    REQUIRE(false);
  }
}

TEST_CASE("Accessing more than one level", "[simdjson]")
{
  auto abstract_json = R"(
    {"str" : { "123" : { "abc" : 3.14 }}}
  )"_padded;
  simdjson::ondemand::parser parser;
  auto doc = parser.iterate(abstract_json);

  simdjson::ondemand::object obj_123;
  auto error = doc.at_pointer("/str/123").get(obj_123);
  if (error)
  {
    REQUIRE(false);
  }

  double x = obj_123["abc"].get_double();

  REQUIRE(x == 3.14);
}

TEST_CASE("Accessing more than one level using at_pointer twice", "[simdjson]")
{
  auto abstract_json = R"(
    {"str" : { "123" : { "abc" : 3.14 }}}
  )"_padded;
  simdjson::ondemand::parser parser;
  auto doc = parser.iterate(abstract_json);

  simdjson::ondemand::object obj_str;
  auto error = doc.at_pointer("/str").get(obj_str);
  if (error)
  {
    REQUIRE(false);
  }
  simdjson::ondemand::object obj_123;
  error = doc.at_pointer("/str/123").get(obj_123);

  double x = obj_123["abc"].get_double();

  REQUIRE(x == 3.14);
}
