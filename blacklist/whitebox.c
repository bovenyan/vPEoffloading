#include "whitebox.h"
#include <stdio.h>
#include <stdlib.h>
#include "of_msg.h"

whitebox * create_whitebox(char * dpid){
    whitebox * wb = (whitebox *)malloc(sizeof(whitebox));
    strcpy(wb->dpid, dpid);
    wb->routing_table = (flow_entry *)malloc(sizeof(flow_entry));
    wb->routing_table->next = NULL;

    printf("whitebox created, connected with dpid: %s\n", dpid);
    return wb;
}

void init_whitebox(const char * url, const char * filename, whitebox ** wb_ptr){
    of_get_switch_stat(url, wb_ptr);
    
    FILE *fp;
    fp = fopen(filename, "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    flow_entry * tail = (*wb_ptr)->routing_table;
    int cookie_cnt = 100;

    while ((read = getline(&line, &len, fp)) != -1){
        tail->next = create_flow_entry(line, len, cookie_cnt);
        ++cookie_cnt;
        tail = tail->next;
    }

    free(line);
    fclose(fp);
}

void destroy_whitebox(whitebox * wb){
    flow_entry * cur = wb->routing_table; 
    flow_entry * tail;

    while(cur != NULL){
        tail = cur->next;
        free(cur);
        cur = tail;
    }

    free(wb);
}

void offload_aggregate(const char * url, flow_entry * agg, whitebox * wb){
    flow_entry * tail = wb->routing_table->next;
    

    while (tail != NULL){
        if (match_entry_agg(agg, tail)){
            char json_str[MAX_OF_MSG_LEN];
            int len = 0; 
            create_add_flow_msg(wb->dpid, tail, json_str, 
                                &len, tail->out_port, 100);
            of_add_flow(url, json_str);
            tail->offloaded = true;
        }
        else{
            printf("not matched\n");
        }
        tail = tail->next;
    } 
}

void update_stats(const char * url, whitebox * wb){
    char results[1500];
    of_flow_stats(url, wb->dpid, results);
}
