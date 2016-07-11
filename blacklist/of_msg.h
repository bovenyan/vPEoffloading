#ifndef OF_MSG_H
#define OF_MSG_H

#include "rest.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void switch_stat_cb(void * ptr, size_t size, size_t nmemb, void * userdata);

void of_get_switch_stat(char * url);

void of_add_flow(char * url, char * data);

void of_del_flow(char * url, char * data);

void of_flow_stats(char * url, int dpid, char * result);

#endif
