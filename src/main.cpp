// Main.cpp
//
// Program entry point

#include <iostream>
#include <curl/curl.h>
#include <simdjson.h>

int main()
{
  std::cout << "Say hello to my little friend!!!" << std::endl;

  // Testing libcurl
  CURL *curl = curl_easy_init();
  if (curl) {
    CURLcode response;
    curl_easy_setopt(curl, CURLOPT_URL, "https://dog-api.kinduff.com/api/facts");
    response = curl_easy_perform(curl); // By default curl_easy_perform will print the page to the console
    curl_easy_cleanup(curl);
  }

  std::cout << std::endl;

  simdjson::ondemand::parser parser;
  auto json = R"({ "x" : 1, "y" : 2})"_padded;
  auto doc = parser.iterate(json);
  double y = doc.find_field("y"); // The cursor is now after the 2 (at })

  std::cout << y << std::endl;

  return 0;
}
