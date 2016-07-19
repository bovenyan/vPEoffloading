#include <stdio.h>
#include "whitebox.h"
#include "of_msg.h"


void print_dpid(void *ptr, size_t size, size_t nmemb, void *userdata) {
    printf("return %s\n", (char*)ptr);
}

int main() {
    whitebox * wb = NULL;
    char url[] = "127.0.0.1:5000";

    init_whitebox(url, wb);

    char black_list_file[] = "../black_list.txt";
    load_black_list(black_list_file, wb);

    return 0;
}
