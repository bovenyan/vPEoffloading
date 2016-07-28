#ifndef WHITEBOX_H
#define WHITEBOX_H

#define _GNU_SOURCE
#include "flow_entry.h"


#define MAX_OF_MSG_LEN 500

typedef struct whitebox {
    //uint64_t dpid;
    char dpid[15];
    flow_entry * routing_table;
} whitebox;

whitebox * create_whitebox(char * dpid);

void init_whitebox(const char * url, const char * filename, whitebox ** wb_ptr);

void destroy_whitebox(whitebox * wb);

void offload_aggregate(const char * url, flow_entry * agg, whitebox * wb);

void update_stats(const char * url, whitebox * wb);


#endif
