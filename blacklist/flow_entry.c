#include "flow_entry.h"
#include <stdio.h>

flow_entry * create_flow_entry(char * line, int len, int cookie) {
    flow_entry * ptr = (flow_entry *)malloc(sizeof(*ptr));
    ptr->dst_ip = 0;
    ptr->src_ip = 0;
    ptr->src_port = 0;
    ptr->dst_port = 0;
    ptr->cookie = cookie;

    char * pch;
    pch = strtok(line, " \t");

    if (strncmp(pch, "*", 1) != 0) {
        ptr->src_ip = ip_str2int(pch);  // src IP
    }
    pch = strtok(NULL, " \t");

    if (strncmp(pch, "*", 1) != 0) {
        ptr->dst_ip = ip_str2int(pch);  // src IP
    }
    pch = strtok(NULL, " \t");

    if (strncmp(pch, "*", 1) != 0) {
        ptr->src_port = atoi(pch);  // src IP
    }
    pch = strtok(NULL, " \t");

    if (strncmp(pch, "*", 1) != 0) {
        ptr->dst_port = ip_str2int(pch);  // src IP
    }

    ptr->byte_count = 0;
    ptr->offloaded = false;

    return ptr;
}

void create_add_flow_msg(int dpid, flow_entry * fe, char * json_str,
                         int * len, int out_port, int soft_timeout) {
    char match[200];
    strcpy(match, "\"match\": {");

    if (fe->src_ip != 0) {
        sprintf(match + strlen(match), "\"nw_src: %s\"",
                ip_int2str(fe->src_ip));
    }

    if (fe->dst_ip != 0) {
        sprintf(match + strlen(match), ", \"nw_dst: %s\"",
                ip_int2str(fe->dst_ip));
    }

    if (fe->src_port != 0) {
        sprintf(match + strlen(match), ", \"tp_src: %d\"", fe->src_port);
    }

    if (fe->dst_port != 0) {
        sprintf(match + strlen(match), ", \"tp_dst: %d\"", fe->dst_port);
    }

    strcat(match, "}");

    *len = sprintf(json_str, "\'{ \"dpid\": %d, \"cookie\": %d, \
                   \"cookie_mask\": 65535, \"idle_timeout\": %d\
                   \"priority\":100, %s, \"actions\":[\"type\":\
                   \"OUTPUT\", \"port\":%d]}\'",
                   dpid, fe->cookie, soft_timeout, match, out_port);
}

void create_del_flow_msg(int dpid, flow_entry * fe,
                         char * json_str, int * len, int cookie) {
    *len = sprintf(json_str, "\'{\"dpdk:\" %d \"cookie\": %d, \
                   \"cookie_mask\": 65535\"}\'", dpid, cookie);
}

bool match_entry(char * json_string, flow_entry * entry) {
    char * ptr;
    char * new_ptr;
    char * end_ptr;
    char buf[32];

    // check all matching fields
    ptr = strstr ("\"match\": {", json_string);
    if (ptr == NULL)
        return false;

    new_ptr = strstr("\"nw_src\": \"", ptr);

    if (new_ptr != NULL) {
        unsigned int src_ip;
        bzero(buf, 32);
        end_ptr = strchr(new_ptr+11, '"');
        strncpy(buf, new_ptr+11, end_ptr-new_ptr+11);
        src_ip = ip_str2int(buf);

        if (src_ip != entry->src_ip)
            return false;
    }

    ptr = new_ptr;
    new_ptr = strstr("\"nw_dst\": \"", ptr);

    if (new_ptr != NULL) {
        unsigned int dst_ip;
        bzero(buf, 32);
        end_ptr = strchr(new_ptr+11, '"');
        strncpy(buf, new_ptr+11, end_ptr-new_ptr+11);
        dst_ip = ip_str2int(buf);

        if (dst_ip != entry->dst_ip)
            return false;
    }

    ptr = new_ptr;
    new_ptr = strstr("\"sport\": \"", ptr);

    if (new_ptr != NULL) {
        unsigned int src_port;
        bzero(buf, 32);
        end_ptr = strchr(new_ptr+10, '"');
        strncpy(buf, new_ptr+10, end_ptr-new_ptr+10);
        src_port = atoi(buf);

        if (src_port != entry->src_port)
            return false;
    }

    ptr = new_ptr;
    new_ptr = strstr("\"dport\": \"", ptr);

    if (new_ptr != NULL) {
        unsigned int dst_port;
        bzero(buf, 32);
        end_ptr = strchr(new_ptr+10, '"');
        strncpy(buf, new_ptr+10, end_ptr-new_ptr+10);
        dst_port = atoi(buf);

        if (dst_port != entry->dst_port)
            return false;
    }

    // Update counter;
    ptr = strstr("\"byte_count\"", json_string);

    if (ptr != NULL) {
        bzero(buf, 32);
        end_ptr = strchr(ptr+14, ',');
        strncpy(buf, ptr+14, end_ptr-ptr+14);
        entry->byte_count = atoi(buf);
    }

    return true;
}
