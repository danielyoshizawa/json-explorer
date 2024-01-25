// Main.cpp
//
// Program entry point

#include <iostream>
#include <curl/curl.h>
#include <simdjson.h>
#include <stdlib.h> // for realloc
#include <string.h> // for memcpy

struct memory
{
  char *response;
  size_t size;
};

// Callback function to write data from stream (Curl)
static size_t callback(void *data, size_t size, size_t nmemb, void *clientp)
{
  size_t realsize = size * nmemb;
  struct memory *mem = static_cast<struct memory *>(clientp);

  char *ptr = static_cast<char *>(realloc(mem->response, mem->size + realsize + 1));
  if (!ptr)
  {
    return 0; // out of memory
  }

  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;

  return realsize;
}

int main()
{
  // Declaring variables
  simdjson::padded_string resource;
  // Fetching resouce from the internet
  CURL *curl = curl_easy_init();
  if (curl) {
    struct memory chunk = {0};
    CURLcode response;
    curl_easy_setopt(curl, CURLOPT_URL, "https://dogapi.dog/api/v2/facts");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, static_cast<void *>(&chunk));
    response = curl_easy_perform(curl);
    if (response)
    {
      std::cerr << "## Error : " << curl_easy_strerror(response) << std::endl;
      return EXIT_FAILURE;
    } else { // CURLE_OK
      resource = simdjson::padded_string(chunk.response, chunk.size);
    }

    free(chunk.response);

    curl_easy_cleanup(curl);
  }

  // Parsing content
  simdjson::ondemand::parser parser;
  simdjson::ondemand::document doc;
  auto error = parser.iterate(resource).get(doc);
  if (error)
  {
    std::cerr << error << std::endl;
    return EXIT_FAILURE;
  }

  simdjson::ondemand::array data;
  error = doc.find_field("data").get(data);
  if (error)
  {
    std::cerr << "## Error : " << error << std::endl;
    return EXIT_FAILURE;
  }

  // Printing elements
  for (auto elem : data) {
    simdjson::ondemand::object attributes;
    error = elem.find_field("attributes").get(attributes);
    if (error)
    {
      std::cerr << "## Error : " << error << std::endl;
      return EXIT_FAILURE;
    }

    simdjson::ondemand::value body;
    error = attributes.find_field("body").get(body);
    if (error)
    {
      std::cerr << "## Error : " << error << std::endl;
      return EXIT_FAILURE;
    }

    std::cout << simdjson::to_json_string(body) << std::endl;
  }

  return EXIT_SUCCESS;
}
