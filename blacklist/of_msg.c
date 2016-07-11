#include "of_msg.h"

void switch_stat_cb(void * ptr, size_t size, size_t nmemb, void * userdata){
    bool ready = false;
    char * ptr_c = (char*)ptr;
    for (int i = 0; i < size; ++i){
        if (ptr_c[i] == '\0')
            break;
        if (ptr_c[i] == '[' || ptr_c[i] == ']'){
            ptr_c[i] = ' ';
        }
        if (ptr_c[i] == ','){
            ready = true;
        }
    }

    if (!ready){
        printf("Switch not ready \n");
        exit(1);
    }
}

void of_get_switch_stat(char * url){
    char full_url[50];
    strcpy(full_url, url);

    strcat(full_url, "/stats/switches");

    get_url(url, switch_stat_cb, NULL);
}

void of_add_flow(char * url, char * data){
    char full_url[50];
    strcpy(full_url, url);

    strcat(full_url, "/stats/flowentry/add");
    
    post_url(url, data);
}

void of_del_flow(char * url, char * data){
    char full_url[50];
    strcpy(full_url, url);

    strcat(full_url, "/stats/flowentry/delete");
    
    post_url(url, data);
}

void flow_stats_cb(void * ptr, size_t size, size_t nmemb, void * userdata){
    strncpy((char*)userdata, (char*)ptr, size);
    *((char*)userdata + size) = '\0';
}

void of_flow_stats(char * url, int dpid, char * results){
    char full_url[50];
    strcpy(full_url, url);
    int len = strlen(full_url);
    sprintf(full_url + len, "/stats/flowentry/%d", dpid);
    
    get_url(url, flow_stats_cb, (void *) results);
}
