#include <stdio.h>
#include "rest.h"

void print_dpid(void *ptr, size_t size, size_t nmemb, void *userdata) {
    printf("return %s\n", (char*)ptr);
}

int main() {
    return 0;
}
