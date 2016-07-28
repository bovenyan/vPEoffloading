#include <stdio.h>
#include "whitebox.h"
#include "of_msg.h"


void print_dpid(void *ptr, size_t size, size_t nmemb, void *userdata) {
    printf("return %s\n", (char*)ptr);
}

int main() {
    whitebox * wb = NULL;
    char url[] = "http://127.0.0.1:8080";

    char route_list_file[] = "../routing_list.txt";

    init_whitebox(url, route_list_file, &wb);

    char agg_str[] = "192.168.0.1 192.168.1.1 * *";
    flow_entry * agg = create_flow_entry(agg_str, strlen(agg_str), 0);
    offload_aggregate(url, agg, wb);

    destroy_whitebox(wb);

    return 0;
}
