#include "of_msg.h"
#include <stdio.h>

void switch_stat_cb(void * ptr, size_t size, size_t nmemb, void * userdata){
    bool ready = false;
    char * ptr_c = (char*)ptr;
    whitebox ** wb_ptr = (whitebox **)userdata;
    
    printf("get URL: %s\n", ptr_c);

    for (int i = 0; i < size; ++i){
        if (ptr_c[i] == '\0')
            break;
        if (ptr_c[i] == '[' || ptr_c[i] == ']' || ptr_c[i] == ','){
            ptr_c[i] = ' ';
        }
    }

    if (atoi(ptr_c) != 0){
        *wb_ptr = create_whitebox(atoi(ptr_c));  
    }
    else{
        printf("Switch not ready \n");
        exit(1);
    }
}

void of_get_switch_stat(const char * url, whitebox ** wb){
    char full_url[50];
    strcpy(full_url, url);

    strcat(full_url, "/stats/switches");

    get_url(full_url, switch_stat_cb, (void *)wb);
}

void of_add_flow(const char * url, char * data){
    char full_url[50];
    strcpy(full_url, url);

    strcat(full_url, "/stats/flowentry/add");
    printf("len of url: %s\n", full_url);
    
    post_url(full_url, data);
}

void of_del_flow(const char * url, char * data){
    char full_url[50];
    strcpy(full_url, url);

    strcat(full_url, "/stats/flowentry/delete");
    
    post_url(full_url, data);
}

void flow_stats_cb(void * ptr, size_t size, size_t nmemb, void * userdata){
    strncpy((char*)userdata, (char*)ptr, size);
    *((char*)userdata + size) = '\0';
}

void of_flow_stats(const char * url, char * dpid, char * results){
    char full_url[50];
    strcpy(full_url, url);
    int len = strlen(full_url);
    sprintf(full_url + len, "/stats/flowentry/%s", dpid);
    
    get_url(full_url, flow_stats_cb, (void *) results);
}
