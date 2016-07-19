#ifndef REST_H
#define REST_H
#include <curl/curl.h>

typedef void (*call_back)(void *ptr, size_t size,
                          size_t nmemb, void * userdata);

void get_url(char * url, call_back cb, void * param);

void post_url(char * url, char * data);

#endif
