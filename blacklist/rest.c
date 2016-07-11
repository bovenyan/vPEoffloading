#include "rest.h"

void get_url(char * url, call_back cb, void * param) {
    CURL * curl;
    CURLcode res;
    struct curl_slist *headers = NULL;
    curl_slist_append(headers, "Accept: application/json");
    curl_slist_append(headers, "Content-Type: application/json");
    curl_slist_append(headers, "charsets: utf-8");

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, param);

        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }

    return;
}

void post_url(char * url, char * data){
    CURL * curl;
    CURLcode res;
    struct curl_slist *headers = NULL;
    curl_slist_append(headers, "Accept: application/json");
    curl_slist_append(headers, "Content-Type: application/json");
    curl_slist_append(headers, "charsets: utf-8");

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }    
    return;
}
