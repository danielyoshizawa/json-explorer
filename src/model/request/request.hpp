#pragma once
#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <stdlib.h> // for realloc
#include <string.h> // for memcpy
#include <string>

namespace json
{
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
};

namespace json
{
  class request
  {
  public:
    std::string load(const std::string & endpoint);
  };
};

#endif // REQUEST_HPP
