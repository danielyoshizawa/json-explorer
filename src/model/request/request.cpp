#include "request.hpp"

#include <iostream>
#include <curl/curl.h>

std::string json::request::load(const std::string & endpoint)
{
  std::string resource{};
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
      // TODO : Change std::variant return
      std::cerr << "## Error : " << curl_easy_strerror(response) << std::endl;
    } else { // CURLE_OK
      resource = std::string(chunk.response, chunk.size);
    }

    free(chunk.response);
    curl_slist_free_all(list);
    curl_easy_cleanup(curl);
  }

  return resource;
}
