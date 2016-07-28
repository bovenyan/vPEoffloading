#include "util.h"
#include "stdio.h"

unsigned int ip_str2int(const char * ip_str) {
    struct in_addr res_obj;
    inet_aton(ip_str, &res_obj);
    printf("ip %s, ipint: %u\n", ip_str, res_obj.s_addr);
    return res_obj.s_addr;
}

char * ip_int2str(const unsigned int ip_int) {
    struct in_addr res_obj;
    res_obj.s_addr = ip_int;
    return inet_ntoa(res_obj);
}
