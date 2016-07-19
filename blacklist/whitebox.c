#include "whitebox.h"
#include <stdio.h>
#include <stdlib.h>
#include "of_msg.h"

whitebox * create_whitebox(int dpid){
    whitebox * wb = (whitebox *)malloc(sizeof(whitebox));
    wb->dpid = dpid;

    return wb;
}

void init_whitebox(const char * url, whitebox * wb){
    of_get_switch_stat(url, wb);
}

void load_routes(const char * filename, whitebox * wb){
    FILE *fp;
    fp = fopen(filename, "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    flow_entry * tail = wb->routing_table;

    int cookie_cnt = 100;

    while ((read = getline(&line, &len, fp)) != -1){
        tail->next = create_flow_entry(line, len, cookie_cnt);
        ++cookie_cnt;
        tail = tail->next;
    }

    free(line);
    fclose(fp);
}

void offload_aggregate(const char * url, flow_entry * agg, whitebox * wb){
    flow_entry * tail = wb->routing_table;
    
    while (tail != NULL){
        if (match_entry_agg(agg, tail)){
            char json_str[50];
            int len = 0; 
            create_add_flow_msg(wb->dpid, tail, json_str, 
                                &len, tail->out_port, 100);
            of_add_flow(url, json_str);
            tail->offloaded = true;
        }
        tail = tail->next;
    } 
}

void update_stats(const char * url, whitebox * wb){
    char results[1500];
    of_flow_stats(url, wb->dpid, results);
}
