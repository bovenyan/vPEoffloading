#ifndef FLOW_ENTRY_H
#define FLOW_ENTRY_H
#include <stdbool.h>
#include <string.h>
#include "util.h"
#include <stdlib.h>

typedef struct flow_entry {
    unsigned int src_ip;
    unsigned int src_mask;
    unsigned int dst_ip;
    unsigned int dst_mask;
    unsigned int src_port;
    unsigned int dst_port;
    unsigned int cookie;

    unsigned int out_port;

    int byte_count;
    bool offloaded;
    struct flow_entry * next;
} flow_entry;

flow_entry * create_flow_entry(char * line, int len, int cookie);

void create_add_flow_msg(int dpid, flow_entry * fe,
                         char * json_str, int * len,
                         int out_port, int soft_timeout);

void create_del_flow_msg(int dpid, flow_entry * fe,
                         char * json_str, int * len, int cookie);

bool match_entry_json(char * json_string, flow_entry * entry);

bool match_entry_agg(flow_entry * agg, flow_entry * entry);

#endif
