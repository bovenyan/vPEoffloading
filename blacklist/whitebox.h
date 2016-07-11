#ifndef WHITEBOX_H
#define WHITEBOX_H

#define _GNU_SOURCE
#include "flow_entry.h"

typedef struct whitebox {
    int lswitch_dpid;
    int rswitch_dpid;
    flow_entry * offload_list;
} whitebox;

whitebox * create_whitebox();

void load_black_list(const char * filename, whitebox * wb);

void update_stats(whitebox * wb);


#endif
