#include "whitebox.h"
#include <stdio.h>
#include <stdlib.h>

void load_black_list(const char * filename, whitebox * wb){
    FILE *fp;
    fp = fopen(filename, "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    flow_entry * tail = wb->offload_list;

    int cookie_cnt = 100;

    while ((read = getline(&line, &len, fp)) != -1){
        tail->next = create_flow_entry(line, len, cookie_cnt);
        ++cookie_cnt;
    }

    free(line);
    fclose(fp);
}
