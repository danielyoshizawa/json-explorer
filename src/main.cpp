// Main.cpp
//
// Program entry point

#include <iostream>
#include <curl/curl.h>
#include <simdjson.h>
#include <stdlib.h> // for realloc
#include <string.h> // for memcpy
#include "explorer.hpp"

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
  std::string endpoint;
  std::cout << "Enter endpoint address : " << std::endl;
  std::cin >> endpoint; // e.g. "https://dogapi.dog/api/v2/facts"
  // Declaring variables
  simdjson::padded_string resource;
  // Fetching resouce from the internet
  CURL *curl = curl_easy_init();
  if (curl) {
    struct memory chunk = {0};
    CURLcode response;
    struct curl_slist *list = NULL;
    curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, static_cast<void *>(&chunk));
    // List of headers
    list = curl_slist_append(list, "Accept: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
    response = curl_easy_perform(curl);
    if (response)
    {
      std::cerr << "## Error : " << curl_easy_strerror(response) << std::endl;
      return EXIT_FAILURE;
    } else { // CURLE_OK
      resource = simdjson::padded_string(chunk.response, chunk.size);
    }

    free(chunk.response);
    curl_slist_free_all(list);
    curl_easy_cleanup(curl);
  }

  json::explorer explorer{resource};

  std::string path{};
  // TODO : Implement commands (cd, ls and quit|exit)
  while (true)
  {
    std::cout << "Path : " << std::endl;
    std::cin >> path;
    explorer.path(path);
  }

  return EXIT_SUCCESS;
}
